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


def band_math_or(input_file_path_list, output_image, write_output=True):

    exp = "im1b1"
    # ignore first one
    for i in range(2, len(input_file_path_list) + 1):
        exp += " || im{}b1".format(i)

    return band_math_mask(input_file_path_list, exp, output_image, write_output)


def band_math(input_file_path_list, exp, output_image, write_output=True):

    parameters = {"exp": exp,
                  "il": input_file_path_list,
                  "out": output_image}

    app = OtbAppHandler("BandMath", parameters, write_output)

    return app


def band_math_mask(input_file_path_list, exp, output_image, write_output=True):
    parameters = {"exp": exp,
                  "il": input_file_path_list,
                  "out": output_image}

    app = OtbAppHandler("BandMath", parameters, write_output)

    return app
