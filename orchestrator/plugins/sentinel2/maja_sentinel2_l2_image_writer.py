# -*- coding: utf-8 -*-
"""
###################################################################################################
#
#                        o     o
#                        oo   oo   oo        o   oo        ,-.
#                        o o o o  o  o       o  o  o       \_/
#                        o  o  o o    o      o o    o     |||)<
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
from orchestrator.plugins.common.earth_explorer.maja_earth_explorer_l2_image_file_writer import \
    EarthExplorerL2ImageFileWriter


class MajaSentinel2L2ImageWriter(EarthExplorerL2ImageFileWriter):

    def __init__(self):
        super(MajaSentinel2L2ImageWriter, self).__init__()

    def can_write(self, plugin_name):
        return plugin_name == "SENTINEL2"
