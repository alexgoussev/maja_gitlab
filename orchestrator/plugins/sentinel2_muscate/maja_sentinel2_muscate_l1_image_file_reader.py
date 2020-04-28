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

orchestrator.plugins.sentinel2.maja_sentinel2_l1_image_file_reader -- shortdesc

orchestrator.plugins.maja_sentinel2_l1_image_file_reader is a description

It defines classes_and_methods

###################################################################################################

:copyright: 2019 CNES. All rights reserved.
:license: license

###################################################################################################
"""
import os
import math
from orchestrator.common.logger.maja_logging import configure_logger
from orchestrator.common.maja_exceptions import MajaDataException, MajaExceptionPluginSentinel2Muscate
from orchestrator.cots.otb.otb_app_handler import OtbAppHandler
from orchestrator.cots.otb.algorithms.otb_resample import resample
from orchestrator.cots.otb.algorithms.otb_resample import OtbResampleType
from orchestrator.cots.otb.otb_pipeline_manager import OtbPipelineManager
from orchestrator.cots.otb.algorithms.otb_constant_image import constant_image
from orchestrator.cots.otb.algorithms.otb_angle_list_to_image import angle_list_to_image
from orchestrator.cots.otb.algorithms.otb_extract_roi import extract_roi
from orchestrator.plugins.common.sentinel2_base.maja_sentinel2_l1_image_file_reader_base import \
    Sentinel2L1ImageFileReaderBase
from orchestrator.plugins.sentinel2_muscate.maja_sentinel2_muscate_plugin import MajaSentinel2MuscatePlugin
from orchestrator.common.constants import ReadL1Mode
import orchestrator.common.xml_tools as xml_tools
from orchestrator.algorithms.grid_to_angle import grid_to_angle
from orchestrator.common.interfaces.maja_xml_input_angles import MajaInternalXmlInputAngles

LOGGER = configure_logger(__name__)


class Sentinel2MuscateL1ImageFileReader(Sentinel2L1ImageFileReaderBase):

    def __init__(self):
        super(Sentinel2MuscateL1ImageFileReader, self).__init__()
        self._Satellite = "SENTINEL2"
        self._plugin = MajaSentinel2MuscatePlugin()
        self._toa_pipeline = OtbPipelineManager()
        self._l2_dfp_pipeline = OtbPipelineManager()
        self._l2_sat_pipeline = OtbPipelineManager()
        self._l2_detf_pipeline = OtbPipelineManager()
        self._l2_zone_pipeline = OtbPipelineManager()
        self.m_headerHandler = None
        self._band_zone_map = {}

    def can_read(self, plugin_name):
        return plugin_name == "SENTINEL2_MUSCATE"

    def generate_toa(self, listOfTOAImageFileNames, reflectanceMultiplicationValues, working):
        """
        :param listOfTOAImageFileNames: ListOfStrings
        :param reflectanceMultiplicationValues: ListOfDoubles
        :return:
        :rtype: string
        """
        if len(reflectanceMultiplicationValues) != len(listOfTOAImageFileNames):
            raise MajaDataException("Not the same number of band images and coefficients")
        # Init the projRef
        l_ProjectionRef = ""
        # =======> GENERATE TOA CACHING
        l_ProjectionRef = self.generate_toa_caching(listOfTOAImageFileNames, reflectanceMultiplicationValues, working)
        LOGGER.debug("Caching TOA images done ...")
        return l_ProjectionRef

    def generate_sat_images(self, working_dir):
        """
        :return:
        """
        # *******************************************************************************************************
        # IPSAT Sub image pipeline connection
        # *******************************************************************************************************
        out_concatenate = os.path.join(working_dir, "SubSatVector.tif")
        param_concatenate = {"il": self._satmasksublist,
                             "out": out_concatenate + ":uint8"
                             }
        concat_app = OtbAppHandler("ConcatenateImages", param_concatenate)
        self._subsatimage = concat_app.getoutput().get("out")

    def generate_mask_rasters(
            self,
            satPixFileNames,
            defectivPixFileNames,
            zoneMaskFileNames,
            noDataMaskFileNames,
            p_ListOfTOABandCode,
            working):
        """

        :param satPixFileNames: ListOfStrings
        :param defectivPixFileNames: ListOfStrings
        :param zoneMaskFileNames: ListOfStrings
        :param noDataMaskFileNames: ListOfStrings
        :param p_ListOfTOABandCode: ListOfStrings
        :param working: string
        :return:
        """

        # *******************************************************************************************************
        # Generate mask rasters by rasterizing the gml mask per L2 resolution per band
        # *******************************************************************************************************
        LOGGER.info("Starting GenerateMaskRasters")

        l_BandsDefinitions = self._plugin.BandsDefinitions
        l2Area = None
        l_ListOfL2Resolution = l_BandsDefinitions.ListOfL2Resolution  # ListOfStrings
        l_NbL2Res = len(l_ListOfL2Resolution)
        l_ListOfL1Resolution = l_BandsDefinitions.ListOfL1Resolution  # ListOfStrings
        l_NbL1Res = len(l_ListOfL1Resolution)
        l_NbL1Band = len(defectivPixFileNames)
        dtm_coarse = self._dem.ALC

        # Set a constant image if the gml masks are empty
        tmp_constant_filename = os.path.join(working, "Masks_const.tif")
        #constant_image(dtm_coarse, 0, tmp_constant_filename, write_output=True)

        # Initialize the L2 Elements
        for l2res in range(l_NbL2Res):
            self._l2defectmasklist.append([])
            self._l2zonemasklist.append([])
            self._l2satimagelist.append([])
            self._l2dfpimagelist.append(None)
            self._l2zoneimagelist.append(None)
        # Init the coarse elements
        for coarseband in p_ListOfTOABandCode:
            self._satmasksublist.append(None)
            self._nodatamasksublist.append(None)
            self._zonemasksublist.append(None)
            self._l2satmasklist.append(None)

        # Loop on L1Res
        for l1res in range(l_NbL1Res):
            # Current resolution: "R1" or "R2" or "R3"
            curL1Res = l_ListOfL1Resolution[l1res]

            # Get the list of band of the current resolution
            listOfL1Bands = l_BandsDefinitions.get_list_of_l1_band_code(curL1Res)
            nbL1Bands = len(listOfL1Bands)
            # For each band of the current resolution
            l_l2zone_pipeline = OtbPipelineManager()
            firstBandIdx = l_BandsDefinitions.get_band_id_in_l1(listOfL1Bands[-1])

            # Verify if we can optimize the work if its the same file for all bands of
            # the resolution and if the bands are in correct bit order
            l_strDefectFileNameRef = defectivPixFileNames[firstBandIdx]
            l_isDefectSameFilesForBands = True
            l_strSatFileNameRef = satPixFileNames[firstBandIdx]
            l_isSatSameFilesForBands = True
            l_strNoDataFileNameRef = noDataMaskFileNames[firstBandIdx]
            l_isNoDataSameFilesForBands = True
            for l_BandIdxL1 in range(len(listOfL1Bands)):
                # Get the L1 band index associated to the L2 band code
                l_StrBandIdL1 = listOfL1Bands[l_BandIdxL1]
                l1BandIdx = l_BandsDefinitions.get_band_id_in_l1(l_StrBandIdL1)
                # Filenameverify
                if l_strDefectFileNameRef != defectivPixFileNames[l1BandIdx]:
                    l_isDefectSameFilesForBands = False
                if l_strSatFileNameRef != satPixFileNames[l1BandIdx]:
                    l_isSatSameFilesForBands = False
                if l_strNoDataFileNameRef != noDataMaskFileNames[l1BandIdx]:
                    l_isNoDataSameFilesForBands = False
            LOGGER.debug("l_isDefectSameFilesForBands = " + str(l_isDefectSameFilesForBands))
            LOGGER.debug("l_isSatSameFilesForBands = " + str(l_isSatSameFilesForBands))
            LOGGER.debug("l_isNoDataSameFilesForBands = " + str(l_isSatSameFilesForBands))

            # Defective PIX (only in L2 resolution)
            if l_isDefectSameFilesForBands:
                if curL1Res in l_ListOfL2Resolution:
                    l_StrBandIdL1 = listOfL1Bands[0]
                    l1BandIdx = l_BandsDefinitions.get_band_id_in_l1(l_StrBandIdL1)
                    LOGGER.debug("l_StrBandIdL1 : ")
                    LOGGER.debug(l_StrBandIdL1)
                    self._l2piximagelist.append(defectivPixFileNames[l1BandIdx])
                    dfp_mask = os.path.join(working, "L1_DFP_Masks_{}.tif".format(curL1Res))
                    param_bintovec_dfp = {"im": defectivPixFileNames[l1BandIdx],
                                          "out": dfp_mask + ":uint8",
                                          "nbcomp": nbL1Bands
                                          }
                    dfp_mask_app = OtbAppHandler("BinaryToVector", param_bintovec_dfp, write_output=True)
                    self._l2dfpimagelist[l_ListOfL2Resolution.index(curL1Res)] = dfp_mask_app.getoutput().get("out")
            else:
                raise MajaExceptionPluginSentinel2Muscate("Product format not supported : not the same file for band on PIX")

            # SAT Mask generation
            if l_isSatSameFilesForBands:
                # Sat Masks generation
                l_StrBandIdL1 = listOfL1Bands[0]
                l1BandIdx = l_BandsDefinitions.get_band_id_in_l1(l_StrBandIdL1)
                l_SATFFilename = satPixFileNames[l1BandIdx]
                sat_mask = os.path.join(working, "L1_SAT_Masks_{}.tif".format(curL1Res))
                param_bintovec_dfp = {"im": l_SATFFilename,
                                      "out": sat_mask + ":uint8",
                                      "nbcomp": nbL1Bands
                                      }
                sat_mask_app = OtbAppHandler("BinaryToVector", param_bintovec_dfp, write_output=True)
                # self._l2_sat_pipeline.add_otb_app(sat_mask_app)
                if curL1Res in l_ListOfL2Resolution:
                    self._l2satmasklist[l_ListOfL2Resolution.index(curL1Res)] = sat_mask_app.getoutput().get("out")
                for l1band in listOfL1Bands:
                    l1BandIdx = l_BandsDefinitions.get_band_id_in_l1(l1band)
                    tmp_sat_roi = os.path.join(working, "tmp_extract_roi_sat_{}.tif".format(l1band))
                    tmp_sat_roi_app = extract_roi(sat_mask_app.getoutput().get("out"),
                                                  [self.m_headerHandler.get_l1_sat_image_index(l1BandIdx) - 1],
                                                  tmp_sat_roi, write_output=False)
                    tmp_sat_resample = os.path.join(working, "tmp_extract_roi_sat_resample_{}.tif".format(l1band))
                    resample(tmp_sat_roi_app.getoutput().get("out"), dtm_coarse, tmp_sat_resample,
                             OtbResampleType.LINEAR)
                    self._satmasksublist[l1BandIdx] = tmp_sat_resample
            else:
                raise MajaExceptionPluginSentinel2Muscate("Product format not supported : not the same file for band on SAT")

            # No_data mask at L2 coarse
            if l_isNoDataSameFilesForBands:
                ndt_mask = os.path.join(working, "L2_NDT_VecMasks_{}.tif".format(curL1Res))
                l_StrBandIdL1 = listOfL1Bands[0]
                l1BandIdx = l_BandsDefinitions.get_band_id_in_l1(l_StrBandIdL1)
                l_NoDataFilename = noDataMaskFileNames[l1BandIdx]
                param_bintovec_ndt = {"im": l_NoDataFilename,
                                      "out": ndt_mask + ":uint8",
                                      "nbcomp": nbL1Bands
                                      }
                ndt_mask_app = OtbAppHandler("BinaryToVector", param_bintovec_ndt, write_output=True)
                tmp_ndt_resample = os.path.join(working, "tmp_extract_roi_ndt_resample_{}.tif".format(curL1Res))
                ndt_resamp_app = resample(
                    ndt_mask_app.getoutput().get("out"),
                    dtm_coarse,
                    tmp_ndt_resample,
                    OtbResampleType.LINEAR,
                    write_output=True)
                for l1band in listOfL1Bands:
                    l1BandIdx = l_BandsDefinitions.get_band_id_in_l1(l1band)
                    tmp_ndt_roi = os.path.join(working, "tmp_extract_roi_ndt_{}.tif".format(l1band))
                    tmp_ndt_roi_app = extract_roi(ndt_resamp_app.getoutput().get("out"),
                                                  [self.m_headerHandler.get_l1_ndt_image_index(l1BandIdx) - 1],
                                                  tmp_ndt_roi, write_output=True)
                    self._nodatamasksublist[l1BandIdx] = tmp_ndt_roi_app.getoutput().get("out")
            else:
                raise MajaExceptionPluginSentinel2Muscate("Product format not supported : not the same file for band on NoData")

            # Detectors FootPrint Masks Generation
            # Test if they all refers to the same files
            l_bin_to_vec_zone_map = {}
            for l_BandIdxL1 in range(len(listOfL1Bands)):
                # Get the L1 band index associated to the L2 band code
                l_StrBandIdL1 = listOfL1Bands[l_BandIdxL1]
                l1BandIdx = l_BandsDefinitions.get_band_id_in_l1(l_StrBandIdL1)
                LOGGER.debug("Sentinel2MuscateL1ImageFileReader::GenerateMaskRasters: CurrentResol = %s, reading the "
                             "BandId L1 (associated) <%s> with index <%s>.", curL1Res, l_StrBandIdL1,
                             l1BandIdx)
                # Detectors FootPrint Masks
                l_bandDetFnames = zoneMaskFileNames[l1BandIdx]
                l_ListOfZone = self.m_headerHandler.get_list_of_zones(listOfL1Bands[l_BandIdxL1])
                bandmath_expr = "max(0 "
                nbDetector = len(l_ListOfZone)
                # For each detector of the current band
                l_listOfZoneInput = []
                for det in range(nbDetector):
                    detFname = l_bandDetFnames[l_ListOfZone[det]]
                    l_det_band_idx = self.m_headerHandler.get_l1_dtf_image_index(l1BandIdx, l_ListOfZone[det])[0]
                    vec_zone_output = None
                    if not os.path.basename(detFname) in list(l_bin_to_vec_zone_map.keys()):
                        detf_mask = os.path.join(
                            working, "L1_DETF_Masks_{}_{}.tif".format(
                                l1BandIdx, l_ListOfZone[det]))
                        param_bintovec_detf = {
                            "im": detFname,
                            "out": detf_mask,
                            "nbcomp": self.m_headerHandler.get_l1_dtf_max_image_index(
                                l_ListOfZone[det])}
                        detf_mask_app = OtbAppHandler("BinaryToVector", param_bintovec_detf, write_output=True)
                        self._l2_detf_pipeline.add_otb_app(detf_mask_app)
                        vec_zone_output = detf_mask_app.getoutput().get("out")
                        l_bin_to_vec_zone_map[os.path.basename(detFname)] = vec_zone_output
                    else:
                        vec_zone_output = l_bin_to_vec_zone_map[os.path.basename(detFname)]
                    l_listOfZoneInput.append(vec_zone_output)
                    bandmath_expr = bandmath_expr + ", im" + \
                        str(det + 1) + "b" + str(l_det_band_idx) + " * " + str(int(l_ListOfZone[det])) + " "
                bandmath_expr = bandmath_expr + ")"
                LOGGER.debug("expression: " + bandmath_expr)
                LOGGER.debug(l1BandIdx)
                tmp_zone = os.path.join(working, "tmp_zone_{}".format(l1BandIdx))
                param_bandmath_zone = {"il": l_listOfZoneInput,
                                       "exp": bandmath_expr,
                                       "out": tmp_zone
                                       }
                zone_bandmath_app = OtbAppHandler("BandMath", param_bandmath_zone, write_output=True)
                # self._l2_zone_pipeline.add_otb_app(zone_bandmath_app)

                if curL1Res in l_ListOfL2Resolution:
                    self._l2zonemasklist[l_ListOfL2Resolution.index(curL1Res)].append(
                        zone_bandmath_app.getoutput().get("out"))
                tmp_zone_band_math = os.path.join(working, "tmp_zone_band_math_{}".format(l1BandIdx))
                masterExpr = "( im1b1 > 0 ) ? im1b1 : -10000"
                param_bandmath_zone = {"il": [zone_bandmath_app.getoutput().get("out")],
                                       "exp": masterExpr,
                                       "out": tmp_zone_band_math
                                       }
                zone_thresh_bandmath_app = OtbAppHandler("BandMath", param_bandmath_zone, write_output=True)
                # LAIG-FA-MAC-1652-CNES : probleme reech detecteur en unsigned char : detecteur 1 devient 0.....
                tmp_zone_resample = os.path.join(working, "tmp_extract_roi_zone_resample_{}.tif".format(l1BandIdx))
                zone_resample_app = resample(
                    zone_thresh_bandmath_app.getoutput().get("out"),
                    dtm_coarse,
                    tmp_zone_resample,
                    OtbResampleType.LINEAR,
                    write_output=True)
                # threshold everything negative to 0
                Thresholdexpr = "im1b1 > 0 ? im1b1 : 0"
                tmp_zone_threshold = os.path.join(working, "tmp_zone_threshold_{}".format(l1BandIdx))
                param_bandmath_zone_threshold = {"il": [zone_resample_app.getoutput().get("out")],
                                                 "exp": Thresholdexpr,
                                                 "out": tmp_zone_threshold
                                                 }
                zone_bandmath_threshold_app = OtbAppHandler(
                    "BandMath", param_bandmath_zone_threshold, write_output=False)
                # Rounding
                tmp_zone_round = os.path.join(working, "tmp_zone_round_{}".format(l1BandIdx))
                param_bandmath_zone_round = {"im": zone_bandmath_threshold_app.getoutput().get("out"),
                                             "out": tmp_zone_round
                                             }
                zone_round_app = OtbAppHandler("RoundImage", param_bandmath_zone_round)
                # Add to the official output
                self._zonemasksublist[l1BandIdx] = zone_round_app.getoutput().get("out")
                # Log current loop
                LOGGER.debug("band loop: " + str(l_BandIdxL1 + 1) + " / " + str(nbL1Bands) + " (" + curL1Res + ")")
            # band loop
            LOGGER.debug("band loop: END")
            self._l2_detf_pipeline.free_otb_app()

            # L2 Zone mask pipeline connection
            if curL1Res in l_ListOfL2Resolution:
                l2_zone_image = os.path.join(working, "l2_zone_mask_{}.tif".format(curL1Res))
                param_l2zone_concatenate = {"il": self._l2zonemasklist[l_ListOfL2Resolution.index(curL1Res)],
                                            "out": l2_zone_image
                                            }
                l2_zone_app = OtbAppHandler("ConcatenateImages", param_l2zone_concatenate)
                self._l2zoneimagelist[l_ListOfL2Resolution.index(curL1Res)] = l2_zone_app.getoutput().get("out")

            # end res loop

    def GetViewingGrids(
            self,
            band,
            nbL1Bands,
            vieHRef,
            satFilename,
            zoneFilenames,
            nodataFilename,
            listOfZone,
            view_angle_col_step,
            view_angle_row_step,
            viewing_angles_zenith,
            viewing_angles_azimuth,
            working):
        LOGGER.debug("GetViewingGrids - Band: " + band)

        dtm_coarse = self._dem.ALC
        l_BandsDefinitions = self._plugin.BandsDefinitions
        l1BandIdx = l_BandsDefinitions.get_band_id_in_l1(band)
        # Set a constant image if the gml masks are empty
        tmp_constant_filename = os.path.join(working, "Masks_sat_const.tif")
        constant_image(dtm_coarse, 0, tmp_constant_filename, write_output=True)

        # Generate masks at L2 coarse resolution
        # to generate the viewing grids

        # Saturated pixel mask at L2 coarse
        # The band has not been filled yet in GenerateMaskRaster
        """sat_mask = os.path.join(working, "L2_SAT_VecMasks_{}.tif".format(band))
        param_bintovec_sat = {"im": satFilename,
                              "out": sat_mask + ":uint8",
                              "nbcomp": nbL1Bands
                              }
        sat_mask_app = OtbAppHandler("BinaryToVector", param_bintovec_sat,write_output=True)
        tmp_sat_roi = os.path.join(working, "tmp_extract_roi_sat_{}.tif".format(band))
        tmp_sat_roi_app = extract_roi(sat_mask_app.getoutput().get("out"), [self.m_headerHandler.get_L1_SAT_image_index(l1BandIdx) - 1],
                                      tmp_sat_roi,write_output=False)
        tmp_sat_resample = os.path.join(working, "tmp_extract_roi_sat_resample_{}.tif".format(band))
        resample(tmp_sat_roi_app.getoutput().get("out"), dtm_coarse, tmp_sat_resample, OtbResampleType.LINEAR)
        self._satmasksublist.append(tmp_sat_resample)

        # No_data mask at L2 coarse
        ndt_mask = os.path.join(working, "L2_NDT_VecMasks_{}.tif".format(band))
        param_bintovec_ndt = {"im": nodataFilename,
                              "out": ndt_mask + ":uint8",
                              "nbcomp": nbL1Bands
                              }
        ndt_mask_app = OtbAppHandler("BinaryToVector", param_bintovec_ndt,write_output=True)
        tmp_ndt_roi = os.path.join(working, "tmp_extract_roi_ndt_{}.tif".format(band))
        tmp_ndt_roi_app = extract_roi(ndt_mask_app.getoutput().get("out"), [self.m_headerHandler.get_l1_ndt_image_index(l1BandIdx) - 1],
                                      tmp_ndt_roi,write_output=False)
        tmp_ndt_resample = os.path.join(working, "tmp_extract_roi_ndt_resample_{}.tif".format(band))
        resample(tmp_ndt_roi_app.getoutput().get("out"), dtm_coarse, tmp_ndt_resample, OtbResampleType.LINEAR)
        self._nodatamasksublist.append(tmp_ndt_resample)

        # Detectors FootPrint
        # TODO: FLIP
        bandDetFnames = zoneFilenames
        bandmath_sstm =  "max(0 "
        id = 0
        # For each detector of the current band
        zone_bandmath_app = None
        if not l1BandIdx in self._band_zone_map:
            l_listOfZoneInput = []
            for detid, detFname in bandDetFnames.iteritems():
                zone_mask = os.path.join(working, "L2_ZONE_VecMasks_{}.tif".format(band))
                param_bintovec_zone = {"im": detFname,
                                      "out": zone_mask + ":uint8",
                                      "nbcomp": 16
                                      }
                zone_mask_app = OtbAppHandler("BinaryToVector", param_bintovec_zone,write_output=True)
                l_det_band_idx = self.m_headerHandler.get_l1_dtf_image_index(l1BandIdx, detid)[0]
                LOGGER.debug("detFname: "+ detFname + " - detId: " + detid + " - bit_number: " + str(self.m_headerHandler.get_l1_dtf_image_index(l1BandIdx, detid)[0]))
                l_listOfZoneInput.append(zone_mask_app.getoutput().get("out"))
                bandmath_sstm = bandmath_sstm + ", im" + str(id + 1) + "b"+str(l_det_band_idx) + " * " + detid + " "
                id = id + 1
            bandmath_sstm = bandmath_sstm + ")"
            masterExpr = "(" + bandmath_sstm + " > 0) ? " + bandmath_sstm + " : -10000"
            tmp_zone = os.path.join(working, "tmp_zone_{}".format(band))
            param_bandmath_zone = {"il": l_listOfZoneInput,
                                   "exp": masterExpr,
                                   "out": tmp_zone
                                   }
            zone_bandmath_app = OtbAppHandler("BandMath", param_bandmath_zone,write_output=True)
        else:
            tmp_zone = os.path.join(working, "tmp_zone_{}".format(band))
            masterExpr = "( im1b1 > 0 ) ? im1b1 : -10000"
            param_bandmath_zone = {"il": [self._band_zone_map[l1BandIdx]],
                                   "exp": masterExpr,
                                   "out": tmp_zone
                                   }
            zone_bandmath_app = OtbAppHandler("BandMath", param_bandmath_zone, write_output=True)

        # LAIG-FA-MAC-1652-CNES : probleme reech detecteur en unsigned char : detecteur 1 devient 0.....
        tmp_zone_resample = os.path.join(working, "tmp_extract_roi_zone_resample_{}.tif".format(band))
        zone_resample_app = resample(zone_bandmath_app.getoutput().get("out"), dtm_coarse, tmp_zone_resample, OtbResampleType.LINEAR)

        # threshold everything negative to 0
        Thresholdexpr = "im1b1 > 0 ? im1b1 : 0"
        tmp_zone_threshold = os.path.join(working, "tmp_zone_threshold_{}".format(band))
        param_bandmath_zone_threshold = {"il": [zone_resample_app.getoutput().get("out")],
                               "exp": Thresholdexpr,
                               "out": tmp_zone_threshold
                               }
        zone_bandmath_threshold_app = OtbAppHandler("BandMath", param_bandmath_zone_threshold,write_output=True)
        #Rounding
        tmp_zone_round = os.path.join(working, "tmp_zone_round_{}".format(band))
        param_bandmath_zone_round = {"im": zone_bandmath_threshold_app.getoutput().get("out"),
                                     "out": tmp_zone_round
                                     }
        zone_round_app = OtbAppHandler("RoundImage", param_bandmath_zone_round)
        # Add to the official output
        self._zonemasksublist.append(zone_round_app.getoutput().get("out"))
"""
        # ---- Viewing angle Grid --------------------------------------------------------------------
        l_VieAnglesGridList = []
        l_nbDetectors = len(viewing_angles_azimuth)
        # Detector loop
        LOGGER.debug("For each detectors (nb=%s) ...", l_nbDetectors)
        for detId in range(len(viewing_angles_azimuth)):
            # Generate an image with the list of viewing angle values set in the header file
            det = listOfZone[detId]
            LOGGER.debug("ZenithViewingAngles for band " + band + " and det " + det + " ,  nb values: " + str(
                len(viewing_angles_zenith[detId])))
            LOGGER.debug(viewing_angles_zenith[detId])
            LOGGER.debug("AzimuthViewingAngles " + band + " and det " + det + " nb values: " + str(
                len(viewing_angles_azimuth[detId])))
            LOGGER.debug(viewing_angles_azimuth[detId])
            output_filename = "/tmp/internal_angles_test_{}_{}.xml".format(band, det)
            LOGGER.debug("Angles output_filename : %s", output_filename)
            writer = MajaInternalXmlInputAngles(viewing_angles_zenith[detId],
                                                viewing_angles_azimuth[detId],
                                                view_angle_col_step, view_angle_row_step, output_filename)
            writer.write()
            if not os.path.exists(output_filename):
                raise MajaExceptionPluginSentinel2Muscate("File does not exist " + output_filename)

            viewing_grid_filename = os.path.join(working, "viewing_grid_{}_{}.tif".format(det, band))

            # angle_list_to_image()
            viewing_angle_app = angle_list_to_image(dtm_coarse, output_filename, viewing_grid_filename,
                                                    extrapolation=True,
                                                    write_output=True)

            # Expand at L2Coarse.
            viewing_grid_resamp_filename = os.path.join(working,
                                                        "viewing_grid_resamp_{}_{}.tif".format(detId, band))
            resample(viewing_angle_app.getoutput().get("out"), dtm_coarse, viewing_grid_resamp_filename,
                     OtbResampleType.LINEAR)

            # add images in a list
            l_VieAnglesGridList.append(viewing_grid_resamp_filename)
            # end detector loop

        # Generate the angle images using the zone (detector) mask
        LOGGER.debug("Start ConcatenatePerZoneVectorImageFilter for band id [" + band + "]...")

        # Concatenate all the detectors
        viewing_concat_filename = os.path.join(working, "viewing_concat_{}.tif".format(band))
        param_concat_perzone = {"mask": self._zonemasksublist[l1BandIdx],
                                "il": l_VieAnglesGridList,
                                "zonelist": listOfZone,
                                "out": viewing_concat_filename
                                }
        concat_perzone_app = OtbAppHandler("ConcatenatePerZone", param_concat_perzone, write_output=True)
        # Multiply by reference altitude
        viewing_grid_mult_filename = os.path.join(working, "viewing_grid_mult_{}.tif".format(band))
        param_scaled_solar = {"im": concat_perzone_app.getoutput().get("out"),
                              "coef": float(vieHRef),
                              "out": viewing_grid_mult_filename
                              }
        view_scale_app = OtbAppHandler("MultiplyByScalar", param_scaled_solar, write_output=True)
        self._vieimagelist.append(view_scale_app.getoutput().get("out"))

        l_nbZones = len(listOfZone)
        LOGGER.debug("Start Loop for Zone (nb=" + str(l_nbZones) + ")...")
        for d in range(l_nbZones):
            l_zone = listOfZone[d]
            # -----------------------------------------------------------------------------------
            # Compute average values of zenithal and azimuthal angles grid per zone (detector in level1B)
            # -----------------------------------------------------------------------------------
            # VAP Reader connection (from ATB)
            tmp_azi = os.path.join(working, "tmp_azi_{}_{}.tif".format(band, l_zone))
            tmp_azi_image = extract_roi(l_VieAnglesGridList[d], [1], tmp_azi)
            param_stats = {"im": tmp_azi,
                           "exclude": 1,
                           "mask": self._zonemasksublist[l1BandIdx],
                           "maskforeground": int(l_zone)
                           }
            l2_stat = OtbAppHandler("Stats", param_stats)

            azi_mean = l2_stat.getoutput().get("mean")
            tmp_zen = os.path.join(working, "tmp_zen_{}_{}.tif".format(band, l_zone))
            tmp_zen_app = extract_roi(l_VieAnglesGridList[d], [0], tmp_zen)
            param_stats = {"im": tmp_zen_app.getoutput().get("out"),
                           "exclude": 1,
                           "mask": self._zonemasksublist[l1BandIdx],
                           "maskforeground": int(l_zone)
                           }
            l2_stat = OtbAppHandler("Stats", param_stats)
            zen_mean = l2_stat.getoutput().get("mean")
            tmp_mean = (zen_mean, azi_mean)
            l_ViewingAngleMean = grid_to_angle(tmp_mean)
            l_ViewingAngleMeanDeg = (l_ViewingAngleMean[0] * 180.0 / math.pi, l_ViewingAngleMean[1] * 180.0 / math.pi)
            # Add a vector to mean maps
            if l_zone not in self._meanZenithMap:
                self._meanZenithMap[listOfZone[d]] = []
            if l_zone not in self._meanAzimuthMap:
                self._meanAzimuthMap[listOfZone[d]] = []
            self._meanZenithMap[listOfZone[d]].append(str(l_ViewingAngleMeanDeg[0]))
            self._meanAzimuthMap[listOfZone[d]].append(str(l_ViewingAngleMeanDeg[1]))
            LOGGER.debug(" For BandId[" +
                         str(band) +
                         "], zone [" +
                         str(listOfZone[d]) +
                         "]  . Mean 'GRID View angles'=" +
                         str(tmp_mean) +
                         " . Mean 'View angles'=" +
                         str(l_ViewingAngleMean[0]) +
                         ":" +
                         str(l_ViewingAngleMean[1]) +
                         " rad. ou  " +
                         str(l_ViewingAngleMeanDeg[0]) +
                         ":" +
                         str(l_ViewingAngleMeanDeg[1]) +
                         " deg.")
        LOGGER.debug("Start Loop for Zone done.")

    # Can read method

    def read(self, product_info, app_handler, l2comm, dem, pReadL1Mode):
        """product_info,plugin, l2comm,mode

        :param product_info: L1ImageInformationsBase
        :param pReadL1Mode: ReadL1ModeType
        :return:
        """
        LOGGER.info("Start Sentinel2Muscate L1 ImageFileReader ...")
        product_filename = product_info.HeaderFilename
        LOGGER.info("Start Sentinel2Muscate L1 ImageFileReader with filename : " + product_filename)
        working_dir = app_handler.get_directory_manager().get_temporary_directory("L1Read_",
                                                                                  do_always_remove=True)
        self._plugin.initialize(app_handler)
        self._GIPPL2COMMHandler = l2comm
        LOGGER.info("Start Sentinel2Muscate L1 ImageFileReader ...")
        self._ReadL1Mode = pReadL1Mode
        self._dem = dem

        # --------------------------------------
        # Check the extension of th efile. For Muscate, must be .XML (in upper case)
        IsValidSatellite = (product_info.HeaderHandler is not None)
        if not IsValidSatellite:
            raise MajaExceptionPluginSentinel2Muscate(
                "The file <{}> is not a valid Sentinel2 L1 product.".format(product_filename))
        self.m_headerHandler = product_info.HeaderHandler
        # Get satellite name
        self.m_Satellite = product_info.Satellite

        # --------------------------------------
        # Load the header tile file in the xml tile handler to read tile information
        xmlTileFilename = product_info.xmlTileFilename
        l_BandsDefinitions = self._plugin.BandsDefinitions  # BandsDefinitions

        # TOA & masks Reader connection
        l_ListOfTOAImageFileNames = product_info.HeaderHandler.get_list_of_toa_image_filenames()
        l_SatPixFileNames = product_info.HeaderHandler.get_list_of_l1_sat_image_filenames()
        l_DefectivPixFileNames = product_info.HeaderHandler.get_list_of_defective_pixel_image_filenames()
        l_ZoneMaskFileNames = product_info.HeaderHandler.get_map_list_of_detector_footprint_image_filenames()
        l_NoDataMaskFileNames = product_info.HeaderHandler.get_list_of_l1_ndt_image_filenames()
        l_ListOfTOABandCode = product_info.HeaderHandler.get_list_of_band_code()  # ListOfStrings
        l_ListOfL1Resolution = l_BandsDefinitions.ListOfL1Resolution  # ListOfStrings
        l_ListOfL2Resolution = l_BandsDefinitions.ListOfL2Resolution  # ListOfStrings
        l_NbBand = len(l_ListOfTOAImageFileNames)  # int

        l_L1NoData = product_info. L1NoData
        l_ReflectanceQuantificationValue = product_info.ReflectanceQuantification
        l_RealL1NoData = l_L1NoData * l_ReflectanceQuantificationValue  # RealNoDataType

        if (len(l_ListOfTOABandCode) != len(l_ListOfTOAImageFileNames)) or (
                len(l_ListOfTOABandCode) != len(l_SatPixFileNames)) or (
                len(l_ListOfTOABandCode) != len(l_DefectivPixFileNames)):
            raise MajaExceptionPluginSentinel2Muscate(
                "Sentinel2L1ImageFileReader.CanRead: Internal error: The number of image file, sat file and band code are different !")

        # =======> GENERATE TOA
        # Get calibration coeffs if activated
        l_reflectanceMultiplicationValues = []  # ListOfDoubles
        if xml_tools.as_bool(l2comm.get_value("CalAdjustOption")):
            l_factors = xml_tools.as_float_list(l2comm.get_value("CalAdjustFactor"))
            if len(l_factors) != len(l_ListOfTOABandCode):
                raise MajaDataException(
                    "Not the same number of Calibration coeffs than L1 bands ( {}, {} )".format(len(l_factors), len(
                        l_ListOfTOABandCode)))
            for i in range(len(l_ListOfTOABandCode)):
                l_reflectanceMultiplicationValues.append(l_ReflectanceQuantificationValue * l_factors[i])
        else:
            for i in range(len(l_ListOfTOABandCode)):
                l_reflectanceMultiplicationValues.append(l_ReflectanceQuantificationValue)

        l_ProjectionRef = self._dem.ProjRef
        self.generate_toa(l_ListOfTOAImageFileNames, l_reflectanceMultiplicationValues, working_dir)  # string

        #                                     START READ L1 for ALGORITHMS
        if pReadL1Mode == ReadL1Mode.READ_L1_MODE_FOR_ALGORITHMS:
            # --------------------------------------
            # Get information of areas (footprint) of the product (Origin, Spacing and Size for L2 and L2Coarse resolution)
            # --------------------------------------
            l_L2Dems = dem.ALTList
            l_CoarseDem = dem.ALC

            # =======> GENERATE TOA SUB IMAGES AT L2 COARSE RESOLUTION
            LOGGER.debug("Start SubSampling ...")
            self.generate_toa_sub_images(working_dir)
            LOGGER.debug("Start SubSampling done.")
            #  the gml mask per L2 resolution per band
            self.generate_mask_rasters(
                l_SatPixFileNames,
                l_DefectivPixFileNames,
                l_ZoneMaskFileNames,
                l_NoDataMaskFileNames,
                l_ListOfTOABandCode,
                working_dir)

            LOGGER.debug("Filenames Mask Rasters : ")
            LOGGER.debug(l_SatPixFileNames)
            LOGGER.debug(l_DefectivPixFileNames)
            LOGGER.debug(l_ZoneMaskFileNames)
            LOGGER.debug(l_NoDataMaskFileNames)
            LOGGER.debug(l_ListOfTOABandCode)

            # Get the ref altitude
            l_CurrentConfigUserCamera = self._plugin.ConfigUserCamera
            grid_ref_alt = l_CurrentConfigUserCamera.get_Algorithms().get_GRID_Reference_Altitudes()
            l_VIEHRef = grid_ref_alt.get_VIEHRef()  # double
            l_SOLH1 = grid_ref_alt.get_SOLH1()  # double

            # IPSOL Sub image pipeline connection
            LOGGER.debug("Start IPSOL SubSampling ...")
            sun_angle_col_step = int(product_info.HeaderHandler.get_string_value_of("SunAngleColStep"))
            sun_angle_row_step = int(product_info.HeaderHandler.get_string_value_of("SunAngleRowStep"))
            # ATTENTION : * -1 for compatibility negative spacing
            LOGGER.debug("Angle Resolution Spacing computed in 5000 resolution: " +
                         str(sun_angle_col_step) + " , " + str(sun_angle_row_step))

            l_zenithSolarAngles = product_info.HeaderHandler.get_sun_zenithal_angles()
            l_azimuthSolarAngles = product_info.HeaderHandler.get_sun_azimuthal_angles()
            LOGGER.debug("ZenithSolarAngles nb values: " + str(len(l_zenithSolarAngles)))
            LOGGER.debug("AzimuthSolarAngles nb values: " + str(len(l_azimuthSolarAngles)))

            l_solarAngleFile = app_handler.get_directory_manager().get_temporary_file("sun_angles_") + ".xml"

            LOGGER.debug("Angles output_filename : %s", l_solarAngleFile)
            writer = MajaInternalXmlInputAngles(l_zenithSolarAngles,
                                                l_azimuthSolarAngles,
                                                sun_angle_col_step, sun_angle_row_step, l_solarAngleFile)
            writer.write()
            # =======> GENERATE SOLAR ANGLE GRIDS
            self.get_solar_grids(self._dem.ALC, l_solarAngleFile, l_SOLH1, working_dir)
            LOGGER.debug("Start IPSOL SubSampling done.")

            # IPVIE Sub image pipeline connection
            LOGGER.debug("Start IPVIE SubSampling ...")
            vie_angle_col_step = int(product_info.HeaderHandler.get_string_value_of("SunAngleColStep"))
            vie_angle_row_step = int(product_info.HeaderHandler.get_string_value_of("SunAngleRowStep"))
            LOGGER.debug("For each band ...")
            for l_band in l_ListOfTOABandCode:
                l1BandIdx = l_BandsDefinitions.get_band_id_in_l1(l_band)
                # Get the list of detectors (index)
                l_ListOfZone = product_info.HeaderHandler.get_list_of_zones(l_band)
                # Get the list of viewing angles in the header file of the tile
                l_zenithVieAngles = product_info.HeaderHandler.get_viewing_zenithal_angles(l_band)
                l_azimuthVieAngles = product_info.HeaderHandler.get_viewing_azimuthal_angles(l_band)
                if len(l_zenithVieAngles) != len(l_azimuthVieAngles):
                    raise MajaExceptionPluginSentinel2Muscate(
                        "The number of detector for viewing zenithal angles and viewing azimuthal angles is different or null !")

                # =======> GENERATE VIEWING ANGLE GRIDS
                self.GetViewingGrids(l_band, l_NbBand, l_VIEHRef, l_SatPixFileNames[l1BandIdx],
                                     l_ZoneMaskFileNames[l1BandIdx], l_NoDataMaskFileNames[l1BandIdx],
                                     l_ListOfZone, vie_angle_col_step, vie_angle_row_step,
                                     l_zenithVieAngles, l_azimuthVieAngles, working_dir)

            # end loop nbBand

            LOGGER.debug("Start IPVIE SubSampling done.")

            # To check mean angle values
            # TODO

            # L2DFP image pipeline connection
            # for (unsigned int i = 0; i < l_NbL2Res; i++)
            #    {
            #        MaskListToVectorImageFilterPointer l_L2DFPMaskListToVectorImageFilter = MaskListToVectorImageFilterType::New();
            #        l_L2DFPMaskListToVectorImageFilter->SetInput(this->m_L2DFPImageListVector.at(i));
            #        m_L2DFPMaskListToVectorImageFilterList.push_back(l_L2DFPMaskListToVectorImageFilter);
            #        this->m_L2DFPOutputList->PushBack(m_L2DFPMaskListToVectorImageFilterList.at(i)->GetOutput());
            #    }

            # IPEDGSub and L2EDG pipeline connection
            # =======> GENERATE EDG IMAGES
            self.generate_edg_images(working_dir)
            # L2 TOA image pipeline connection
            # =======> GENERATE L2 TOA IMAGES
            self.generate_l2_toa_images(working_dir)
            # IPSAT Sub and L2SAT image pipeline connection
            # =======> GENERATE SAT IMAGES
            self.generate_sat_images(working_dir)
            # CLA image pipeline connection
            # =======> GENERATE CLA IMAGES
            self.generate_cla_images(l_RealL1NoData, working_dir)

            # Fill the datas
            self.dict_of_vals[
                "IPEDGSubOutput"] = self._edgsubmask
            self.dict_of_vals[
                "SOL1Image"] = self._sol1image
            l_DTMBandCode = xml_tools.as_string_list(l2comm.get_value("DTMViewingDirectionBandCode"))[0]
            l_DTMBandIdx = self._plugin.BandsDefinitions.get_band_id_in_l2_coarse(l_DTMBandCode)

            self.dict_of_vals[
                "DTMVIEImage"] = self._vieimagelist[l_DTMBandIdx]

            LOGGER.debug("l_DTMBandIdx : ")
            LOGGER.debug(l_DTMBandIdx)
            self.dict_of_vals[
                "IPTOASubOutput"] = self._sub_toa
            self.dict_of_vals[
                "L2TOAImageList"] = self._l2toaimagelist

            self.dict_of_vals["ViewingZenithMeanMap"] = self._meanZenithMap
            self.dict_of_vals["ViewingAzimuthMeanMap"] = self._meanAzimuthMap

            self.dict_of_vals["CLAImage"] = self._claimage

            self.dict_of_vals["IPSATSubOutput"] = self._subsatimage
            l_CLDBandCode = l2comm.get_value("CLDViewingDirectionBandCode")
            l_CLDBandIdx = self._plugin.BandsDefinitions.get_band_id_in_l2_coarse(l_CLDBandCode)
            LOGGER.debug("l_CLDBandIdx: ")
            LOGGER.debug(l_CLDBandIdx)
            self.dict_of_vals["ShadowVIEImage"] = self._vieimagelist[l_CLDBandIdx]
            l_CirrusBandCode = l2comm.get_value("CirrusBandCode")
            l_CirrusBandIdx = self._plugin.BandsDefinitions.get_band_id_in_l2_coarse(l_CirrusBandCode)

            LOGGER.debug("l_CirrusBandIdx: ")
            LOGGER.debug(l_CirrusBandIdx)

            self.dict_of_vals["L1TOACirrusImage"] = self._toa_scalar_list[l_CirrusBandIdx]

            self.dict_of_vals["AngleZoneMaskList"] = self._l2zoneimagelist
            self.dict_of_vals["L2EDGOutputList"] = self._l2edgmasklist
            self.dict_of_vals["L2SATImageList"] = self._l2satmasklist
            self.dict_of_vals["L2PIXImageList"] = self._l2piximagelist
            self.dict_of_vals["L2DFPImageList"] = self._l2dfpimagelist

            # Cleanup pipelines
            self._toa_pipeline.free_otb_app()
            self._l2_dfp_pipeline.free_otb_app()
            self._l2_sat_pipeline.free_otb_app()
            self._l2_detf_pipeline.free_otb_app()

            # *************************************************************************************************************
            #                                     END READ L1 for ALGORITHMS
            # *************************************************************************************************************

