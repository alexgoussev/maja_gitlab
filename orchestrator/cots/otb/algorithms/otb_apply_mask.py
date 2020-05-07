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


def apply_mask(image, mask, nodataval, output_image, write_output=True):
    """
    :param image:
    :param mask:
    :param nodataval:
    :param output_image:
    :param write_output:
    :return:
    """
    parameters = {"in": image,
                  "mode": "apply",
                  "mode.apply.mask": mask,
                  "mode.apply.ndval": nodataval,
                  "out": output_image}

    app = OtbAppHandler("ManageNoData", parameters, write_output)

    return app
