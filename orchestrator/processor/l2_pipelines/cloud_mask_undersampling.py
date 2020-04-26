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
from orchestrator.modules.maja_module import MajaModule
from orchestrator.common.maja_exceptions import *
from orchestrator.common.logger.maja_logging import configure_logger
from orchestrator.cots.otb.otb_app_handler import OtbAppHandler
import os
LOGGER = configure_logger(__name__)


class MajaCloudMaskUndersampling(MajaModule):
    """
    classdocs
    """

    NAME = "CloudMaskUndersampling"

    def __init__(self):
        """
        Constructor
        """
        super(MajaCloudMaskUndersampling, self).__init__()
        self._undersampling_app = None

    def run(self, dict_of_input, dict_of_output):
        LOGGER.info("Cloud Mask Undersampling start")
        caching = dict_of_input.get("Params").get("Caching")
        cla_working = ""
        if caching:
            cla_working = dict_of_input.get("AppHandler").get_directory_manager().get_temporary_directory("CloudMaskUnderProc_",
                                            do_always_remove=True)
        l1_cla = dict_of_input.get("L1Reader").get_value("CLAImage")
        cla_image = os.path.join(cla_working, "cla_image_sub.tif")
        clalt_image = os.path.join(cla_working, "clalt_image_sub.tif")
        param_resamp_cla = {"dtm": dict_of_input.get("DEM").ALC,
                            "im": l1_cla,
                            "nodata": dict_of_input.get("L1Info").RealL1NoData,
                            "cla": cla_image,
                            "clalt": clalt_image}
        self._undersampling_app = OtbAppHandler("CloudMaskUndersampling", param_resamp_cla, write_output=caching)
        dict_of_output["CLA_Sub"] = self._undersampling_app.getoutput()["cla"]
        dict_of_output["CLALT_Sub"] = self._undersampling_app.getoutput()["clalt"]

