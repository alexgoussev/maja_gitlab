# -*- coding: utf-8 -*-
#
# Copyright (C) 2020 Centre National d'Etudes Spatiales (CNES)
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#    http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#
"""
###################################################################################################

                        o     o
                        oo   oo   oo        o   oo        ,-.
                        o o o o  o  o       o  o  o       \_/
                        o  o  o o    o      o o    o     {|||D
                        o     o oooooo      o oooooo      / \
                        o     o o    o o    o o    o      `-^
                        o     o o    o  oooo  o    o

###################################################################################################
orchestrator.cots.otb.otb_launcher -- shortdesc

orchestrator.cots.otb.otb_launcher is a description

It defines classes_and_methods

###################################################################################################
"""

from .otb_cots import MajaOtbCots
from orchestrator.common.logger.maja_logging import configure_logger
from orchestrator.common.maja_utils import get_test_mode,is_croco_off,is_croco_on
from orchestrator.common.system_utils import memory_used_by_process2,memory_used_by_process_current
import time,os
LOGGER = configure_logger(__name__)


class OtbAppHandler:

    ram_to_use = 4096
    ram_limit_factor = 2.0

    @staticmethod
    def set_ram_to_use(ram):
        OtbAppHandler.ram_to_use = ram

    def __init__(self, otb_app, parameters, write_output=True):
        self._c1 = MajaOtbCots()
        self._app_name = otb_app
        LOGGER.debug("Initializing : " + self._app_name)
        if "ram" not in list(parameters.keys()):
            curr_ram = int(memory_used_by_process_current(os.getpid()))
            avail_ram = OtbAppHandler.ram_to_use - curr_ram
            if avail_ram < OtbAppHandler.ram_to_use/OtbAppHandler.ram_limit_factor:
                parameters["ram"] = str(OtbAppHandler.ram_to_use / OtbAppHandler.ram_limit_factor)
            else:
                parameters["ram"] = str(avail_ram)
        LOGGER.debug(parameters)
        self._write_output = not is_croco_off() and (write_output or is_croco_on())
        self._c1.pre(otb_app, parameters)
        if not get_test_mode():
            self._run()
        self._post()

    def __del__(self):
        if self._c1 is not None:
            LOGGER.debug("Destructing : "+self._app_name)
        ram_bef = int(memory_used_by_process_current(os.getpid()))
        del self._c1
        ram_after = int(memory_used_by_process_current(os.getpid()))
        LOGGER.debug("RAM : " + str(ram_bef) + " : " + str(ram_after) + " : " + str(ram_bef-ram_after) + " MB")

    def _run(self):
        start_time = time.time()
        LOGGER.debug("Running : " + self._app_name)
        self._c1.run(self._write_output)
        LOGGER.debug("Finished : " + self._app_name +
                     " ,Time: "+time.strftime("%M min %S seconds", time.gmtime(time.time()-start_time)) +
                     " ,RAM current : " + str(int(memory_used_by_process_current(os.getpid()))) + " MB" +
                     " ,RAM max : " + str(int(memory_used_by_process2(os.getpid())))+" MB")

    def _post(self):
        LOGGER.debug("Running : " + self._app_name)
        self._c1.post(self._write_output)
        LOGGER.debug("Finished : " + self._app_name +
                     " ,RAM current : " + str(int(memory_used_by_process_current(os.getpid()))) + " MB" +
                     " ,RAM max : " + str(int(memory_used_by_process2(os.getpid()))) + " MB")

    def getoutput(self):
        return self._c1.outputs

    def get_app_name(self):
        if self._c1.otb_app is not None:
            return self._app_name
        else:
            return None

    def free_ressources(self):
        if self._c1.otb_app is not None:
            self._c1.otb_app.FreeRessources()
