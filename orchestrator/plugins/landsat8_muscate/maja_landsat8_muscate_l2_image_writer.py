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

orchestrator.plugins.maja_dataset -- shortdesc

orchestrator.plugins.maja_dataset is a description

It defines classes_and_methods

###################################################################################################

:copyright: 2019 CNES. All rights reserved.
:license: license

###################################################################################################
"""
from orchestrator.plugins.common.muscate.maja_muscate_l2_image_writer import MajaMuscateL2ImageWriter
from orchestrator.plugins.landsat8_muscate.maja_landsat8_muscate_plugin import MajaLandsat8MuscatePlugin
from orchestrator.common.logger.maja_logging import configure_logger
LOGGER = configure_logger(__name__)


class MajaLandsat8MuscateL2ImageWriter(MajaMuscateL2ImageWriter):

    def __init__(self):
        super(MajaLandsat8MuscateL2ImageWriter, self).__init__()
        self.plugin = MajaLandsat8MuscatePlugin()

    def can_write(self, plugin_name):
        return plugin_name == "LANDSAT8_MUSCATE" or plugin_name == "LANDSAT8"
