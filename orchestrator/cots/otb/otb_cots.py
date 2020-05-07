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

orchestrator.cots.otb.otb_cots -- shortdesc

orchestrator.cots.otb.otb_cots is a description

It defines classes_and_methods

###################################################################################################

:copyright: 2019 CNES. All rights reserved.
:license: license

###################################################################################################
"""

from ..maja_cots import MajaCots
from orchestrator.common.maja_exceptions import *
from orchestrator.common.maja_utils import get_test_mode
import otbApplication
import copy
from orchestrator.common.logger.maja_logging import configure_logger

LOGGER = configure_logger(__name__)

OTB_APP_PIXELS_TYPE = {"uint8": otbApplication.ImagePixelType_uint8,
                       "uint16": otbApplication.ImagePixelType_uint16,
                       "uint32": otbApplication.ImagePixelType_uint32,
                       "int16": otbApplication.ImagePixelType_int16,
                       "int32": otbApplication.ImagePixelType_int32,
                       "float": otbApplication.ImagePixelType_float,
                       "double": otbApplication.ImagePixelType_double}

DEFAULT_OUTPUT_VALUES = {otbApplication.ParameterType_Float: 1.0,
                         otbApplication.ParameterType_Int: 1}


class MajaOtbCots(MajaCots):

    def __init__(self):
        super(MajaOtbCots, self).__init__(None)
        # TODO: TBC
        self.outputs = {}
        self.otb_app = None

    def run(self, write_output=True):
        if write_output:
            # The following line execute the application
            self.otb_app.ExecuteAndWriteOutput()
        else:
            self.otb_app.Execute()

    def __del__(self):
        del(self.otb_app)
        self.otb_app = None

    def pre(self, otb_app, parameters):
        """

        :param parameters:
        :param otb_app:
        :return:
        """
        # The following line creates an instance of the BandMath application
        self.otb_app = otbApplication.Registry.CreateApplication(otb_app)

        if self.otb_app is None:
            raise MajaDriverException("No app " + otb_app + " found")

        self.otb_app.Init()
        # The following lines set all the application parameters:
        LOGGER.debug("Parameters for %s : %s", otb_app, parameters)
        LOGGER.debug("Parameters type %s", {key: (type(value), value.__class__.__name__)
                                            for key, value in parameters.items()})

        # First set input image
        if "in" in parameters:
            parameters_im = {"in": parameters["in"]}
            self.otb_app.SetParameters(parameters_im)
            if not get_test_mode():
                self.otb_app.UpdateParameters()

        # remove flag if set to false
        parameters_clean = {}
        for key, value in parameters.items():
            if key in self.otb_app.GetParametersKeys():
                if self.otb_app.GetParameterType(key) == otbApplication.ParameterType_OutputImage \
                        and len(value.split(":")) > 1:
                    # split value into value and output type
                    if value.split(":")[1] in  OTB_APP_PIXELS_TYPE.keys():
                        parameters_clean[key] = (value.split(":")[0])
                        self.otb_app.SetParameterOutputImagePixelType(key, OTB_APP_PIXELS_TYPE.get(value.split(":")[1]))
                    else:
                        parameters_clean[key] = value
                else:
                    parameters_clean[key] = value
            else:
                LOGGER.debug("%s removed because not in app list", key)
                continue

        self.otb_app.SetParameters(parameters_clean)
        # Update parameters for dynamics
        if not get_test_mode():
            self.otb_app.UpdateParameters()

    def post(self, write_output=True):

        LOGGER.debug("Write output %s", write_output)
        params_keys = self.otb_app.GetParametersKeys()
        for param in params_keys:
            # role == 1 -> output
            if self.otb_app.GetParameterRole(param) == 1 or self.otb_app.GetParameterType(
                    param) == otbApplication.ParameterType_OutputImage:
                if get_test_mode():
                    if self.otb_app.GetParameterType(param) == otbApplication.ParameterType_Int:
                        self.outputs[param] = 1
                    elif self.otb_app.GetParameterType(param) == otbApplication.ParameterType_Float:
                        self.outputs[param] = 1.0
                    elif self.otb_app.GetParameterType(param) == otbApplication.ParameterType_String:
                        self.outputs[param] = "false"
                    else:
                        self.outputs[param] = copy.deepcopy(self.otb_app.GetParameterValue(param))
                else:
                    if write_output:
                        if not self.otb_app.GetParameterType(param) == otbApplication.ParameterType_Group:
                            self.outputs[param] = copy.deepcopy(self.otb_app.GetParameterValue(param))
                    else:
                        if self.otb_app.GetParameterType(param) == otbApplication.ParameterType_OutputImage:
                            self.outputs[param] = self.otb_app.GetParameterOutputImage(param)
                        else:
                            if not self.otb_app.GetParameterType(param) == otbApplication.ParameterType_Group:
                                self.outputs[param] = copy.deepcopy(self.otb_app.GetParameterValue(param))
        if write_output:
            del(self.otb_app)
            self.otb_app = None
