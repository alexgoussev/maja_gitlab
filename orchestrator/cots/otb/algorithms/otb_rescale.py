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


def rescale_intensity(input_file_path, out_min, out_max, output_image, inmin=None, inmax=None, write_output=True):

    parameters = {"in": input_file_path,
                  "outmin": out_min,
                  "outmax": out_max,
                  "out": output_image,
                  }
    if inmax is not None:
        parameters["inmax"] = inmax

    if inmin is not None:
        parameters["inmin"] = inmin

    app = OtbAppHandler("RescaleIntensity", parameters, write_output)

    return app