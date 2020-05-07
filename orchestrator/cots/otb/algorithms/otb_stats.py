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


def stats(input_file_path, exclude_value=None, input_mask=None, mask_foreground=None, write_output=True):

    param_stats = {"im": input_file_path}

    if input_mask is not None:
        param_stats["mask"] = input_mask
    if mask_foreground is not None:
        param_stats["maskforeground"] = mask_foreground
    if exclude_value is not None:
        param_stats["exclude"] = exclude_value

    app = OtbAppHandler("Stats", param_stats, write_output)

    return app
