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
from orchestrator.plugins.venus.maja_venus_l1_image_info import MajaVenusL1ImageInformations
from orchestrator.plugins.venus.maja_venus_plugin import MajaVenusPlugin
from orchestrator.plugins.venus.maja_venus_l1_image_file_reader import VenusL1ImageFileReader


def register_all():
    FactoryBase.register("PluginBase",
                         MajaVenusPlugin)
    FactoryBase.register("L1ImageInformationsBase",
                         MajaVenusL1ImageInformations)

    FactoryBase.register("L1ImageReaderBase",
                         VenusL1ImageFileReader)


