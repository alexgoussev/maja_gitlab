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
orchestrator.tests.cots.test_otb_angle_list_to_image -- shortdesc

orchestrator.tests.cots.test_otb_angle_list_to_image is a description

It defines classes_and_methods

###################################################################################################

:copyright: 2019 CNES. All rights reserved.
:license: license

###################################################################################################
"""


import os

from orchestrator.cots.otb.algorithms.otb_angle_list_to_image import angle_list_to_image
from orchestrator.tests.settings import QB_1_ORTHO_EXTRACT, INTERNAL_XML_FILES
from orchestrator.tests.maja_test_case import MajaTestCase


class TestOtbCotsAngleListToImage(MajaTestCase):
    """Test class for ClassUndertestName"""

    def setUp(self):
        self.input_reference_image = QB_1_ORTHO_EXTRACT.get("image_fullpath", None)
        self.input_angle_xml_file = INTERNAL_XML_FILES.get("angles_fullpath", None)

    def test_otb_angle_list_to_image_run(self):
        """
        Test the initialization of the object
        """
        expected_output = os.path.join(self.working_test_directory,
                                       "output_angle_list_to_image.tif")
        rok_otb_cots = angle_list_to_image(self.input_reference_image, self.input_angle_xml_file, expected_output)

        self.assertIsNotNone(rok_otb_cots)

        self.assertTrue(os.path.exists(expected_output))
