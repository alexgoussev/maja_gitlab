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
orchestrator.cots.otb.otb_cots_manager -- shortdesc

orchestrator.cots.otb.otb_cots_manager is a description

It defines classes_and_methods

###################################################################################################

:copyright: 2019 CNES. All rights reserved.
:license: license

###################################################################################################
"""

from orchestrator.common.logger.maja_logging import configure_logger
import otbApplication
LOGGER = configure_logger(__name__)


class OtbPipelineManager(object):
    """
    This class allow to manage launched apps in a pipeline.

    """

    def __init__(self):
        """
        Init to have constant values
        """
        self.otb_app_coarse_resolution = []
        
    def __del__(self):
        self.free_otb_app()

    def add_otb_app(self, otb_app):
        self.otb_app_coarse_resolution.append(otb_app)

    def free_otb_app(self):
        for otb_app in self.otb_app_coarse_resolution:
            if otb_app.get_app_name() is not None :
                LOGGER.debug("Removing "+otb_app.get_app_name())
                self.otb_app_coarse_resolution.remove(otb_app)
                del (otb_app)
            else:
                self.otb_app_coarse_resolution.remove(otb_app)
        self.otb_app_coarse_resolution = []

    def get_last_app(self):
        return self.otb_app_coarse_resolution[-1]
