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


class L1ImageReaderProvider(object):

    @staticmethod
    def create(plugin_name, product_info, app_handler, l2comm, dem, mode):
        creators = FactoryBase.get_registered("L1ImageReaderBase")
        for crea in creators:
            LOGGER.info("Trying : " + crea.__name__)
            if crea().can_read(plugin_name):
                l1reader = crea()
                l1reader.read(product_info, app_handler, l2comm, dem, mode)
                return l1reader
        raise MajaBusinessException("No factory to handle " + product_info.ProductFileName)
