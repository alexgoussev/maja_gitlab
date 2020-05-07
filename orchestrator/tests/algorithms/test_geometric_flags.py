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

orchestrator.tests.algorithms.test_geometric_flags -- shortdesc

orchestrator.tests.algorithms.test_geometric_flags is a description

It defines classes_and_methods

###################################################################################################

:copyright: 2019 CNES. All rights reserved.
:license: license

###################################################################################################
"""


import unittest
from orchestrator.tests.maja_test_case import MajaTestCase
from orchestrator.algorithms.geometric_flags.geometric_flags import GeometricFlagsGenerator


class TestGeometricFlagsGenerator(MajaTestCase):
    """Test class for ClassUndertestName"""

    def test_object(self):
        maja_object = GeometricFlagsGenerator(1, [1], 1, [1], 0.5, 0.5)
        self.assertIsNotNone(maja_object)

    def test_sunglint_distance(self):
        maja_object = GeometricFlagsGenerator(1, [1], 1, [1], 0.5, 0.5)
        self.assertIsNotNone(maja_object.sunglint_distance)

    def test_hot_spot_distance(self):
        maja_object = GeometricFlagsGenerator(1, [1], 1, [1], 0.5, 0.5)
        self.assertIsNotNone(maja_object.hot_spot_distance)

    def test_is_sunglint(self):
        maja_object = GeometricFlagsGenerator(1, [1], 1, [1], 0.5, 0.5)
        self.assertIsNotNone(maja_object.is_sunglint())

    def test_is_hot_spot(self):
        maja_object = GeometricFlagsGenerator(1, [1], 1, [1], 0.5, 0.5)
        self.assertIsNotNone(maja_object.is_hotspot())


if __name__ == "__main__":
    unittest.main()
