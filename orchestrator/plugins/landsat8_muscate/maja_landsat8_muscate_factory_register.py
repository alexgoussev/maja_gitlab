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

orchestrator.plugins.sentinel2.maja_sentinel2_l1_angles -- shortdesc

orchestrator.plugins.sentinel2.maja_sentinel2_l1_angles is a description

It defines classes_and_methods

###################################################################################################

:copyright: 2019 CNES. All rights reserved.
:license: license

###################################################################################################
"""
from orchestrator.plugins.common.factory.factory_base import FactoryBase
from orchestrator.plugins.landsat8_muscate.maja_landsat8_muscate_l1_image_info import MajaLandsat8MuscateL1ImageInformations
from orchestrator.plugins.landsat8_muscate.maja_landsat8_muscate_l1_image_file_reader import Landsat8MuscateL1ImageFileReader
from orchestrator.plugins.landsat8_muscate.maja_landsat8_muscate_l2_image_writer import MajaLandsat8MuscateL2ImageWriter
from orchestrator.plugins.landsat8_muscate.maja_landsat8_muscate_l2_header_writer import MajaLandsat8MuscateL2HeaderWriter
from orchestrator.plugins.landsat8_muscate.maja_landsat8_muscate_l2_image_reader import MajaLandsat8MuscateL2ImageReader
from orchestrator.plugins.landsat8_muscate.maja_landsat8_muscate_plugin import MajaLandsat8MuscatePlugin


def register_all():
    FactoryBase.register("L1ImageInformationsBase", MajaLandsat8MuscateL1ImageInformations)
    FactoryBase.register("PluginBase",
                         MajaLandsat8MuscatePlugin)
    FactoryBase.register("L1ImageReaderBase",
                         Landsat8MuscateL1ImageFileReader)
    FactoryBase.register("L2ImageWriterBase",
                         MajaLandsat8MuscateL2ImageWriter)
    FactoryBase.register("L2HeaderWriterBase", MajaLandsat8MuscateL2HeaderWriter)
    FactoryBase.register("L2ImageReaderBase", MajaLandsat8MuscateL2ImageReader)
