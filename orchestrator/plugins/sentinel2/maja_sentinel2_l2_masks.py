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

orchestrator.plugins.sentinel2.maja_sentinel2_l1_masks -- shortdesc

orchestrator.plugins.sentinel2.maja_sentinel2_l1_masks is a description

It defines classes_and_methods

###################################################################################################

:copyright: 2019 CNES. All rights reserved.
:license: license

###################################################################################################
"""

import os
from orchestrator.common.logger.maja_logging import configure_logger
LOGGER = configure_logger(__name__)

ANNEX_FILES = "Variable_Header/Specific_Product_Header/Product_Organization/List_of_Annex_Files/Annex_File[@sk='MSK']/File_Location/text()"


QUALITY_INFO = "n1:Quality_Indicators_Info"
MASKS = "Pixel_Level_QI/MASK_FILENAME"
BAND_ID = "./@bandId"
MASKS_TYPE = "./@type"
MASKS_VALUE = "./text()"

# TODO: write a mother class to put write method and col_step and row_step values


class MajaL2Masks(object):

    def __init__(self, root, product_directory="", nss={}):
        self.product_directory = product_directory
        self.masks_filepaths = {"R1": None,
                                "R2": None}

        self._read(root, nss)

    def _read(self, root, nss={}):
        """
        Read the xml file and extract angles
        """
        annex_files = root.xpath(ANNEX_FILES)

        for mask_location in annex_files:
            if mask_location.endswith("R1.HDR"):
                self.masks_filepaths["R1"] = os.path.abspath(os.path.join(self.product_directory, mask_location))
            if mask_location.endswith("R2.HDR"):
                self.masks_filepaths["R2"] = os.path.abspath(os.path.join(self.product_directory, mask_location))
