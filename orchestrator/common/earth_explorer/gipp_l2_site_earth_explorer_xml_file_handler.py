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

orchestrator.common.earth_explorer.gipp_l2_comm_earth_explorer_xml_file_handler -- shortdesc

orchestrator.common.earth_explorer.gipp_l2_comm_earth_explorer_xml_file_handler is a description

It defines classes_and_methods

###################################################################################################

:copyright: 2019 CNES. All rights reserved.
:license: license

###################################################################################################
"""

from orchestrator.common.maja_exceptions import MajaDriverException
from orchestrator.common.xml_tools import get_root_xml, get_only_value

GIPP_SITE_HANDLER_XPATH = {
    "DarkPixelThreshold": "/Earth_Explorer_File/Data_Block/AOT_Estimation/Dark_Pixel_Threshold/text()",
    "DarkestPixelSurfaceReflectance": "/Earth_Explorer_File/Data_Block/AOT_Estimation/" +
                                      "Darkest_Pixel_Surface_Reflectance/text()"}


class GippL2SITEEarthExplorerXMLFileHandler(object):

    def __init__(self, gipp_filename):
        self.gipp_filename = gipp_filename
        self.root = get_root_xml(self.gipp_filename, deannotate=True)
        self.l2_site_values = {}

        for key, value in list(GIPP_SITE_HANDLER_XPATH.items()):
            result = get_only_value(self.root, value)
            if result is not None:
                self.l2_site_values[key] = result

    def get_value(self, key, check=False):
        if key in self.l2_site_values:
            return self.l2_site_values[key]
        else:
            if check:
                return None
            else:
                raise MajaDriverException("No " + key + " in L2SITE dictionnary")


if __name__ == '__main__':
    pass
