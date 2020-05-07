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
from orchestrator.plugins.common.earth_explorer.maja_earth_explorer_l2_image_file_reader import EarthExplorerL2ImageFileReader
from orchestrator.plugins.sentinel2.maja_sentinel2_plugin import MajaSentinel2Plugin


class MajaSentinel2L2ImageReader(EarthExplorerL2ImageFileReader):

    def __init__(self):
        super(MajaSentinel2L2ImageReader, self).__init__()
        self.plugin = MajaSentinel2Plugin()

    def detect_l2_products(self, dir, product_list):
        self.earth_explorer_detect_l2_products(dir, product_list, self.plugin)

    def can_read(self, product_filename):
        return self.can_read_with_plugin_base(product_filename, self.plugin)

    def read(self, product_filename, app_handler, enable_public_data):
        self.read_with_plugin_base(product_filename, enable_public_data, app_handler, self.plugin)

    def read_info(self, product_filename, enable_public_data):
        self.read_info_with_plugin_base(product_filename, enable_public_data, self.plugin)
