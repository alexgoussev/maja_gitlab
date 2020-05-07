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
from orchestrator.common.maja_utils import get_test_mode
from orchestrator.common.logger.maja_logging import configure_logger

LOGGER = configure_logger(__name__)


def extract_roi(input_file_path, channels, output_image, write_output=True):

    parameters = {"in": input_file_path,
                  "cl": ["Channel" + str(idx + 1) for idx in channels],
                  "out": output_image}
    if get_test_mode():
        parameters.pop("cl")
    app = OtbAppHandler("ExtractROI", parameters, write_output)

    return app
