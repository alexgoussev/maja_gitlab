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
from orchestrator.common.maja_exceptions import MajaExceptionPluginBase

LOGGER = configure_logger(__name__)


class MAJAPluginProvider(object):

    @staticmethod
    def create(plugin_name, app_handler):
        creators = FactoryBase.get_registered("PluginBase")
        for crea in creators:
            LOGGER.info("Trying : " + crea.__name__ + " for plugin " + plugin_name)
            if crea().is_valid(plugin_name):
                plugin = crea()
                plugin.initialize(app_handler)
                return plugin
        raise MajaExceptionPluginBase("No factory to create plugin for " + plugin_name)

    @staticmethod
    def create_with_unique_sat(sat_name, app_handler):
        creators = FactoryBase.get_registered("PluginBase")
        for crea in creators:
            LOGGER.info("Trying : " + crea.__name__ + " for satellite " + sat_name)
            if crea().is_valid_with_unique_satellite(sat_name):
                plugin = crea()
                plugin.initialize(app_handler)
                return plugin
        raise MajaExceptionPluginBase("No factory to create plugin for sat " + sat_name)

    @staticmethod
    def auto_tm(plugin_name):
        if not "MUSCATE" in plugin_name:
            return plugin_name + "_MUSCATE"
        return plugin_name
