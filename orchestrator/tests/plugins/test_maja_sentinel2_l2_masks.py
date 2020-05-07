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

orchestrator.tests.plugins.test_maja_sentinel2_l1_masks -- shortdesc

orchestrator.tests.plugins.test_maja_sentinel2_l1_masks is a description

It defines classes_and_methods

###################################################################################################

:copyright: 2019 CNES. All rights reserved.
:license: license

###################################################################################################
"""


import os
import unittest

from orchestrator.common.xml_tools import get_root_xml
from orchestrator.tests.settings import A_PRODUCT_S2_L2
from orchestrator.plugins.sentinel2.maja_sentinel2_l2_masks import MajaL2Masks
from ..maja_test_case import MajaTestCase


class TestMajaSentinel2L2Maks(MajaTestCase):
    """Test class for ClassUndertestName"""

    def setUp(self):
        self.main_xml = A_PRODUCT_S2_L2.get("main_xml_fullpath")
        self.root = get_root_xml(self.main_xml, deannotate=True)
        self.product_directory = A_PRODUCT_S2_L2.get("directory")
        self.assertTrue(os.path.isfile(self.main_xml))

    def test_object(self):
        """
        Assert the initialization of the object do not fail
        """
        self.maja_oject = MajaL2Masks(self.root, self.product_directory)
        self.assertIsNotNone(self.maja_oject)

    def test_masks(self):
        """
        Assertion on the extracted angles
        """
        self.maja_oject = MajaL2Masks(self.root, self.product_directory)
        masks_object = self.maja_oject.masks_filepaths

        self.assertEqual(masks_object.get("R1"), A_PRODUCT_S2_L2.get("mask_r1_fullpath"))
        self.assertEqual(masks_object.get("R2"), A_PRODUCT_S2_L2.get("mask_r2_fullpath"))


if __name__ == "__main__":
    unittest.main()
