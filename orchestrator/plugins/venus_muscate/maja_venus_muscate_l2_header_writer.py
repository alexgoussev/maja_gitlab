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
from orchestrator.common.muscate.muscate_xml_file_handler import MuscateXMLFileHandler
import orchestrator.common.xml_tools as xml_tools
from orchestrator.cots.otb.otb_app_handler import OtbAppHandler
from orchestrator.plugins.common.muscate.maja_muscate_l2_header_writer import MajaMuscateL2HeaderWriter
from orchestrator.plugins.venus_muscate.maja_venus_muscate_plugin import MajaVenusMuscatePlugin
from orchestrator.common.logger.maja_logging import configure_logger
from orchestrator.common.maja_exceptions import MajaExceptionPluginMuscate
import math
LOGGER = configure_logger(__name__)


class MajaVenusMuscateL2HeaderWriter(MajaMuscateL2HeaderWriter):

    def __init__(self):
        super(MajaVenusMuscateL2HeaderWriter, self).__init__()
        self.plugin = MajaVenusMuscatePlugin()

    def create(self, plugin_name, app_handler):
        if plugin_name == "VENUS_MUSCATE" or plugin_name == "VENUS":
            self.apphandler = app_handler
            return True
        else:
            return False
