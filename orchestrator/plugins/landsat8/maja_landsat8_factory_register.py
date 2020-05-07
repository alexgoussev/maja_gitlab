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
from orchestrator.plugins.landsat8.maja_landsat8_l1_image_info import MajaLandsat8L1ImageInformations
from orchestrator.plugins.landsat8.maja_landsat8_plugin import MajaLandsat8Plugin
from orchestrator.plugins.landsat8.maja_landsat8_l1_image_file_reader import Landsat8L1ImageFileReader


def register_all():
    FactoryBase.register("L1ImageInformationsBase",
                         MajaLandsat8L1ImageInformations)
    FactoryBase.register("PluginBase",
                         MajaLandsat8Plugin)
    FactoryBase.register("L1ImageReaderBase",
                         Landsat8L1ImageFileReader)


