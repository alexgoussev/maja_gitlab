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

orchestrator.cots.otb.otb_band_math -- shortdesc

orchestrator.cots.otb.otb_band_math is a description

It defines classes_and_methods

###################################################################################################

:copyright: 2019 CNES. All rights reserved.
:license: license

###################################################################################################
"""


from orchestrator.cots.otb.otb_app_handler import OtbAppHandler
from orchestrator.common.logger.maja_logging import configure_logger

LOGGER = configure_logger(__name__)


def clean_pipe(input_file_path):

    parameters = {"in": input_file_path,
                "startx": 0,
                "starty": 0,
                "sizex": 1,
                "sizey": 1,
                "out": "tmp.tif"}
    otb_app = OtbAppHandler("ExtractROI",parameters,write_output=False)
    parameters2 = {"im": otb_app.getoutput().get("out")}
    otb_app2 = OtbAppHandler("Stats", parameters2, write_output=True)
    LOGGER.debug("Stats on clean: "+str(otb_app2.getoutput().get("mean")))
    del otb_app2
    del otb_app
