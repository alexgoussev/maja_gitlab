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

orchestrator.tests.maja_test_case -- shortdesc

orchestrator.tests.maja_test_case is a description

It defines classes_and_methods

###################################################################################################

:copyright: 2019 CNES. All rights reserved.
:license: license

###################################################################################################
"""


import tempfile
import unittest


class MajaTestCase(unittest.TestCase):
    """Set working directory and epsilon for numeric comparison"""

    EPSILON = 1e-6

    def __init__(self, *args, **kwargs):

        super(MajaTestCase, self).__init__(*args, **kwargs)
        self.working_test_directory = tempfile.mkdtemp(prefix="maja_test")


if __name__ == "__main__":
    unittest.main()
