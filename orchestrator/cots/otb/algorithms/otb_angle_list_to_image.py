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
orchestrator.cots.otb.otb_angle_list_to_image -- shortdesc

orchestrator.cots.otb.otb_angle_list_to_image is a description

It defines classes_and_methods

###################################################################################################

:copyright: 2019 CNES. All rights reserved.
:license: license

###################################################################################################
"""


from orchestrator.cots.otb.otb_app_handler import OtbAppHandler
from orchestrator.common.logger.maja_logging import configure_logger

LOGGER = configure_logger(__name__)


def angle_list_to_image(input_reference_image, file_angles, output_image, extrapolation=None, write_output=True):

    parameters = {"dtm": input_reference_image,
                  "angles": file_angles,
                  "out": output_image}

    if extrapolation is not None:
        parameters["extrapol"] = extrapolation

    app = OtbAppHandler("AngleListToImage", parameters, write_output)

    return app
