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


def constant_image(dtm, value, output_image, write_output=True):
    """

    :param output_image:
    :param dtm:
    :param value:
    :param write_output:
    :return:
    """
    parameters = {"value": value,
                  "dtm": dtm,
                  "out": output_image}

    app = OtbAppHandler("ConstantImage", parameters, write_output)

    return app
