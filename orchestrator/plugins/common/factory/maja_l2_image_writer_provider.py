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
from orchestrator.plugins.common.factory.factory_base import FactoryBase
from orchestrator.common.logger.maja_logging import configure_logger
from orchestrator.common.maja_exceptions import MajaBusinessException
LOGGER = configure_logger(__name__)


class L2ImageWriterProvider(object):

    @staticmethod
    def create(plugin_name):
        creators = FactoryBase.get_registered("L2ImageWriterBase")
        for crea in creators:
            LOGGER.info("Trying L2 : " + crea.__name__)
            if crea().can_write(plugin_name):
                l2writer = crea()
                return l2writer
        raise MajaBusinessException("No factory to generate L2ImageWriter for " + plugin_name)
