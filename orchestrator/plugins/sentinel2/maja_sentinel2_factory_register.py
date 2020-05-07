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
from orchestrator.plugins.sentinel2.maja_sentinel2_l1_image_file_reader import Sentinel2L1ImageFileReader
from orchestrator.plugins.sentinel2.maja_sentinel2_l1_image_info import MajaSentinel2L1ImageInformations
from orchestrator.plugins.sentinel2.maja_sentinel2_l2_image_writer import MajaSentinel2L2ImageWriter
from orchestrator.plugins.sentinel2.maja_sentinel2_l2_image_reader import MajaSentinel2L2ImageReader
from orchestrator.plugins.sentinel2.maja_sentinel2_plugin import MajaSentinel2Plugin
from orchestrator.plugins.sentinel2.maja_sentinel2_l2_header_writer import MajaSentinel2L2HeaderWriter


def register_all():
    FactoryBase.register("L1ImageInformationsBase", MajaSentinel2L1ImageInformations)
    FactoryBase.register("L1ImageReaderBase",
                         Sentinel2L1ImageFileReader)
    FactoryBase.register("PluginBase",
                         MajaSentinel2Plugin)
    FactoryBase.register("L2ImageWriterBase",
                         MajaSentinel2L2ImageWriter)
    FactoryBase.register("L2ImageReaderBase", MajaSentinel2L2ImageReader)
    FactoryBase.register("L2HeaderWriterBase", MajaSentinel2L2HeaderWriter)
