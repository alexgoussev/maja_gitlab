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
from orchestrator.cots.otb.otb_app_handler import OtbAppHandler


def one_band_equal_value(image, output_image, threshold, equal_value=1, outside_value=0, write_output=True):
    """
    :param image:
    :param output_image:
    :param threshold:
    :param equal_value:
    :param outside_value
    :param write_output:
    :return:
    """
    parameters = {"im": image,
                  "thresholdvalue": threshold,
                  "equalvalue": equal_value,
                  "outsidevalue": outside_value,
                  "out": output_image}

    app = OtbAppHandler("OneBandEqualThreshold", parameters, write_output)

    return app
