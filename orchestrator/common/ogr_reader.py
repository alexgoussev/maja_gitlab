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

orchestrator.processor.base_processor -- shortdesc

orchestrator.processor.base_processor is the base of all processors

It defines method mandatory for a processor

###################################################################################################

:copyright: 2019 CNES. All rights reserved.
:license: license

###################################################################################################
"""
from osgeo import ogr
from orchestrator.common.maja_exceptions import MajaOgrException


class OGRReader:

    def __init__(self, shapefile, driver='GML'):
        self.shapefile = shapefile
        self.driver = ogr.GetDriverByName(driver)
        self.ds = None
        self.read()

    def read(self):
        """
        Open the shapefile and read content
        :return:
        """
        self.ds = self.driver.Open(self.shapefile, 0)

        if self.ds is None:
            raise MajaOgrException("Could not open {}".format(self.shapefile))

    def get_feature_count(self):
        layer = self.ds.GetLayer()
        feature_count = layer.GetFeatureCount()
        return feature_count
