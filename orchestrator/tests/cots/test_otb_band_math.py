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

orchestrator.tests.cots.test_otb_band_math -- shortdesc

orchestrator.tests.cots.test_otb_band_math is a description

It defines classes_and_methods

###################################################################################################

:copyright: 2019 CNES. All rights reserved.
:license: license

###################################################################################################
"""

import os
import unittest

from orchestrator.cots.otb.algorithms.otb_band_math import band_math
from orchestrator.tests.settings import QB_1_ORTHO_EXTRACT
from orchestrator.tests.maja_test_case import MajaTestCase


class TestOtbCotsBandMath(MajaTestCase):
    """Test class for ClassUndertestName"""

    def setUp(self):
        self.input_image_list = [QB_1_ORTHO_EXTRACT.get("image_fullpath", None)]
        self.expression = 'im1b1*im1b1'
        self.type_output = 'uint16'

    def test_otb_band_math_run(self):
        """
        Test the initialization of the object
        """
        expected_output = os.path.join(self.working_test_directory,
                                       "output_band_math.tif")
        rok_otb_cots = band_math(self.input_image_list, self.expression, expected_output)

        self.assertIsNotNone(rok_otb_cots)

        self.assertTrue(os.path.exists(expected_output))


if __name__ == "__main__":
    unittest.main()
