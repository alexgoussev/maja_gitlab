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

orchestrator.tests.plugins.test_maja_sentinel2_l1_pimage_file_reader -- shortdesc

orchestrator.tests.plugins.test_maja_sentinel2_l1_pimage_file_reader is a description

It defines classes_and_methods

###################################################################################################

:copyright: 2019 CNES. All rights reserved.
:license: license

###################################################################################################
"""

from __future__ import absolute_import

from orchestrator.plugins.common.factory.plugin_activate import register_all
import argparse, sys

import orchestrator.plugins.common.factory.product_utils as product_utils

argParser = argparse.ArgumentParser()
required_arguments = argParser.add_argument_group('required arguments')
required_arguments.add_argument('-i', '--input_dir', required=True,
                                    help='Path to input folder')
required_arguments.add_argument('-t', '--tile_id', required=False,
                                    help='Tile id of the L1 product')
args = argParser.parse_args(sys.argv[1:])

register_all()
product_utils.get_input_l1_image_product(args.input_dir, args.tile_id)

