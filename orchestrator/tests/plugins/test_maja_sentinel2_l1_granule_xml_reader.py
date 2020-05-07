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
orchestrator.tests.plugins.test_maja_sentinel2_l1_granule_xml_reader -- shortdesc

orchestrator.tests.plugins.test_maja_sentinel2_l1_granule_xml_reader is a description

It defines classes_and_methods

###################################################################################################

:copyright: 2019 CNES. All rights reserved.
:license: license

###################################################################################################
"""


import os
import unittest

from orchestrator.tests.settings import A_PRODUCT_S2_L1
from orchestrator.plugins.sentinel2.maja_sentinel2_l1_granule_xml_reader import MajaSentinel2L1GranuleXmlReader


class TestMajaSentinel2GranuleXmlReader(unittest.TestCase):
    """Test class for ClassUndertestName"""

    def setUp(self):
        self.granule_xml = A_PRODUCT_S2_L1.get("granule_xml_fullpath")
        self.assertTrue(os.path.isfile(self.granule_xml))

    def test_object(self):
        """
        Assert the initialization of the object do not fail
        """
        self.maja_oject = MajaSentinel2L1GranuleXmlReader(self.granule_xml)
        self.assertIsNotNone(self.maja_oject)


if __name__ == "__main__":
    unittest.main()
