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
from orchestrator.plugins.common.muscate.maja_muscate_l2_header_writer import MajaMuscateL2HeaderWriter
from orchestrator.plugins.sentinel2_muscate.maja_sentinel2_muscate_plugin import MajaSentinel2MuscatePlugin
from orchestrator.common.logger.maja_logging import configure_logger
LOGGER = configure_logger(__name__)


class MajaSentinel2MuscateL2HeaderWriter(MajaMuscateL2HeaderWriter):

    def __init__(self):
        super(MajaSentinel2MuscateL2HeaderWriter, self).__init__()
        self.plugin = MajaSentinel2MuscatePlugin()

    def create(self, plugin_name, app_handler):
        if plugin_name == "SENTINEL2_MUSCATE" or plugin_name == "SENTINEL2":
            self.apphandler = app_handler
            return True
        else:
            return False
