#!/usr/bin/env python3
# -*- coding: utf-8 -*-
#
# Copyright (C) 2020 Centre National d'Etudes Spatiales (CNES), CS-SI, CESBIO - All Rights Reserved
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#    http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#
"""

Author:         Peter KETTIG <peter.kettig@cnes.fr>,
Project:        Start-MAJA, CNES
"""

import unittest
from StartMaja.Common import DummyFiles
import os


class TestDummyFiles(unittest.TestCase):
    root = os.path.join(os.getcwd(), "DummyFiles")
    platforms = ["sentinel2", "landsat8", "venus"]

    @classmethod
    def setUpClass(cls):
        from StartMaja.Common import FileSystem
        FileSystem.create_directory(cls.root)

    @classmethod
    def tearDownClass(cls):
        from StartMaja.Common import FileSystem
        FileSystem.remove_directory(cls.root)

    def test_mnt_generation(self):
        import shutil
        gen = DummyFiles.MNTGenerator(self.root)
        mnt = gen.generate()
        self.assertTrue(gen.platform in self.platforms)
        self.assertTrue(os.path.exists(mnt.hdr))
        self.assertTrue(os.path.exists(mnt.dbl))
        self.assertTrue("_TEST_AUX_REFDE2_" in mnt.hdr)
        self.assertTrue("_TEST_AUX_REFDE2_" in mnt.dbl)

        shutil.rmtree(mnt.dbl)
        os.remove(mnt.hdr)
        self.assertFalse(os.path.exists(mnt.hdr))
        self.assertFalse(os.path.exists(mnt.dbl))

    def test_cams_generation(self):
        import shutil
        gen = DummyFiles.CAMSGenerator(self.root)
        c = gen.generate()
        self.assertTrue(gen.platform in self.platforms)
        self.assertTrue(os.path.exists(c.hdr))
        self.assertTrue(os.path.exists(c.dbl))
        self.assertTrue("_TEST_EXO_CAMS_" in c.hdr)
        self.assertTrue("_TEST_EXO_CAMS_" in c.dbl)

        shutil.rmtree(c.dbl)
        os.remove(c.hdr)
        self.assertFalse(os.path.exists(c.hdr))
        self.assertFalse(os.path.exists(c.dbl))

    def test_gipp_generation_cams(self):
        gen = DummyFiles.GippGenerator(self.root)
        gipp = gen.generate()
        self.assertTrue(gen.platform in self.platforms)
        self.assertTrue(gipp.check_completeness())

    def test_gipp_generation_nocams(self):
        gen = DummyFiles.GippGenerator(self.root)
        gipp = gen.generate(cams=False)
        self.assertTrue(gen.platform in self.platforms)
        self.assertTrue(gipp.check_completeness())

    def test_gipp_generation_cams_tm(self):
        gen = DummyFiles.GippGenerator(self.root)
        gipp = gen.generate(mission="tm")
        self.assertTrue(gen.platform in self.platforms)
        self.assertTrue(gipp.check_completeness())

    def test_s2_l1_generation(self):
        import shutil
        gen = DummyFiles.L1Generator(self.root, platform="sentinel2")
        prod = gen.generate()
        self.assertTrue(os.path.exists(gen.mtd))
        self.assertTrue(os.path.exists(gen.prod))
        self.assertTrue("MTD_MSIL1C.xml" in os.path.basename(gen.mtd))
        self.assertTrue("MSIL1C" in gen.prod)
        self.assertEqual(prod, prod)
        shutil.rmtree(gen.prod)
        self.assertFalse(os.path.exists(gen.prod))

    def test_l2_generation(self):
        import shutil
        gen = DummyFiles.L2Generator(self.root)
        prod = gen.generate()
        self.assertTrue(os.path.exists(gen.mtd))
        self.assertTrue(os.path.exists(gen.prod))
        self.assertTrue("_MTD_ALL.xml" in os.path.basename(gen.mtd))
        self.assertTrue(os.path.dirname(gen.mtd), gen.prod)
        self.assertEqual(prod, prod)
        shutil.rmtree(gen.prod)
        self.assertFalse(os.path.exists(gen.prod))


if __name__ == '__main__':
    unittest.main()
