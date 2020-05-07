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


class OtbResampleType:

    def __init__(self):
        return

    LINEAR = 0
    BCO = 1
    LINEAR_WITH_RADIUS = 2
    FAST_LINEAR = 3
    CLOUD_UNDERSAMPLING_CLA = 4
    CLOUD_UNDERSAMPLING_CLD_ALT = 5


def resample(input_file_path, dtm, output_image, method=None, threshold=None, padradius=None, outarea=None, write_output=True):

    cl_param = "bco"

    if method is not None:
        if method == OtbResampleType.LINEAR:
            cl_param = "linear"
        elif method == OtbResampleType.BCO:
            cl_param = "bco"
        elif method == OtbResampleType.LINEAR_WITH_RADIUS:
            cl_param = "linearradius"
        elif method == OtbResampleType.FAST_LINEAR:
            cl_param = "fastlinear"
        elif method == OtbResampleType.CLOUD_UNDERSAMPLING_CLA:
            cl_param = "cloudcla"
        elif method == OtbResampleType.CLOUD_UNDERSAMPLING_CLD_ALT:
            cl_param = "cloudclalt"
    else:
        cl_param = "bco"

    parameters = {"im": input_file_path,
                  "dtm": dtm,
                  "out": output_image,
                  "interp": cl_param}

    if threshold is not None:
        parameters["threshold"] = threshold

    if outarea is not None:
        parameters["outareasize.x"] = outarea[0]
        parameters["outareasize.y"] = outarea[1]

    if padradius is not None:
        parameters["padradius"] = padradius

    app = OtbAppHandler("Resampling", parameters, write_output)

    return app
