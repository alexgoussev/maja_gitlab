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
from orchestrator.common.logger.maja_logging import configure_logger
LOGGER = configure_logger(__name__)
from orchestrator.plugins.common.factory.factory_base import FactoryBase
import os
from orchestrator.plugins.sentinel2.maja_sentinel2_l1_image_file_reader import Sentinel2L1ImageFileReader
from orchestrator.plugins.sentinel2.maja_sentinel2_plugin import MajaSentinel2Plugin
from orchestrator.common.dem.dem_base import DEMBase
import orchestrator.common.gipp_utils as gipp_utils


def test(argv):
    in_dir = argv[1]
    dem_filename = argv[2]
    working_dir = argv[3]

    l_ListOfTOAImageFileNames = [os.path.join(in_dir, 'TOAReader_0.tif'),
                                 os.path.join(in_dir, 'TOAReader_1.tif'),
                                 os.path.join(in_dir, 'TOAReader_2.tif'),
                                 os.path.join(in_dir, 'TOAReader_3.tif'),
                                 os.path.join(in_dir, 'TOAReader_4.tif'),
                                 os.path.join(in_dir, 'TOAReader_5.tif'),
                                 os.path.join(in_dir, 'TOAReader_6.tif'),
                                 os.path.join(in_dir, 'TOAReader_7.tif'),
                                 os.path.join(in_dir, 'TOAReader_8.tif'),
                                 os.path.join(in_dir, 'TOAReader_9.tif'),
                                 os.path.join(in_dir, 'TOAReader_10.tif'),
                                 os.path.join(in_dir, 'TOAReader_11.tif'),
                                 os.path.join(in_dir, 'TOAReader_12.tif')
                                 ]

    maja_object = Sentinel2L1ImageFileReader()
    maja_object._toa_scalar_list = l_ListOfTOAImageFileNames
    maja_object._plugin = MajaSentinel2Plugin()


    dem = DEMBase()
    dem.initialize(dem_filename, working_dir, False)

    maja_object._dem = dem
    maja_object.generate_edg_images_from_toa(l_ListOfTOAImageFileNames, working_dir)