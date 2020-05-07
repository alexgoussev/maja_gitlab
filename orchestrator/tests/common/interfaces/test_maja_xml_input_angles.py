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

orchestrator.tests.common.interfaces.test_maja_xml_input_angles -- shortdesc

orchestrator.tests.common.interfaces.test_maja_xml_input_angles is a description

It defines classes_and_methods

###################################################################################################

:copyright: 2019 CNES. All rights reserved.
:license: license

###################################################################################################
"""

import unittest

from orchestrator.common.interfaces.maja_xml_input_angles import MajaInternalXmlInputAngles


class TestMajaInternalXmlInputAngles(unittest.TestCase):
    """Test class for MajaInternalXmlInputAngles"""

    def setUp(self):
        self.values_1 = [1, 2, 3, 4, 5]
        self.values_2 = [6, 7, 8, 9, 10]
        self.row_step = 5000
        self.col_step = 5000
        self.output_filename = "/tmp/internal_angles_test.xml"

    def test_object(self):
        """
        Test the initialisation of the object
        """
        maja_object = MajaInternalXmlInputAngles(self.values_1, self.values_2,
                                                 self.col_step, self.row_step, self.output_filename)
        self.assertIsNotNone(maja_object)

    def test_object_write(self):
        """
        Test the initialisation of the object
        """
        maja_object = MajaInternalXmlInputAngles(self.values_1, self.values_2,
                                                 self.col_step, self.row_step, self.output_filename)
        maja_object.write()


if __name__ == "__main__":
    unittest.main()
