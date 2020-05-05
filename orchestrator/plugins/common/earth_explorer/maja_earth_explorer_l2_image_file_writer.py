# -*- coding: utf-8 -*-
#
# Copyright (C) 2020 Centre National d'Etudes Spatiales (CNES)
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
###################################################################################################

                        o     o
                        oo   oo   oo        o   oo        ,-.
                        o o o o  o  o       o  o  o       \_/
                        o  o  o o    o      o o    o     {|||D
                        o     o oooooo      o oooooo      / \
                        o     o o    o o    o o    o      `-^
                        o     o o    o  oooo  o    o

###################################################################################################

orchestrator.plugins.sentinel2.maja_sentinel2_angles -- shortdesc

orchestrator.plugins.sentinel2.maja_sentinel2_angles is a description

It defines classes_and_methods


###################################################################################################
"""
import orchestrator.common.file_utils as file_utils
from orchestrator.plugins.common.base.maja_l2_image_writer_base import L2ImageWriterBase
from orchestrator.plugins.common.base.maja_l2_image_filenames_provider import L2ImageFilenamesProvider
from orchestrator.cots.otb.otb_app_handler import OtbAppHandler
from orchestrator.cots.otb.algorithms.otb_resample import resample
from orchestrator.common.logger.maja_logging import configure_logger
import os

LOGGER = configure_logger(__name__)


class EarthExplorerL2ImageFileWriter(L2ImageWriterBase):

    def __init__(self):
        super(EarthExplorerL2ImageFileWriter, self).__init__()

    def write(self, working_dir):
        LOGGER.info("EarthExplorerL2ImageFileWriter:Write()")

        # ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** **
        # Store the Global filename of the product.Here, it 's a EarthExplorer L2 product organization
        l_L2ImageFilenamesProvider = L2ImageFilenamesProvider()
        l_L2ImageFilenamesProvider.initialize(
            self._l1_image_info,
            self._plugin.ListOfL2Resolutions,
            self._l2_output_directory,
            False)
        # ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** **
        # Create the Outputs directories
        # ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** **
        file_utils.create_directory(l_L2ImageFilenamesProvider.get_public_directory())
        file_utils.create_directory(l_L2ImageFilenamesProvider.get_private_filenames().get_private_directory())
        # ---------------------------------------------------------------------------------------------
        # If multi temporal
        LOGGER.debug(
            "EarthExplorerL2ImageFileWriter:: m_WriteLTC                       : " + str(self._dealingltc))
        LOGGER.debug("l_L2ImageFilenamesProvider.get_private_file_names().GetDealingLTC() : " +
                     str(l_L2ImageFilenamesProvider.get_private_filenames().get_dealing_ltc()))
        if self._dealingltc:
            file_utils.create_directory(
                l_L2ImageFilenamesProvider.get_private_filenames().get_ltc_image_dir_filename())

        LOGGER.debug("l_L2ImageFilenamesProvider.get_private_file_names().GetLTCImageDirFileName() : " +
                     l_L2ImageFilenamesProvider.get_private_filenames().get_ltc_image_dir_filename())

        # ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** **
        self.initialize(l_L2ImageFilenamesProvider.get_private_filenames())

        # ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** **
        # Store filename
        self._global_product_filename = l_L2ImageFilenamesProvider.get_hdr_filename()
        self._production_report_filename = l_L2ImageFilenamesProvider.get_pmc_filename()
        # ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** **
        # Store the Privates filename
        self._l2privateimagefilenamesprovider = l_L2ImageFilenamesProvider.get_private_filenames()

        # ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** **
        # Write product only if enable
        if self._write_l2_products:
            # ex:  - self.m_ReflectanceQuantificationValue: 0.001
            # - self.m_AOTQuantificationValue: 0.05
            # - self.m_VAPQuantificationValue: 0.005
            l_ReflectanceQuantificationValue = 1. / self._reflectancequantification
            l_AOTQuantificationValue = 1. / self._aotquantificationvalue
            l_VAPQuantificationValue = 1. / self._vapquantificationvalue

            # ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** *
            # Write Private images
            # ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** *
            self.write_private_images(
                l_L2ImageFilenamesProvider.get_private_filenames(),
                l_ReflectanceQuantificationValue,
                self._plugin.CLDDataBandsSelected,
                self._plugin.CLDCoreAlgorithmsMapBand,
                self._writeonlyclacld,
                self._dealingltc,
                working_dir)

            # ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** *
            # Write Public images
            # ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** *
            self.write_public_images(
                l_L2ImageFilenamesProvider,
                l_ReflectanceQuantificationValue,
                l_AOTQuantificationValue,
                self._aotnodatavalue,
                l_VAPQuantificationValue,
                self._vapnodatavalue,
                self._plugin.CLDDataBandsSelected,
                self._plugin.CLDCoreAlgorithmsMapBand,
                self._writepublicproduct,
                self._envcoroption,
                working_dir)

            # ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** *
            # Write Quicklook QLK
            # ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** *
            if self._writepublicproduct:
                l_RedBandId = 0
                l_GreenBandId = 0
                l_BlueBandId = 0
                resol_QLK = 0
                l_Resolution = ""
                l_BandsDefinitions = self._plugin.BandsDefinitions
                l_BandsDefinitions.get_l2_information_for_quicklook_band_code(
                    self._quicklookredbandcode,
                    self._quicklookgreenbandcode,
                    self._quicklookbluebandcode,
                   )
                self.write_quicklook_image(
                    l_L2ImageFilenamesProvider.get_qlk_filename(),
                    self._sre_list[resol_QLK],
                    self._writepublicproduct,
                    l_RedBandId,
                    l_GreenBandId,
                    l_BlueBandId,
                    self._quicklookminreflredband,
                    self._quicklookmaxreflredband,
                    self._quicklookminreflgreenband,
                    self._quicklookmaxreflgreenband,
                    self._quicklookminreflblueband,
                    self._quicklookmaxreflblueband,
                    self._real_l2_no_data,
                    self._dtm.ALC,
                    working_dir)

    def write_qlt_product(self, p_res, p_qlt_image_filename, working_dir):
        LOGGER.info("EarthExplorerL2ImageFileWriter:WriteQLTproduct()")
        l_BandsDefinitions = self._plugin.BandsDefinitions
        l_StrRes = l_BandsDefinitions.ListOfL2Resolution[p_res]
        QOTHImageList = []

        QOTHImageList.append(self._l2edgimagelist[p_res])
        QOTHImageList.append(self._l2taomasklist[p_res])
        if self._plugin.WaterVapourDetermination:
            QOTHImageList.append(self._l2iwcmasklist[p_res])

        # Concat to get atb
        qoth_tmp_concat = os.path.join(working_dir, "tmp_qoth_" + l_StrRes + ".tif")
        param_qoth_concat = {"il": QOTHImageList,
                             "out": qoth_tmp_concat
                             }
        qoth_concat_app = OtbAppHandler("ConcatenateImages", param_qoth_concat, write_output=False)

        # Binary concatenation
        qoth_tmp_binary = os.path.join(working_dir, "tmp_qoth_binary_" + l_StrRes + ".tif")
        param_qoth_binary = {"im": qoth_concat_app.getoutput().get("out"),
                             "out": qoth_tmp_binary
                             }
        qoth_binary_app = OtbAppHandler("BinaryConcatenate", param_qoth_binary, write_output=False)


        # -------------------------------------------------------
        # Concatenation of the QLT mask with the SAT, PIX and OTH masks
        # --------------------------------------------------------
        # As for the PIX mask, the SAT mask in concatenate in one band where each bit matches one band
        sat_tmp_concat = os.path.join(working_dir, "tmp_sat_" + l_StrRes + ".tif")
        param_sat_binconcat = {"im": self._l2satimagelist[p_res],
                               "out": sat_tmp_concat
                               }
        sat_binconcat_app = OtbAppHandler("BinaryConcatenate", param_sat_binconcat, write_output=False)

        # Create the QLT vector image
        QLTImageList = []
        QLTImageList.append(sat_binconcat_app.getoutput().get("out"))
        QLTImageList.append(self._l2piximagelist[p_res])
        QLTImageList.append(qoth_binary_app.getoutput().get("out"))
        param_qlt_concat = {"il": QLTImageList,
                            "out": p_qlt_image_filename
                            }
        OtbAppHandler("ConcatenateImages", param_qlt_concat)

    def write_public_images(
            self,
            p_L2ImageFilenamesProvider,
            p_ReflectanceQuantificationValue,
            p_AOTQuantificationValue,
            p_AOTNodataValue,
            p_VAPQuantificationValue,
            p_VAPNodataValue,
            p_CLDDataBandsSelected,
            p_CLDCoreAlgorithmsMapBand,
            p_WritePublicProduct,
            p_EnvCorOption,
            working_dir):
        # == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == ==
        # IF PUBLIC PART OF L2 PRODUCT  IS WRITTEN
        # == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == ==
        if p_WritePublicProduct:
            l_NumberOfResolutions = len(p_L2ImageFilenamesProvider.get_sre_headers())
            LOGGER.debug("L2ImageFileWriterBase::Initialize Number of resolutions: " + str(l_NumberOfResolutions) + ".")
            # ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** *
            # ** ** LOOP on RESOLUTION ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** **
            l_BandsDefinitions = self._plugin.BandsDefinitions

            for resol in range(0, l_NumberOfResolutions):
                l_StrResolution = l_BandsDefinitions.ListOfL2Resolution[resol]
                # --------------------------------------------------------
                # L2 area AreaType l_AreaToL2Resolution
                l_AreaFile = self._sre_list[resol]
                l_ListOfBand = l_BandsDefinitions.get_list_of_l2_band_code(l_StrResolution)

                LOGGER.debug("L2ImageFileReader::Gen Public image file for the resolution " + l_StrResolution + ".")

                # ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** **
                # Read the Coef apply for SRE and FRE images
                LOGGER.info(
                    "SRE and FRE values multiply by the reflectance quantification value " +
                    str(p_ReflectanceQuantificationValue) +
                    ".")
                # ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** **
                # ** ** PUBLIC  DATA ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** **

                # START WRITING SRE Image file DATA
                # Caching the SRE image, before computing the QuickLook.
                # Create the scalar image filter
                param_scaled_sre = {
                    "im": self._sre_list[resol],
                    "coef": p_ReflectanceQuantificationValue,
                    "out": p_L2ImageFilenamesProvider.get_sre_filenames()[resol] + ":int16"}
                OtbAppHandler("MultiplyByScalar", param_scaled_sre)

                # ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** **
                # START WRITING FRE Image file DATA
                if p_EnvCorOption:
                    param_scaled_fre = {
                        "im": self._fre_list[resol],
                        "coef": p_ReflectanceQuantificationValue,
                        "out": p_L2ImageFilenamesProvider.get_fre_filenames()[resol] + ":int16"}
                    OtbAppHandler("MultiplyByScalar", param_scaled_fre)

                # ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** **
                # START WRITING ATB Image file DATA
                # Initialize the Scalar filter
                # FA1424: Temporary Fix to address cosmetic aspects of FA1424
                # VAPThreshold.SetInput(self.GetVAPImageList()[resol))
                # VAPThreshold.SetOutsideValue(255. / p_VAPQuantificationValue)
                # VAPThreshold.ThresholdAbove(255. / p_VAPQuantificationValue)

                # VAPScalar.SetInput(VAPThreshold.GetOutput())
                # VAPScalar.SetCoef(p_VAPQuantificationValue)
                tmp_vap = os.path.join(working_dir, "tmp_vap_scaled_" + l_StrResolution + ".tif")
                param_bandmath_vap = {
                    "il": [
                        self._l2vapimagelist[resol],
                        self._l2edgimagelist[resol]],
                    "exp": "(im2b1 == 1)?" +
                    str(p_VAPNodataValue) +
                    ":" +
                    "rint(im1b1*" +
                    str(p_VAPQuantificationValue)+")",
                    "out": tmp_vap + ":uint8"}
                vap_scal_app = OtbAppHandler("BandMath", param_bandmath_vap, write_output=False)


                tmp_aot = os.path.join(working_dir, "tmp_aot_scaled_" + l_StrResolution + ".tif")
                param_bandmath_aot = {"il": [self._l2aotlist[resol], self._l2edgimagelist[resol]],
                                      "exp": "(im2b1 == 1)?" + str(p_AOTNodataValue) + ":" + "rint(im1b1*" + str(
                                          p_AOTQuantificationValue)+")",
                                      "out": tmp_aot + ":uint8"
                                      }
                aot_scal_app = OtbAppHandler("BandMath", param_bandmath_aot, write_output=False)

                param_atb_concat = {"il": [vap_scal_app.getoutput().get("out"), aot_scal_app.getoutput().get("out")],
                                    "out": p_L2ImageFilenamesProvider.get_atb_image_filename()[resol] + ":uint8"
                                    }
                OtbAppHandler("ConcatenateImages", param_atb_concat)

                # ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** **
                # START WRITING MSK Image file DATA
                # ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** **

                # Connect the WAM image
                was_resampled = os.path.join(working_dir, "was_resampled_" + l_StrResolution + ".tif")
                app_resample_was = resample(self._wasimage, self._dtm.ALTList[resol],
                                            was_resampled, threshold=0.25, write_output=False)
                # Connect the HID image
                hid_resampled = os.path.join(working_dir, "hid_resampled_" + l_StrResolution + ".tif")
                app_resample_hid = resample(self._dtm_hid, self._dtm.ALTList[resol],
                                            hid_resampled, threshold=0.25, write_output=False)
                # Connect the SHDimage
                shd_resampled = os.path.join(working_dir, "shd_resampled_" + l_StrResolution + ".tif")
                app_resample_shd = resample(self._dtm_shd, self._dtm.ALTList[resol],
                                            shd_resampled, threshold=0.25, write_output=False)

                # Create the MOTH image that concatenates the WAT, HID, SHD, STL and TGS masks
                MOTHImageList = []
                MOTHImageList.append(app_resample_was.getoutput().get("out"))
                MOTHImageList.append(app_resample_hid.getoutput().get("out"))
                MOTHImageList.append(app_resample_shd.getoutput().get("out"))
                MOTHImageList.append(self._stl_list[resol])
                MOTHImageList.append(self._tgs_list[resol])
                app_resample_snow = None
                if self._cld_snow is not None:
                    snow_resampled = os.path.join(working_dir, "snow_resampled_" + l_StrResolution + ".tif")
                    app_resample_snow = resample(self._cld_snow, self._dtm.ALTList[resol],
                                                 snow_resampled, working_dir, 0.25, write_output=False)
                    MOTHImageList.append(app_resample_snow.getoutput().get("out"))
                # Concat to get atb
                moth_tmp_concat = os.path.join(working_dir, "tmp_moth_" + l_StrResolution + ".tif")
                param_moth_concat = {"il": MOTHImageList,
                                     "out": moth_tmp_concat
                                     }
                # Concatenate to produce the MOTH file
                app_moth_concat = OtbAppHandler("ConcatenateImages", param_moth_concat, write_output=False)
                # Binary concatenation of WAT, HID, SHD, STL and TGS masks
                param_moth_binconcat = {"im": app_moth_concat.getoutput().get("out"),
                                        "out": p_L2ImageFilenamesProvider.get_msk_filename()[resol] + ":uint8"
                                        }
                moth_binconcat_app = OtbAppHandler("BinaryConcatenate", param_moth_binconcat)

                # Concatenation of the MSK mask with the CLD and MOTH masks
                # --------------------------------------------------------

                # ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** **
                # START WRITING QLT Image file DATA
                # ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** **
                self.write_qlt_product(resol, p_L2ImageFilenamesProvider.get_qlt_filenames()[resol], working_dir)

                # ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** *
                # START WRITING CLD Public Image file DATA
                # ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** *

                # Connect the CLD image
                # -------------------------------------
                self.write_cld_image(self._l2cldlist[resol], p_CLDDataBandsSelected,
                                   p_L2ImageFilenamesProvider.get_cld_image_filename()[resol])

            LOGGER.debug("Writing L2 resolution image done !")
            # ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** *
            # ** ** END LOOP on RESOLUTION ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** **
            # WARNING: For simplicity, the SOL and VIE images( and headers) are written by the L2HeaderFileWriter

