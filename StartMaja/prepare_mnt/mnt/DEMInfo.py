#
# Copyright (C) 2020 Centre National d'Etudes Spatiales (CNES)
#
#Licensed under the Apache License, Version 2.0 (the "License");
#you may not use this file except in compliance with the License.
#You may obtain a copy of the License at
#
#    http://www.apache.org/licenses/LICENSE-2.0
#
#Unless required by applicable law or agreed to in writing, software
#distributed under the License is distributed on an "AS IS" BASIS,
#WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
#See the License for the specific language governing permissions and
#limitations under the License.
#
#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""

Author:         Peter KETTIG <peter.kettig@cnes.fr>, Pierre LASSALLE <pierre.lassalle@cnes.fr>
Project:        StartMaja, CNES
Created on:     Tue Sep 11 15:31:00 2018
"""


class DEMInfo:
    def __init__(self, site, dem_full_res):
        from StartMaja.Common import ImageIO
        import numpy as np
        self.name = site.nom
        self.epsg = site.epsg_str
        self.ulx = site.ul[0]
        self.uly = site.ul[1]
        self.resx = site.res_x
        self.resy = site.res_y
        self.lx = site.px
        self.ly = site.py
        self.alt = dem_full_res
        arr, drv = ImageIO.tiff_to_array(self.alt, array_only=False)
        self.mean_alt = np.mean(arr)
        self.std_dev_alt = np.std(arr)
        self.short_description = ImageIO.get_utm_description(drv)
        self.nodata = ImageIO.get_nodata_value(drv)
        res_arr = ImageIO.get_resolution(drv)
        self.dem_subsampling_ratio = str(int(float(res_arr[0]) / float(site.res_x)))

