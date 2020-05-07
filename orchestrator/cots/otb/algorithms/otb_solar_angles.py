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
orchestrator.cots.otb.otb_solar_angles -- shortdesc

orchestrator.cots.otb.otb_solar_angles is a description

It defines classes_and_methods

###################################################################################################

:copyright: 2019 CNES. All rights reserved.
:license: license

###################################################################################################
"""

from orchestrator.cots.otb.otb_app_handler import OtbAppHandler
from orchestrator.common.logger.maja_logging import configure_logger
from orchestrator.common.maja_exceptions import MajaNotYetImplemented

LOGGER = configure_logger(__name__)


def solar_angle(solar_angle_image, sol1_height, sol_href, output_image, sol2_in=None, sol2_height=None,
                write_output=True):
    # test about input and raise MajaNotYetImplemented is case of sol2 case
    if sol2_in is not None or sol2_height is not None:
        raise MajaNotYetImplemented()

    parameters = {"sol1.in": solar_angle_image,
                  "sol1.h": sol1_height,
                  "solhref": sol_href,
                  "sol": output_image}

    app = OtbAppHandler("SolarAngle", parameters, write_output)

    return app
