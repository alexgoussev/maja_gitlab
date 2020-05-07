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
from orchestrator.cots.otb.otb_app_handler import OtbAppHandler
from orchestrator.modules.maja_module import MajaModule
from orchestrator.common.maja_exceptions import *


LOGGER = configure_logger(__name__)


class MajaValidityL2Nominal(MajaModule):
    """
    classdocs
     """

    NAME = "ValidityL2Nominal"

    def __init__(self):
        """
        Constructor
        """
        super(MajaValidityL2Nominal, self).__init__()
        self.in_keys_to_check = ["L2Reader", "L2COMM"]
        self.out_keys_to_check = []
        self.out_keys_provided = ["L2inNoDataRate","L2inValidity"]

    def run(self, dict_of_input, dict_of_output):
        LOGGER.info("Validity L2 nominal computation start")
        param_stats = {"im": dict_of_input.get("L2Reader").get_value("NDTImage"),
                       "exclude": 1}
        l2_stat = OtbAppHandler("Stats", param_stats)
        # Test on the value
        l_L2inNoDataRate = 0
        if l2_stat.getoutput()["excludedcount"] == 0 and l2_stat.getoutput()["validcount"] == 0:
            l_L2inNoDataRate = 0
        else:
            l_L2inNoDataRate = l2_stat.getoutput()["excludedcount"] * 100.0 / \
                (l2_stat.getoutput()["excludedcount"] + l2_stat.getoutput()["validcount"])
        LOGGER.debug("L2 no data rate : " + str(l_L2inNoDataRate))
        dict_of_output["L2inNoDataRate"] = l_L2inNoDataRate
        dict_of_output["L2inValidity"] = False
        if l_L2inNoDataRate > float(dict_of_input.get("L2COMM").get_value("MaxNoDataPercentage")):
            dict_of_output["L2inValidity"] = False
        else:
            dict_of_output["L2inValidity"] = True

