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
from orchestrator.tests.settings import A_PRODUCT_S2_L1
from orchestrator.plugins.sentinel2.maja_sentinel2_l1_masks import MajaL1Masks
from ..maja_test_case import MajaTestCase


class TestMajaSentinel2L1Maks(MajaTestCase):
    """Test class for ClassUndertestName"""

    def setUp(self):
        self.granule_xml = A_PRODUCT_S2_L1.get("granule_xml_fullpath")
        self.product_directory = A_PRODUCT_S2_L1.get("directory")
        self.root = get_root_xml(self.granule_xml)
        self.nss = self.root.nsmap
        self.assertTrue(os.path.isfile(self.granule_xml))

    def test_object(self):
        """
        Assert the initialization of the object do not fail
        """
        self.maja_oject = MajaL1Masks(self.root, self.product_directory, self.nss)
        self.assertIsNotNone(self.maja_oject)

    def test_masks(self):
        """
        Assertion on the extracted angles
        """
        self.maja_oject = MajaL1Masks(self.root, self.product_directory, self.nss)
        masks_object = self.maja_oject.masks_filepaths

        LOGGER.debug("...........", masks_object.get("MSK_DEFECT"))

        self.assertEqual(masks_object.get("MSK_DEFECT").get('12'), A_PRODUCT_S2_L1.get("mask_defect_12_fullpath"))
        self.assertEqual(masks_object.get("MSK_DETFOO").get('0'), A_PRODUCT_S2_L1.get("mask_detfoo_0_fullpath"))


if __name__ == "__main__":
    unittest.main()
