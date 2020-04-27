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
from orchestrator.cots.otb.algorithms.otb_band_math import band_math_mask
from orchestrator.cots.otb.otb_app_handler import OtbAppHandler
from orchestrator.common.maja_exceptions import MajaProcessingError


def binary_threshold(input_image, inside_value, outside_value,
                     output_image, lower_threshold=None, upper_threshold=None,
                     write_output=True):
    """

    :param input_image:
    :param lower_threshold:
    :param upper_threshold:
    :param inside_value:
    :param outside_value:
    :param output_image:
    :param write_output:
    :return:
    """
    if lower_threshold is None and upper_threshold is None:
        raise MajaProcessingError("Error, no threshold given")

    if lower_threshold is None:
        expression = "im1b1<{up}?{in_v}:{out_v}".format(up=upper_threshold, in_v=inside_value, out_v=outside_value)
        return band_math_mask([input_image], expression, output_image=output_image, write_output=write_output)
    elif upper_threshold is None:
        parameters = {"threshold": lower_threshold,
                      "abovevalue": inside_value,
                      "undervalue": outside_value,
                      "im": input_image,
                      "out": output_image}
        return OtbAppHandler("ThresholdImage", parameters, write_output)
    else:
        expression = "(im1b1>{low}&&im1b1<{up})?{in_v}:{out_v}".format(low=lower_threshold, up=upper_threshold,
                                                                       in_v=inside_value, out_v=outside_value)
        return band_math_mask([input_image], expression, output_image=output_image, write_output=write_output)
