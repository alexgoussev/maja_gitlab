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


import os

from orchestrator.tests.settings import GIPP_L2
from orchestrator.common.earth_explorer.gipp_l2_comm_earth_explorer_xml_file_handler import GippL2COMMEarthExplorerXMLFileHandler
from orchestrator.tests.maja_test_case import MajaTestCase


class TestMajaSentinel2L1Angles(MajaTestCase):
    """Test class for ClassUndertestName"""

    def setUp(self):
        self.gipp_l2com = GIPP_L2.get("gipp_l2_comm_fullpath")
        self.assertTrue(os.path.isfile(self.gipp_l2com))

    def test_object(self):
        """
        Assert the initialization of the object do not fail
        """
        self.maja_oject = GippL2COMMEarthExplorerXMLFileHandler(self.gipp_l2com)
        self.assertIsNotNone(self.maja_oject)
        self.assertIsNotNone(self.maja_oject.l2_comm_values)

    def test_some_values(self):
        """
        Assertion on the extracted angles
        """
        self.maja_oject = GippL2COMMEarthExplorerXMLFileHandler(self.gipp_l2com)
        self.assertEqual(self.maja_oject.l2_comm_values.get("GIP_L2COMM_Mission"), "SENTINEL-2A")


#         self.assertEqual(sun_angles_object.sun_angles_mean.get("sun_zenith_angle"),
#                          A_PRODUCT_S2_L1.get("granule_solar_angles").get("sun_zenith_angle"))
#         self.assertEqual(sun_angles_object.sun_angles_mean.get("sun_azimuth_angle"),
#                          A_PRODUCT_S2_L1.get("granule_solar_angles").get("sun_azimuth_angle"))
#
#         self.assertEqual(len(sun_angles_object.zenith_angle_list_string_values), 23)
#
# #     def test_sun_angles_as_np_array(self):
# #         self.assertEqual(len(sun_angles_object.sun_angles_zenith[0]), 23)
