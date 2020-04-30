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
from math import pi, tan, sin, cos

from orchestrator.cots.otb.otb_app_handler import OtbAppHandler
from orchestrator.cots.otb.otb_pipeline_manager import OtbPipelineManager


def compute_one_pixel_value(input_value_zen, input_value_azi):
    """

    :param input_value_zen:
    :param input_value_azi:
    :return:
    """
    l_zenrad = input_value_zen * pi
    l_azirad = input_value_azi * pi

    out_pix = ((tan(l_zenrad) * sin(l_azirad)), (tan(l_zenrad) * cos(l_azirad)))
    return out_pix


def assign_zenith_and_azimuth_image_to_grid_to_image(input_image_zen, input_value_azi, output_filename):
    """

    :param output_filename:
    :param input_image_zen:
    :param input_value_azi:
    :return:
    """
    band_math_1 = OtbAppHandler("BandMath", {"il": [input_image_zen, input_value_azi],
                                             "exp": "tan(im1b1)*sin(im2b1)"}, write_output=False)

    pipeline = OtbPipelineManager()
    pipeline.add_otb_app(band_math_1)
    band_math_2 = OtbAppHandler("BandMath", {"il": [input_image_zen, input_value_azi],
                                             "exp": "tan(im1b1)*cos(im2b1)"}, write_output=False)
    pipeline.add_otb_app(band_math_2)

    concat = OtbAppHandler("ConcatenateImages", {"il": [band_math_1.getoutput().get(
        "out"), band_math_2.getoutput().get("out")], "out": output_filename}, write_output=True)
    pipeline.add_otb_app(concat)

    return pipeline
