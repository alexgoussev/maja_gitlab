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

orchestrator.plugins.sentinel2.maja_sentinel2_l2_main_xml_reader -- shortdesc

orchestrator.plugins.sentinel2.maja_sentinel2_l2_main_xml_reader is a description

It defines classes_and_methods

###################################################################################################

:copyright: 2019 CNES. All rights reserved.
:license: license

###################################################################################################
"""

from orchestrator.common.xml_tools import get_root_xml
from .maja_sentinel2_l2_angles import MajaL2Angles


class MajaSentinel2L2MainXmlReader(object):
    """
    classdocs
    """

    def __init__(self, main_xml_file):
        """
        Constructor
        """
        self.root = get_root_xml(main_xml_file, deannotate=True)
        self.angles = MajaL2Angles(self.root)
