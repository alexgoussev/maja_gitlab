# -*- coding: utf-8 -*-
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

:copyright: 2019 CNES. All rights reserved.
:license: license

###################################################################################################
"""

from .otb_cots import MajaOtbCots
from orchestrator.common.logger.maja_logging import configure_logger
from orchestrator.common.maja_utils import get_test_mode
LOGGER = configure_logger(__name__)


class OtbAppHandler:

    ram_to_use = 512

    @staticmethod
    def set_ram_to_use(ram):
        OtbAppHandler.ram_to_use = ram

    def __init__(self, otb_app, parameters, write_output=True):
        self._c1 = MajaOtbCots()
        self._app_name = otb_app
        LOGGER.debug("Initializing : " + self._app_name)
        if "ram" not in list(parameters.keys()):
            parameters["ram"] = str(OtbAppHandler.ram_to_use)
        LOGGER.debug(parameters)
        self._write_output = write_output
        self._c1.pre(otb_app, parameters)
        if not get_test_mode():
            self._run()
        self._post()

    def __del__(self):
        if self._c1.otb_app is not None:
            LOGGER.debug("Destructing : "+self._app_name)
        del(self._c1)

    def _run(self):
        LOGGER.debug("Running : " + self._app_name)
        self._c1.run(self._write_output)
        LOGGER.debug("Finished : " + self._app_name)

    def _post(self):
        LOGGER.debug("Running : " + self._app_name)
        self._c1.post(self._write_output)
        LOGGER.debug("Finished : " + self._app_name)

    def getoutput(self):
        return self._c1.outputs

    def get_app_name(self):
        if self._c1.otb_app is not None:
            return self._app_name
        else:
            return None


class OtbCotsGeneric(MajaOtbCots):

    def __init__(self):
        super(OtbCotsGeneric, self).__init__()
        # TODO: TBC
        # self.outputs = {}

    # def pre(self, otb_app, parameters):
    #     """
    #
    #     :param parameters:
    #     :return:
    #     """
    #     # The following line creates an instance of the BandMath application
    #     self.otb_app = otbApplication.Registry.CreateApplication(otb_app)
    #
    #     if self.otb_app is None:
    #         raise MajaDriverException("No app " + otb_app + " found")
    #
    #     self.otb_app.Init()
    #     # The following lines set all the application parameters:
    #     LOGGER.debug("Parameters for %s : %s", otb_app, parameters)
    #     LOGGER.debug("Parameters type %s", {key: (type(value), value.__class__.__name__)
    #                                         for key, value in parameters.iteritems()})
    #
    #     # remove flag if set to false
    #     parameters_clean = {}
    #     for key, value in parameters.iteritems():
    #         if self.otb_app.GetParameterType(key) == 0 and not value:
    #             LOGGER.debug("%s removed because set to %s", key, value)
    #             continue
    #         elif self.otb_app.GetParameterType(key) == otbApplication.ParameterType_OutputImage \
    #                 and len(value.split(":")) > 1:
    #             # split value into value and output type
    #             parameters_clean[key] = (value.split(":")[0])
    #             self.otb_app.SetParameterOutputImagePixelType(key, OTB_APP_PIXELS_TYPE.get(value.split(":")[1]))
    #         else:
    #             parameters_clean[key] = value
    #
    #     self.otb_app.SetParameters(parameters_clean)
    #     # Update parameters for dynamics
    #     self.otb_app.UpdateParameters()
    #
    # def post(self, write_output):
    #
    #     LOGGER.debug("Write output %s", write_output)
    #
    #     params_keys = self.otb_app.GetParametersKeys()
    #     for param in params_keys:
    #         # role == 1 -> output
    #         if self.otb_app.GetParameterRole(param) == 1
    #         or self.otb_app.GetParameterType(param) == otbApplication.ParameterType_OutputImage:
    #             if write_output:
    #                 self.outputs[param] = copy.deepcopy(self.otb_app.GetParameterValue(param))
    #             else:
    #                 if self.otb_app.GetParameterType(param) == otbApplication.ParameterType_OutputImage:
    #                     self.outputs[param] = self.otb_app.GetParameterOutputImage(param)
    #                 else:
    #                     self.outputs[param] = copy.deepcopy(self.otb_app.GetParameterValue(param))
    #     if write_output:
    #         self.otb_app = None
