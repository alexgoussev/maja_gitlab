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
from orchestrator.common.logger.maja_logging import configure_logger
LOGGER = configure_logger(__name__)

class FactoryBase(object):
    registry = dict()

    @staticmethod
    def register(subclass, cls):
        if subclass in FactoryBase.registry:
            FactoryBase.registry[subclass].append(cls)
        else:
            FactoryBase.registry[subclass] = [cls]
        return cls

    @staticmethod
    def get_registered(subclass):
        if subclass in FactoryBase.registry:
            return FactoryBase.registry[subclass]
        else:
            return list()
