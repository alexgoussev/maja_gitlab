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


class MajaSnowPercentage(MajaModule):
    """
    classdocs
    """

    NAME = "SnowPercentage"

    def __init__(self):
        """
        Constructor
        """
        super(MajaSnowPercentage, self).__init__()
        self.in_keys_to_check = []
        self.out_keys_to_check = ["cld_snow"]
        self.out_keys_provided = ["SnowRate"]

    def run(self, dict_of_input, dict_of_output):
        LOGGER.info("Snow percentage computation start")
        param_stats = {"im": dict_of_output.get("cld_snow"),
                       "exclude": 1}
        l2_stat = OtbAppHandler("Stats", param_stats)
        # Test on the value
        if (l2_stat.getoutput()["excludedcount"] == 0 and l2_stat.getoutput()["validcount"] == 0):
            l_snowrate = 0
        else:
            l_snowrate = l2_stat.getoutput()["excludedcount"] * 100.0 / (l2_stat.getoutput()
                                                                         ["excludedcount"] + l2_stat.getoutput()["validcount"])
        LOGGER.debug("L2 snowrate : " + str(l_snowrate))
        dict_of_output["SnowRate"] = l_snowrate
        return l_snowrate

