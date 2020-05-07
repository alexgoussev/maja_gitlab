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

import orchestrator.plugins.sentinel2.maja_sentinel2_factory_register as maja_sentinel2_factory_register
import orchestrator.plugins.sentinel2_muscate.maja_sentinel2_muscate_factory_register as maja_sentinel2_muscate_factory_register
import orchestrator.plugins.venus_muscate.maja_venus_muscate_factory_register as maja_venus_muscate_factory_register
import orchestrator.plugins.landsat8_muscate.maja_landsat8_muscate_factory_register as maja_landsat8_muscate_factory_register
import orchestrator.plugins.landsat8.maja_landsat8_factory_register as maja_landsat8_factory_register
import orchestrator.plugins.venus.maja_venus_factory_register as maja_venus_factory_register


def register_all():
    maja_sentinel2_factory_register.register_all()
    maja_sentinel2_muscate_factory_register.register_all()
    maja_venus_muscate_factory_register.register_all()
    maja_landsat8_muscate_factory_register.register_all()
    maja_landsat8_factory_register.register_all()
    maja_venus_factory_register.register_all()
