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

orchestrator.tests.cots.test_otb_solar_angle -- shortdesc

orchestrator.tests.cots.test_otb_solar_angle is a description

It defines classes_and_methods

###################################################################################################

:copyright: 2019 CNES. All rights reserved.
:license: license

###################################################################################################
"""


import os
import unittest

from orchestrator.cots.otb.algorithms.otb_solar_angles import solar_angle
from orchestrator.tests.settings import QB_1_ORTHO_EXTRACT
from orchestrator.tests.maja_test_case import MajaTestCase


class TestOtbCotsSolarAngle(MajaTestCase):

    def setUp(self):
        self.input_angles = QB_1_ORTHO_EXTRACT.get("image_fullpath", None)
        self.sol1_height = 2
        self.sol_href = 1

    def test_otb_angle_list_to_image_run(self):
        """
        Test the initialization of the object
        """
        expected_output = os.path.join(self.working_test_directory,
                                       "output_angle_list_to_image.tif")

        rok_otb_cots = solar_angle(
            self.input_angles,
            sol1_height=self.sol1_height,
            sol_href=self.sol_href,
            output_image=expected_output)

        self.assertIsNotNone(rok_otb_cots)
        self.assertTrue(os.path.exists(expected_output))


if __name__ == "__main__":
    unittest.main()
