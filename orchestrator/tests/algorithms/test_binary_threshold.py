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

orchestrator.tests.algorithm.test_binary_threshold -- shortdesc

orchestrator.tests.algorithm.test_binary_threshold is a description

It defines classes_and_methods

###################################################################################################

:copyright: 2019 CNES. All rights reserved.
:license: license

###################################################################################################
"""
import unittest

from ..settings import QB_1_ORTHO_EXTRACT
from ..maja_test_case import MajaTestCase
from orchestrator.cots.otb.algorithms.otb_binary_threshold import binary_threshold
from orchestrator.common.directory_manager import get_working_file


class TestBinaryThreshold(MajaTestCase):
    """Test class for ClassUndertestName"""

    def setUp(self):
        self.image = QB_1_ORTHO_EXTRACT.get("image_fullpath", None)

    def test_algo(self):
        """
        Test the initialization of the object
        """
        binary_threshold(input_image=self.image,
                         lower_threshold=25,
                         upper_threshold=100,
                         inside_value=1,
                         outside_value=0,
                         output_image=get_working_file("TestAlgoBinaryThreshold",
                                                       working_directory=self.working_test_directory))


if __name__ == "__main__":
    unittest.main()
