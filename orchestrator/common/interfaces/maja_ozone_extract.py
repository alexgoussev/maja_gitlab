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

orchestrator.common.interfaces.maja_xml_input -- shortdesc

orchestrator.common.interfaces.maja_xml_input is a description

It defines classes_and_methods

###################################################################################################

:copyright: 2019 CNES. All rights reserved.
:license: license

###################################################################################################
"""
import os
from orchestrator.cots.otb.otb_app_handler import OtbAppHandler
from orchestrator.common.logger.maja_logging import configure_logger
LOGGER = configure_logger(__name__)


def get_ozone_amount(ozone_filename, corner):
    ozoneamount = 0.0
    l_gribfilename = os.path.splitext(ozone_filename)[0] + ".DBL.BIN"
    if os.path.exists(l_gribfilename):
        LOGGER.info("Reading meteo file : " + l_gribfilename)
        param_app = {"im": l_gribfilename + "?&resol=7",
                     "lat": corner.latitude,
                     "lon": corner.longitude
                     }
        app = OtbAppHandler("OzoneExtractor", param_app)
        ozoneamount = app.getoutput()["ozone"]
        # ------------------------------------------------------------------------------------
        # Conversion from Kg/m2 to cm.atm (Dobson Unit/1000)
        # Note:
        # - 1 kg[O3]/m2 = 1/2.1416 x 10-5 = 46694.06 dobson
        # - 1 cm.atm = 1 jacobson = 1000 dobson
        # In the ozone file, the value is in 1 kg[O3]/m2.
        # The ozone value computed is in Jacobson (cm.atm/m2)
        l_dobsonconversionfactor = 46.694
        ozoneamount = ozoneamount * l_dobsonconversionfactor
        LOGGER.debug(
            "OzoneAmountValue patched with the following Dobson conversion factor " +
            str(l_dobsonconversionfactor) +
            ".")
    return ozoneamount
