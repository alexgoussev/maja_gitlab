# -*- coding: utf-8 -*-
"""
###################################################################################################
#
#                        o     o
#                        oo   oo   oo        o   oo        ,-.
#                        o o o o  o  o       o  o  o       \_/
#                        o  o  o o    o      o o    o     |||)<
#                        o     o oooooo      o oooooo      / \
#                        o     o o    o o    o o    o      `-^
#                        o     o o    o  oooo  o    o
#
###################################################################################################

orcRThestrator.plugins.maja_dataset -- shortdesc

orchestrator.plugins.maja_dataset is a description

It defines classes_and_methods

###################################################################################################

:copyright: 2019 CNES. All rights reserved.
:license: license

###################################################################################################
"""
import orchestrator.common.file_utils as file_utils
from orchestrator.common.constants import *
import orchestrator.common.xml_tools as xml_tools
from orchestrator.cots.otb.otb_app_handler import OtbAppHandler
from orchestrator.cots.otb.otb_pipeline_manager import OtbPipelineManager
from orchestrator.cots.otb.algorithms.otb_write_images import write_images
from orchestrator.cots.otb.algorithms.otb_band_math import band_math
from orchestrator.cots.otb.algorithms.otb_resample import OtbResampleType
import orchestrator.cots.otb.otb_file_utils as otb_file_utils
from orchestrator.cots.otb.algorithms.otb_resample import resample
from orchestrator.cots.otb.algorithms.otb_extract_roi import extract_roi
from orchestrator.plugins.common.base.maja_l2_private_image_filenames_provider import L2PrivateImageFilenamesProvider
from orchestrator.common.muscate.muscate_xml_file_handler import MuscateXMLFileHandler
from orchestrator.plugins.common.base.maja_l2_image_writer_base import L2ImageWriterBase
from orchestrator.cots.otb.algorithms.otb_constant_image import constant_image
from orchestrator.common.logger.maja_logging import configure_logger
import os
from orchestrator.common.maja_common import Area
LOGGER = configure_logger(__name__)


class MajaMuscateL2ImageWriter(L2ImageWriterBase):

    def __init__(self):
        super(MajaMuscateL2ImageWriter, self).__init__()

    # Initialize method
    def initialize_product(self):

        LOGGER.debug("Start MuscateL2ImageFileWriter::InitializeProduct() ...")
        l_L2BaseFilename = self._l1_image_info.get_l2_product_id()
        LOGGER.debug("L2Base filename: " + l_L2BaseFilename)
        LOGGER.debug("Output Directory: " + self._l2_output_directory)
        l_PublicDirectory = os.path.join(self._l2_output_directory, l_L2BaseFilename)
        l_DATADirectory = os.path.join(l_PublicDirectory, "DATA")
        # Create Directories
        file_utils.create_directory(l_PublicDirectory)
        file_utils.create_directory(l_DATADirectory)
        # Store filename
        l_L2XMLFilename = os.path.join(l_PublicDirectory, l_L2BaseFilename + "_MTD_ALL.xml")
        self._global_product_filename = l_L2XMLFilename

    # Generate data method
    def write(self, working_dir):
        LOGGER.debug("Start MuscateL2ImageFileWriter::Write() ...")
        l_L1XMLFilename = self._l1_image_info.HeaderFilename
        LOGGER.debug("Start writing the L2 product for this L1 header filename <" + l_L1XMLFilename +
                     "> in the output directory <" + self._l2_output_directory + ">.")

        # L2BaseFilename: LANDSAT5-TM-XS_20100118-103000-000_L2A_EU93066200A00B_C_V1-0
        l_L2BaseFilename = self._l1_image_info.get_l2_product_id()
        LOGGER.debug("L2Base filename: " + l_L2BaseFilename)
        l_PublicDirectory = os.path.join(self._l2_output_directory, l_L2BaseFilename)
        l_DATADirectory = os.path.join(l_PublicDirectory, "DATA")
        l_DateInYYYYMMDD = self._l1_image_info.ProductDateStr

        l_L2PrivateImageFilenames = L2PrivateImageFilenamesProvider()
        l_L2PrivateImageFilenames.set_dealing_ltc(self._dealingltc)
        l_L2PrivateImageFilenames.initialize_with_root_dir(os.path.join(l_DATADirectory, l_L2BaseFilename + "_PVD_ALL"),
                                                           l_DateInYYYYMMDD)

        # Call super class  GeneateData()
        self.initialize(l_L2PrivateImageFilenames)

        # Create the Outputs directories
        file_utils.create_directory(l_PublicDirectory)
        file_utils.create_directory(l_DATADirectory)
        file_utils.create_directory(l_L2PrivateImageFilenames.get_private_directory())

        # If multi temporal
        LOGGER.debug("MuscateL2ImageFileWriter:: m_WriteLTC : " + str(self._dealingltc))
        if self._dealingltc:
            file_utils.create_directory(l_L2PrivateImageFilenames.get_ltc_image_dir_filename())

        # Store filename
        l_L2XMLFilename = os.path.join(l_PublicDirectory, l_L2BaseFilename + "_MTD_ALL.xml")

        self._global_product_filename = l_L2XMLFilename
        # Set the product report filename for MUSCATE handling !!!
        self._production_report_filename = self._l2_output_directory + "/maja_product_report.log"
        # Store the Privates filename
        self._l2privateimagefilenamesprovider = l_L2PrivateImageFilenames

        # Write product only if enable
        if self._write_l2_products:
            # ex :  - self.m_ReflectanceQuantificationValue : 0.001
            #       - self.m_AOTQuantificationValue         : 0.05
            #       - self.m_VAPQuantificationValue         : 0.005
            l_ReflectanceQuantificationValue = 1. / self._reflectancequantification
            l_AOTQuantificationValue = 1. / self._aotquantificationvalue
            l_VAPQuantificationValue = 1. / self._vapquantificationvalue
            # Write Private images
            self.write_private_images(
                l_L2PrivateImageFilenames,
                l_ReflectanceQuantificationValue,
                self._plugin.CLDDataBandsSelected,
                self._plugin.CLDCoreAlgorithmsMapBand,
                self._writeonlyclacld,
                self._dealingltc,
                working_dir)

            # Write Public images (include CLD public)
            self.write_public_images(
                l_PublicDirectory,
                l_L2BaseFilename,
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

            l_QuicklookFilename = l_L2XMLFilename.replace("_MTD_ALL.xml", "_QKL_ALL.jpg")
            LOGGER.debug("The Quicklook filename is <" + l_QuicklookFilename + ">.")
            # Write Quicklook QLK
            if self._writepublicproduct:
                l_RedBandId = 0
                l_BlueBandId = 0
                l_GreenBandId = 0
                resol_QLK = 0
                l_Resolution = ""
                l_BandsDefinitions = self._plugin.BandsDefinitions
                l_RedBandId,l_BlueBandId, l_GreenBandId = l_BandsDefinitions.get_l2_information_for_quicklook_band_code(self._quicklookredbandcode,
                                                                        self._quicklookgreenbandcode,
                                                                        self._quicklookbluebandcode)


                l_L2QuickLookFilename = l_PublicDirectory + "/" + l_L2BaseFilename + "_QKL_ALL.jpg"
                self.write_quicklook_image(l_L2QuickLookFilename, self._sre_list[resol_QLK],
                                         self._writepublicproduct, l_RedBandId, l_GreenBandId, l_BlueBandId,
                                         self._quicklookminreflredband,
                                         self._quicklookmaxreflredband, self._quicklookminreflgreenband,
                                         self._quicklookmaxreflgreenband,
                                         self._quicklookminreflblueband, self._quicklookmaxreflblueband,
                                         self._real_l2_no_data, self._sre_list[resol_QLK], working_dir)

    def write_public_images(
            self,
            p_PublicDirectory,
            p_L2BaseFilename,
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

        # IF PUBLIC PART OF L2 PRODUCT IS WRITTEN
        if p_WritePublicProduct:
            l_BandsDefinitions = self._plugin.BandsDefinitions

            l_ListOfL2Res = l_BandsDefinitions.ListOfL2Resolution
            l_NumberOfResolutions = len(l_ListOfL2Res)
            LOGGER.debug("L2ImageFileWriterBase::Initialize Number of resolutions: " + str(l_NumberOfResolutions) + ".")
            # Not use the list of XS band because for Landsat8, the band B9 is not
            # selected in the L2 resolution (only in L2Coarse resolution)
            l_BaseL2FullFilename = os.path.join(p_PublicDirectory, p_L2BaseFilename)
            l_MASKSDirectory = os.path.join(p_PublicDirectory, "MASKS")
            l_BaseL2FullMASKSFilename = os.path.join(l_MASKSDirectory, p_L2BaseFilename)
            file_utils.create_directory(l_MASKSDirectory)

            # *************************************************************************************************************
            # ****  LOOP on RESOLUTION   *********************************************
            # *************************************************************************************************************
            for resol in range(0, l_NumberOfResolutions):
                l_StrResolution = l_BandsDefinitions.ListOfL2Resolution[resol]
                # --------------------------------------------------------
                # L2 area AreaType l_AreaToL2Resolution

                l_AreaFile = self._sre_list[resol]
                l_ListOfBand = l_BandsDefinitions.get_list_of_l2_band_code(l_StrResolution)

                l_NumberOfBands = len(l_ListOfBand)
                LOGGER.debug("L2ImageFileReader::Gen Public image file for the resolution " + l_StrResolution + ".")
                l_grpSuffix = ""
                if l_NumberOfResolutions == 1:
                    l_grpSuffix = "XS"
                else:
                    l_grpSuffix = l_ListOfL2Res[resol]
                l_StrResolution = l_BandsDefinitions.ListOfL2Resolution[resol]

                # Read the Coef apply for SRE and FRE images
                LOGGER.info(
                    "SRE and FRE values multiply by the reflectance quantification value " +
                    str(p_ReflectanceQuantificationValue) +
                    ".")
                # *************************************************************************************************************
                # ****  PUBLIC  DATA      ************************************************
                # *************************************************************************************************************

                # START WRITING SRE Image file DATA
                # Initialize the Scalar filter
                tmp_sre_scaled = os.path.join(working_dir, "tmp_sre_multiply_" + l_StrResolution + ".tif")
                param_scaled_sre = {"im": self._sre_list[resol],
                                    "coef": p_ReflectanceQuantificationValue,
                                    "out": tmp_sre_scaled
                                    }
                scaled_sre_app = OtbAppHandler("MultiplyByScalar", param_scaled_sre,write_output=True)
                sre_pipeline = OtbPipelineManager()

                #Extract each channel for each file

                for i in range(l_NumberOfBands):
                    tmp_sre_roi = os.path.join(working_dir, "tmp_sre_roi_" + l_StrResolution + ".tif")

                    tmp_sre_roi_app = extract_roi(scaled_sre_app.getoutput().get("out"), [i],
                                                   tmp_sre_roi, write_output=True)
                    sre_pipeline.add_otb_app(tmp_sre_roi_app)

                    param_round_sre = {"im": tmp_sre_roi_app.getoutput().get("out"),
                                       "out": l_BaseL2FullFilename + "_SRE_" + l_ListOfBand[i] + ".tif"+ file_utils.get_extended_filename_write_image_file_standard()
                                      }
                    round_sre_app = OtbAppHandler("RoundVectorImage", param_round_sre, write_output=True)

                    sre_pipeline.add_otb_app(round_sre_app)



                sre_pipeline.free_otb_app()

                # START WRITING FRE Image file DATA
                if p_EnvCorOption:
                    # Initialize the Scalar filter
                    tmp_fre_scaled = os.path.join(working_dir, "tmp_fre_multiply_" + l_StrResolution + ".tif")
                    param_scaled_fre = {"im": self._fre_list[resol],
                                        "coef": p_ReflectanceQuantificationValue,
                                        "out": tmp_fre_scaled
                                        }
                    scaled_fre_app = OtbAppHandler("MultiplyByScalar", param_scaled_fre, write_output=False)

                    fre_pipeline = OtbPipelineManager()

                    # Extract each channel for each file
                    for i in range(l_NumberOfBands):
                        tmp_fre_roi = os.path.join(working_dir, "tmp_fre_roi_" + l_StrResolution + ".tif")
                        tmp_fre_roi_app = extract_roi(scaled_fre_app.getoutput().get("out"), [i],
                                                      tmp_fre_roi, write_output=True)
                        fre_pipeline.add_otb_app(tmp_fre_roi_app)

                        param_round_fre = {"im": tmp_fre_roi_app.getoutput().get("out"),
                                           "out": l_BaseL2FullFilename + "_FRE_" + l_ListOfBand[
                            i] + ".tif" + file_utils.get_extended_filename_write_image_file_standard()
                                           }
                        round_fre_app = OtbAppHandler("RoundVectorImage", param_round_fre, write_output=True)

                        fre_pipeline.add_otb_app(round_fre_app)

                    fre_pipeline.free_otb_app()

                # START WRITING ATB Image file DATA
                # Initialize the Scalar filter
                # FA1424: Temporary Fix to address cosmetic aspects of FA1424
                # VAPThreshold.SetInput(self.GetVAPImageList()[resol))
                # VAPThreshold.SetOutsideValue(255. / p_VAPQuantificationValue)
                # VAPThreshold.ThresholdAbove(255. / p_VAPQuantificationValue)

                # VAPScalar.SetInput(VAPThreshold.GetOutput())
                # VAPScalar.SetCoef(p_VAPQuantificationValue)
                tmp_vap = os.path.join(working_dir, "tmp_vap_scaled_" + l_StrResolution + ".tif")
                param_bandmath_vap = {"il": [self._l2vapimagelist[resol], self._l2edgimagelist[resol]],
                                      "exp": "(im2b1 == 1)?" + str(p_VAPNodataValue) + ":" + "im1b1*" + str(
                                          p_VAPQuantificationValue),
                                      "out": tmp_vap
                                      }
                vap_scal_app = OtbAppHandler("BandMath", param_bandmath_vap, write_output=True)

                tmp_round_vap = os.path.join(working_dir, "tmp_vap_round_" + l_StrResolution + ".tif")
                param_round_vap = {"im": vap_scal_app.getoutput().get("out"),
                                    "out": tmp_round_vap
                                  }
                vap_round_app = OtbAppHandler("RoundVectorImage", param_round_vap, write_output=True)


                tmp_aot = os.path.join(working_dir, "tmp_aot_scaled_" + l_StrResolution + ".tif")
                param_bandmath_aot = {"il": [self._l2aotlist[resol], self._l2edgimagelist[resol]],
                                      "exp": "(im2b1 == 1)?" + str(p_AOTNodataValue) + ":" + "im1b1*" + str(
                                         p_AOTQuantificationValue),
                                      "out": tmp_aot
                                      }
                aot_scal_app = OtbAppHandler("BandMath", param_bandmath_aot, write_output=True)

                tmp_round_aot = os.path.join(working_dir, "tmp_aot_round_" + l_StrResolution + ".tif")
                param_round_aot = {"im": aot_scal_app.getoutput().get("out"),
                                   "out": tmp_round_aot
                                   }
                aot_round_app = OtbAppHandler("RoundVectorImage", param_round_aot, write_output=True)


                param_atb_concat = {
                    "il": [vap_round_app.getoutput().get("out"), aot_round_app.getoutput().get("out")],
                    "out": l_BaseL2FullFilename + "_ATB_" + l_grpSuffix + ".tif" + ":uint8"+  file_utils.get_extended_filename_write_image_file_standard()
                    }

                OtbAppHandler("ConcatenateImages", param_atb_concat)

                # START WRITING IAB MASK
                # Create the image list
                tmp_iab = os.path.join(working_dir, "tmp_iab_concat_" + l_StrResolution + ".tif")
                param_iab_concat = {
                    "il": [self._l2iwcmasklist[resol], self._l2taomasklist[resol]],
                    "out": tmp_iab
                }
                tmp_iab_concat_app = OtbAppHandler("ConcatenateImages", param_iab_concat)
                param_iab_binconcat = {"im": tmp_iab_concat_app.getoutput().get("out"),
                                       "out": l_BaseL2FullMASKSFilename + "_IAB_" + l_grpSuffix + ".tif"
                                       + file_utils.get_extended_filename_write_mask_file_muscate()
                                       }
                iab_binconcat_app = OtbAppHandler("BinaryConcatenate", param_iab_binconcat, write_output=True)

                # START WRITING MG2 Image file DATA
                l_mg2_image_list = []
                mg2_pipeline = OtbPipelineManager()
                # Connect the WAM image
                wat_resampled = os.path.join(working_dir, "wat_resampled_" + l_StrResolution + ".tif")
                app_resample_wat = resample(self._wasimage, self._dtm.ALTList[resol],
                                            wat_resampled, method=OtbResampleType.LINEAR, threshold=0.25, write_output=True)
                l_mg2_image_list.append(app_resample_wat.getoutput().get("out"))

                # Extract the CM2 cloud mask
                l_cm2_index = p_CLDCoreAlgorithmsMapBand[CLOUD_MASK_ALL_CLOUDS]
                l_mg2_image_list.append(self._l2cldlist[resol][l_cm2_index])

                #Connect the SNW image if any

                if self._cld_snow is not None:
                    LOGGER.debug("Snow mask has been successfully computed, adding it to the MG2")
                    snw_resampled = os.path.join(working_dir, "snw_resampled_" + l_StrResolution + ".tif")
                    app_resample_snw = resample(self._cld_snow, self._dtm.ALTList[resol],
                                                snw_resampled,  method=OtbResampleType.LINEAR, threshold=0.25, write_output=True)
                    l_mg2_image_list.append(app_resample_snw.getoutput().get("out"))
                    mg2_pipeline.add_otb_app(app_resample_snw)
                else:
                    # Add a constant mask
                    tmp_constant_filename = os.path.join(working_dir, "Const_shd_masks.tif")
                    cst_snw_app = constant_image(self._dtm.ALTList[resol], 0, tmp_constant_filename, write_output=True)
                    l_mg2_image_list.append(cst_snw_app.getoutput().get("out"))
                    mg2_pipeline.add_otb_app(cst_snw_app)

                # Connect the shadow or mask
                l_shadows_index = p_CLDCoreAlgorithmsMapBand[CLOUD_MASK_SHADOWS]
                l_shadvar_index = p_CLDCoreAlgorithmsMapBand[CLOUD_MASK_SHADVAR]
                tmp_shador_bandmath = os.path.join(working_dir,
                                                   "tmp_shador_bandmath_" + l_StrResolution + ".tif")
                tmp_band_math_app = band_math([self._l2cldlist[resol][l_shadows_index],
                                               self._l2cldlist[resol][l_shadvar_index]],
                                              "im1b1 || im2b1",
                                              tmp_shador_bandmath)
                l_mg2_image_list.append(tmp_band_math_app.getoutput().get("out"))

                # Connect the HID image
                hid_resampled = os.path.join(working_dir, "hid_resampled_" + l_StrResolution + ".tif")
                app_resample_hid = resample(self._dtm_hid, self._dtm.ALTList[resol],
                                            hid_resampled,  method=OtbResampleType.LINEAR,threshold=0.25, write_output=True)
                l_mg2_image_list.append(app_resample_hid.getoutput().get("out"))
                # Connect the SHDimage
                shd_resampled = os.path.join(working_dir, "shd_resampled_" + l_StrResolution + ".tif")
                app_resample_shd = resample(self._dtm_shd, self._dtm.ALTList[resol],
                                            shd_resampled, method=OtbResampleType.LINEAR, threshold=0.25, write_output=True)
                l_mg2_image_list.append(app_resample_shd.getoutput().get("out"))

                # Append STL
                l_mg2_image_list.append(self._stl_list[resol])
                # Append TGS
                l_mg2_image_list.append(self._tgs_list[resol])

                # Concatenate all
                tmp_mg2 = os.path.join(working_dir, "tmp_mg2_concat_" + l_StrResolution + ".tif")
                param_mg2_concat = {
                    "il": l_mg2_image_list,
                    "out": tmp_mg2
                }
                tmp_mg2_concat_app = OtbAppHandler("ConcatenateImages", param_mg2_concat)
                param_mg2_binconcat = {"im": tmp_mg2_concat_app.getoutput().get("out"),
                                       "out": l_BaseL2FullMASKSFilename + "_MG2_" + l_grpSuffix + ".tif"
                                       + file_utils.get_extended_filename_write_mask_file_muscate()
                                       }
                mg2_binconcat_app = OtbAppHandler("BinaryConcatenate", param_mg2_binconcat, write_output=True)
                mg2_pipeline.free_otb_app()

                # START WRITING SAT Image file DATA
                # TODO Create the writer with test on number of bands
                param_sat_binconcat = {"im": self._l2satimagelist[resol],
                                       "out": l_BaseL2FullMASKSFilename + "_SAT_" + l_grpSuffix + ".tif"
                                       + file_utils.get_extended_filename_write_mask_file_muscate()
                                       }
                sat_binconcat_app = OtbAppHandler("BinaryConcatenate", param_sat_binconcat, write_output=True)

                # START WRITING PIX Image file DATA
                if "PIXImages" in self._l1_image_info.MuscateData:
                    LOGGER.debug("The L1 product have 'Aberrant_Pixels' masks. There are writed in the L2 out product...")
                    otb_file_utils.write_images([self._l2piximagelist[resol]], [l_BaseL2FullMASKSFilename + "_PIX_" + l_grpSuffix + ".tif"
                                                                                + file_utils.get_extended_filename_write_mask_file_muscate()])
                else:
                    LOGGER.debug("No PIX node detected to write")

                # START WRITING USI Image file DATA
                if "Node_Useful_Image" in self._l1_image_info.MuscateData:
                    LOGGER.debug("The L1 product have 'Useful_Image' files. There are copied in the L2 out product...")

                    # Write the USI in the Xml file, in the Useful_Imagenode !
                    l_XPathRootUSI_In = "//Mask[Mask_Properties/NATURE='Useful_Image']/Mask_File_List/MASK_FILE[@group_id='{}']"
                    xnodes_in = xml_tools.get_all_values(
                        self._l1_image_info.MuscateData["Node_Useful_Image"],
                        l_XPathRootUSI_In.format(l_grpSuffix))
                    # Get the path in the xml product filename
                    lPath = os.path.dirname(self._l1_image_info.HeaderFilename)
                    for node_in in xnodes_in:
                        l_FullPathFilename = os.path.join(lPath, node_in.text)
                        # Expand threshold the file
                        usi_resampled = l_BaseL2FullMASKSFilename + "_USI_" + l_grpSuffix + ".tif"\
                                        + file_utils.get_extended_filename_write_mask_file_muscate()
                        resample(l_FullPathFilename, self._dtm.ALTList[resol],
                                                    usi_resampled, threshold=0.25, method=OtbResampleType.LINEAR, write_output=True)

                    else:
                        LOGGER.debug("No 'Useful_Image' mask detected in the L1 product.")
                # Fin si manage USI

                # START WRITING DFP Image file DATA (=DFP in MUSCATE) #TODO
                if self._l2dfpimagelist is not None:
                    param_dfp_binconcat = {"im":  self._l2dfpimagelist[resol],
                                           "out": l_BaseL2FullMASKSFilename + "_DFP_" + l_grpSuffix + ".tif"
                                           + file_utils.get_extended_filename_write_mask_file_muscate()
                                           }
                    dfp_binconcat_app = OtbAppHandler("BinaryConcatenate", param_dfp_binconcat, write_output=True)
                else:
                    LOGGER.debug("DFP Masks not available.")

                # START WRITING EDG Image file DATA
                otb_file_utils.write_images([self._l2edgimagelist[resol]], [l_BaseL2FullMASKSFilename + "_EDG_" +
                                                                            l_grpSuffix + ".tif" + file_utils.get_extended_filename_write_mask_file_muscate()])

                # START WRITING CLM (CLD) Image file DATA
                # Connect the CLD image
                # Connect the CLD image
                # -------------------------------------
                self.write_cld_image(self._l2cldlist[resol], p_CLDDataBandsSelected,
                                   l_BaseL2FullMASKSFilename + "_CLM_" +
                                   l_grpSuffix + ".tif")
                LOGGER.debug("Writing L2 resolution image done !")

            # *************************************************************************************************************
            # ****  END LOOP on RESOLUTION   *****************************************
            # *************************************************************************************************************
            # *************************************************************************************************************
            # WARNING : For simplicity, the SOL and VIE images (and headers) are written by the L2HeaderFileWriter
            # *************************************************************************************************************
