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
Author:         Peter KETTIG <peter.kettig@cnes.fr>
Project:        Start-MAJA, CNES
"""

import os
from datetime import datetime, timedelta
from StartMaja.Chain.Product import MajaProduct


class Landsat8Natif(MajaProduct):
    """
    A Landsat-8 natif product
    """

    base_resolution = (30, -30)

    @property
    def platform(self):
        return "landsat8"

    @property
    def type(self):
        return "natif"

    @property
    def level(self):
        return "l1c"

    @property
    def tile(self):
        import re
        site = self.base.split("_")[4]
        tile = re.search(self.reg_tile, site)
        if tile:
            return tile.group()[1:]
        return site

    @property
    def metadata_file(self):
        metadata_filename = self.base.split(".")[0] + ".HDR"
        return self.get_file(folders="../", filename=metadata_filename)

    @property
    def validity(self):
        if os.path.exists(self.metadata_file):
            return True
        return False

    def link(self, link_dir):
        from StartMaja.Common.FileSystem import symlink
        symlink(self.fpath, os.path.join(link_dir, self.base))
        mtd_file = self.metadata_file
        symlink(mtd_file, os.path.join(link_dir, os.path.basename(mtd_file)))

    @property
    def date(self):
        str_date = self.base.split(".")[0].split("_")[-1]
        # Add a timedelta of 12hrs in order to compensate for the missing H/M/S:
        return datetime.strptime(str_date, "%Y%m%d") + timedelta(hours=12)

    @property
    def mnt_site(self):
        from StartMaja.prepare_mnt.mnt.SiteInfo import Site
        try:
            band_bx = self.get_file(filename=r"*_B0?1*.tif")
        except IOError as e:
            raise e
        return Site.from_raster(self.tile, band_bx)

    @property
    def mnt_resolutions_dict(self):
        return [{"name": "XS",
                "val": str(self.mnt_resolution[0]) + " " + str(self.mnt_resolution[1])}]

    def get_synthetic_band(self, synthetic_band, **kwargs):
        raise NotImplementedError


class Landsat8Muscate(MajaProduct):
    """
    A Landsat-8 muscate product
    """

    base_resolution = (30, -30)

    @property
    def platform(self):
        return "landsat8"

    @property
    def type(self):
        return "muscate"

    @property
    def level(self):
        if self.base.find("_L1C_") >= 0:
            return "l1c"
        elif self.base.find("_L2A_") >= 0:
            return "l2a"
        raise ValueError("Unknown product level for %s" % self.base)

    @property
    def tile(self):
        import re
        if len(self.base.split("_")) == 7:
            site = "_".join(self.base.split("_")[3:5])
        else:
            site = self.base.split("_")[3]
        tile = re.search(self.reg_tile, site)
        if tile:
            return tile.group()[1:]
        return site

    @property
    def metadata_file(self):
        return self.get_file(filename="*MTD_ALL.xml")

    @property
    def date(self):
        str_date = self.base.split("_")[1]
        # Datetime has troubles parsing milliseconds, so it's removed:
        str_date_no_ms = str_date[:str_date.rfind("-")]
        return datetime.strptime(str_date_no_ms, "%Y%m%d-%H%M%S")

    @property
    def validity(self):
        from StartMaja.Common import FileSystem, XMLTools
        if self.level == "l1c" and os.path.exists(self.metadata_file):
            return True
        if self.level == "l2a":
            try:
                jpi = FileSystem.find_single("*JPI_ALL.xml", self.fpath)
            except ValueError:
                return False
            validity_xpath = "./Processing_Flags_And_Modes_List/Processing_Flags_And_Modes/Value"
            processing_flags = XMLTools.get_xpath(jpi, validity_xpath)
            validity_flags = [flg.text for flg in processing_flags]
            if "L2VALD" in validity_flags:
                return True
        return False

    def link(self, link_dir):
        from StartMaja.Common.FileSystem import symlink
        symlink(self.fpath, os.path.join(link_dir, self.base))

    @property
    def mnt_site(self):
        from StartMaja.prepare_mnt.mnt.SiteInfo import Site
        try:
            band_bx = self.get_file(filename=r"*_B0?1*.tif")
        except IOError as e:
            raise e
        return Site.from_raster(self.tile, band_bx)

    @property
    def mnt_resolutions_dict(self):
        return [{"name": "XS",
                "val": str(self.mnt_resolution[0]) + " " + str(self.mnt_resolution[1])}]

    def get_synthetic_band(self, synthetic_band, **kwargs):
        raise NotImplementedError


class Landsat8LC1(MajaProduct):
    """
    A Landsat-8 ssc product
    """

    base_resolution = (30, -30)

    @property
    def platform(self):
        return "landsat8"

    @property
    def type(self):
        return "natif"

    @property
    def level(self):
        return "l1c"

    @property
    def tile(self):
        return self.base[3:9]

    @property
    def metadata_file(self):
        return self.get_file(filename="*_MTL.txt")

    @property
    def date(self):
        year_doy = self.base[9:15]
        # Add a timedelta of 12hrs in order to compensate for the missing H/M/S:
        return datetime.strptime(year_doy, "%Y%j") + timedelta(hours=12)

    @property
    def validity(self):
        if os.path.exists(self.metadata_file):
            return True
        return False

    def link(self, link_dir):
        from StartMaja.Common.FileSystem import symlink
        symlink(self.fpath, os.path.join(link_dir, self.base))

    @property
    def mnt_site(self):
        from StartMaja.prepare_mnt.mnt.SiteInfo import Site
        try:
            band_bx = self.get_file(filename=r"*_B0?1*.tif")
        except IOError as e:
            raise e
        return Site.from_raster(self.tile, band_bx)

    @property
    def mnt_resolutions_dict(self):
        return [{"name": "XS",
                "val": str(self.mnt_resolution[0]) + " " + str(self.mnt_resolution[1])}]

    def get_synthetic_band(self, synthetic_band, **kwargs):
        raise NotImplementedError


class Landsat8LC2(MajaProduct):
    """
    A Landsat-8 ssc product
    """

    base_resolution = (30, -30)

    @property
    def platform(self):
        return "landsat8"

    @property
    def type(self):
        return "natif"

    @property
    def level(self):
        return "l1c"

    @property
    def tile(self):
        return self.base.split("_")[2]

    @property
    def metadata_file(self):
        return self.get_file(filename="*_MTL.txt")

    @property
    def date(self):
        str_date = self.base.split("_")[3]
        # Add a timedelta of 12hrs in order to compensate for the missing H/M/S:
        return datetime.strptime(str_date, "%Y%m%d") + timedelta(hours=12)

    @property
    def validity(self):
        if os.path.exists(self.metadata_file):
            return True
        return False

    def link(self, link_dir):
        from StartMaja.Common.FileSystem import symlink
        symlink(self.fpath, os.path.join(link_dir, self.base))

    @property
    def mnt_site(self):
        from StartMaja.prepare_mnt.mnt.SiteInfo import Site
        try:
            band_bx = self.get_file(filename=r"*_B0?1*.tif")
        except IOError as e:
            raise e
        return Site.from_raster(self.tile, band_bx)

    @property
    def mnt_resolutions_dict(self):
        return [{"name": "XS",
                "val": str(self.mnt_resolution[0]) + " " + str(self.mnt_resolution[1])}]

    def get_synthetic_band(self, synthetic_band, **kwargs):
        raise NotImplementedError
