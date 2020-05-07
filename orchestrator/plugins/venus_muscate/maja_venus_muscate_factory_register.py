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
from orchestrator.plugins.venus_muscate.maja_venus_muscate_l1_image_info import MajaVenusMuscateL1ImageInformations
from orchestrator.plugins.venus_muscate.maja_venus_muscate_l1_image_file_reader import VenusMuscateL1ImageFileReader
from orchestrator.plugins.venus_muscate.maja_venus_muscate_l2_image_writer import MajaVenusMuscateL2ImageWriter
from orchestrator.plugins.venus_muscate.maja_venus_muscate_l2_header_writer import MajaVenusMuscateL2HeaderWriter
from orchestrator.plugins.venus_muscate.maja_venus_muscate_l2_image_reader import MajaVenusMuscateL2ImageReader
from orchestrator.plugins.venus_muscate.maja_venus_muscate_plugin import MajaVenusMuscatePlugin


def register_all():
    FactoryBase.register("L1ImageInformationsBase", MajaVenusMuscateL1ImageInformations)
    FactoryBase.register("PluginBase",
                         MajaVenusMuscatePlugin)
    FactoryBase.register("L1ImageReaderBase",
                         VenusMuscateL1ImageFileReader)
    FactoryBase.register("L2ImageWriterBase",
                         MajaVenusMuscateL2ImageWriter)
    FactoryBase.register("L2HeaderWriterBase", MajaVenusMuscateL2HeaderWriter)
    FactoryBase.register("L2ImageReaderBase", MajaVenusMuscateL2ImageReader)
