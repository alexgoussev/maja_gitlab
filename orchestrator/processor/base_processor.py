# -*- coding: utf-8 -*-
"""
###################################################################################################
#
#                        o     o
#                        oo   oo   oo        o   oo        ,-.
#                        o o o o  o  o       o  o  o       \_/
#                        o  o  o o    o      o o    o     {|||)<
#                        o     o oooooo      o oooooo      / \
#                        o     o o    o o    o o    o      `-^
#                        o     o o    o  oooo  o    o
#
###################################################################################################

orchestrator.processor.base_processor -- shortdesc

orchestrator.processor.base_processor is the base of all processors

It defines method mandatory for a processor

###################################################################################################

:copyright: 2019 CNES. All rights reserved.
:license: license

###################################################################################################
"""

from orchestrator.common.logger.maja_logging import configure_logger
from orchestrator.common.constants import CAMSStatus
LOGGER = configure_logger(__name__)


class BaseProcessor(object):

    def __init__(self, apphandler):
        self._name = "BASE"
        self._productIsValid = True
        self._apphandler = apphandler
        self._listofenabledsat = list()
        self._cams_status = CAMSStatus.DEACTIVATED

    def pre_processing(self):
        raise NotImplementedError

    def scientific_processing(self):
        raise NotImplementedError

    def post_processing(self):
        raise NotImplementedError

    def get_name(self):
        return self._name

    def init_list_of_sat(self):
        self._listofenabledsat = list()

    def activate_this_sat(self, sat, plugin, uniquesat):
        self._listofenabledsat.append(plugin + "|" + uniquesat + "|" + sat)
        LOGGER.info("Activated " + self._listofenabledsat[-1])

    @staticmethod
    def get_associated_unique_sat(key):
        return key.split("|")[1]

    @staticmethod
    def get_associated_sat(key):
        return key.split("|")[2]

    @staticmethod
    def get_associated_plugin(key):
        return key.split("|")[0]

    def get_list_of_unique_sat_activated(self):
        list_of_sat = list()
        for s in self._listofenabledsat:
            list_of_sat.append(self.get_associated_unique_sat(s))
        return list_of_sat

    def get_list_of_activated_sat(self):
        return self._listofenabledsat
