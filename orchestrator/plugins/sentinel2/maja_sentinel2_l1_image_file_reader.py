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

:organization: CS SI
:copyright: 2017 CNES. All rights reserved.
:license: see LICENSE file
:created: 12 Jan 2018

###################################################################################################
"""
import os
from orchestrator.common.logger.maja_logging import configure_logger
from orchestrator.common.maja_exceptions import MajaDataException, MajaExceptionPluginSentinel2
from orchestrator.common.xml_tools import check_xml
from orchestrator.plugins.common.sentinel2_base.maja_sentinel2_l1_image_file_reader_base import \
    Sentinel2L1ImageFileReaderBase
from orchestrator.plugins.sentinel2.maja_sentinel2_plugin import MajaSentinel2Plugin

from orchestrator.common.constants import ReadL1Mode
import orchestrator.common.xml_tools as xml_tools
from orchestrator.common.maja_common import BoundingBox
from orchestrator.cots.otb.algorithms.otb_band_math import band_math
from orchestrator.cots.otb.algorithms.otb_multiply_by_scalar import multiply_by_scalar
from orchestrator.cots.otb.algorithms.otb_resample import resample
from orchestrator.cots.otb.algorithms.otb_resample import OtbResampleType
from orchestrator.cots.otb.algorithms.otb_band_math import band_math_or
from orchestrator.cots.otb.algorithms.otb_binary_threshold import binary_threshold

LOGGER = configure_logger(__name__)


class Sentinel2L1ImageFileReader(Sentinel2L1ImageFileReaderBase):
    def __init__(self):
        super(Sentinel2L1ImageFileReader, self).__init__()
        self._Satellite = "SENTINEL2"
        self._plugin = MajaSentinel2Plugin()

    def can_read(self, plugin_name):
        return plugin_name == "SENTINEL2"

    def generate_toa(self, listOfTOAImageFileNames, reflectanceMultiplicationValues, working):
        """

        :param listOfTOAImageFileNames: ListOfStrings
        :param reflectanceMultiplicationValues: ListOfDoubles
        :return:
        :rtype: string
        """

        # Initialization
        l_ProjectionRef = ""

        # =======> GENERATE TOA CACHING
        l_ProjectionRef = self.generate_toa_caching(listOfTOAImageFileNames, reflectanceMultiplicationValues, working)

        LOGGER.debug("Caching TOA images done ...")

        return l_ProjectionRef

    def generate_edg_images_from_toa(self, listOfTOAImageFileNames, working):
        """

        :param listOfTOAImageFileNames: list
        :param working: path
        :return:
        """
        # Get the number of band with the number of TOA image files set in the input product directory
        l_NbBand = len(listOfTOAImageFileNames)  # int

        # *******************************************************************************************************
        # L2SubEDG pipeline connection
        # *******************************************************************************************************
        LOGGER.debug("Start IPEDGSub")
        m_OneBandFilterList = []
        m_ThresholdFilterList1 = []
        m_ThresholdFilterList2 = []
        m_ResamplingList = []
        m_OrFilterList = []

        for i in range(2):
            toaFilename = listOfTOAImageFileNames[i]
            LOGGER.debug(("toaFilename : ", toaFilename))
            out_oneBandValue = os.path.join(working, "OneBandValue" + str(i) + ".tif")
            band_math_OneBand = band_math([self._toa_scalar_list[i]], "abs(im1b1-0.0)<0.000001 ? 1:0",
                                          output_image=out_oneBandValue + ":uint8")
            m_OneBandFilterList.append(band_math_OneBand.getoutput()["out"])

            out_threshold_mask1 = os.path.join(working, "ThresholdMask1" + str(i) + ".tif")
            threshold_mask1 = multiply_by_scalar(band_math_OneBand.getoutput()["out"], 1000,
                                                 output_image=out_threshold_mask1, write_output=False)
            m_ThresholdFilterList1.append(threshold_mask1.getoutput()["out"])

            out_resample = os.path.join(working, "mask_resample" + str(i) + ".tif")
            resample_mask = resample(threshold_mask1.getoutput()["out"], self._dem.ALC, out_resample,
                                     OtbResampleType.LINEAR_WITH_RADIUS)

            m_ResamplingList.append(resample_mask.getoutput()["out"])

            out_band_math_resample_mask = os.path.join(working, "band_math_resample_mask" + str(i) + ".tif")
            band_math_resample_mask = band_math([resample_mask.getoutput()["out"]], "(im1b1-500) < 0.00001 ? 0:1",
                                                output_image=out_band_math_resample_mask + ":uint8")
            m_ThresholdFilterList2.append(band_math_resample_mask.getoutput()["out"])

        out_or0 = os.path.join(working, "MaskOrMask_0.tif")
        band_math_or_b1 = band_math_or([m_ThresholdFilterList2[0], m_ThresholdFilterList2[1]],
                                       output_image=out_or0 + ":uint8")
        m_OrFilterList.append(band_math_or_b1.getoutput()["out"])

        for i in range(l_NbBand - 2):
            out_oneBandValue = os.path.join(working, "OneBandValue" + str(i + 2) + ".tif")
            band_math_OneBand = band_math([self._toa_scalar_list[i + 2]], "abs(im1b1-0.0)<0.000001 ? 1:0",
                                          output_image=out_oneBandValue + ":uint8")
            m_OneBandFilterList.append(band_math_OneBand.getoutput()["out"])

            out_threshold_mask1 = os.path.join(working, "ThresholdMask1" + str(i + 2) + ".tif")
            threshold_mask1 = multiply_by_scalar(band_math_OneBand.getoutput()["out"], 1000,
                                                 output_image=out_threshold_mask1, write_output=False)
            m_ThresholdFilterList1.append(threshold_mask1.getoutput()["out"])

            out_resample = os.path.join(working, "mask_resample" + str(i + 2) + ".tif")
            resample_mask = resample(threshold_mask1.getoutput()["out"], self._dem.ALC, out_resample,
                                     OtbResampleType.LINEAR_WITH_RADIUS)
            m_ResamplingList.append(resample_mask.getoutput()["out"])

            out_band_math_resample_mask = os.path.join(working, "band_math_resample_mask" + str(i + 2) + ".tif")
            band_math_resample_mask = band_math([resample_mask.getoutput()["out"]], "(im1b1-500) < 0.00001 ? 0:1",
                                                output_image=out_band_math_resample_mask + ":uint8")
            m_ThresholdFilterList2.append(band_math_resample_mask.getoutput()["out"])

            out_or = os.path.join(working, "MaskOrMask" + str(i + 2) + ".tif")
            band_math_or_b1 = band_math_or([m_OrFilterList[i], band_math_resample_mask.getoutput()["out"]],
                                           output_image=out_or + ":uint8")
            m_OrFilterList.append(band_math_or_b1.getoutput()["out"])

        self._edgsubmask = m_OrFilterList[len(m_OrFilterList) - 1]
        LOGGER.debug("End IPEDGSub.")

        # *******************************************************************************************************
        # L2EDG pipeline connection
        # *******************************************************************************************************
        LOGGER.debug("Start L2EDG ...")

        l_BandsDefinitions = self._plugin.BandsDefinitions
        LOGGER.debug("BANDS DEFINITION")
        LOGGER.debug(l_BandsDefinitions)

        l_ListOfL2Resolution = l_BandsDefinitions.ListOfL2Resolution  # ListOfStrings
        # At L2 resolution
        l_NbL2Res = len(l_ListOfL2Resolution)

        for r in range(l_NbL2Res):
            res_str = l_ListOfL2Resolution[r]
            # Set 1000 to edge pixels to identify the pixel contaminated by an edge pixel after resampling
            out_thresh = os.path.join(working, "EDGThreshL2_{}.tif".format(res_str))
            m_L2EDGThresholdImage = binary_threshold(self._edgsubmask,
                                                     lower_threshold=0,
                                                     inside_value=1000,
                                                     outside_value=0,
                                                     output_image=out_thresh,
                                                     write_output=True).getoutput()["out"]  # //l_ThresholdImageFilter

            # ExpandFilterPointer => PadAndResampleImageFilter => app ressampling
            out_ressampling = os.path.join(working, "IPEDGRealL2_{}.tif".format(res_str))
            resample(m_L2EDGThresholdImage, self._dem.ALTList[r], out_ressampling, OtbResampleType.LINEAR)

            # Set Threshold value to one because the expand filter interpolates values set to 0
            # or 1000 in the first threshold and adds systematically CONST_EPSILON to the output value.
            m_L2EDGThresholdImage2_out = os.path.join(working, "IPEDGMaskL2_{}.tif".format(res_str))
            m_L2EDGThresholdImage2 = binary_threshold(out_ressampling,
                                                      lower_threshold=0.,
                                                      inside_value=1,
                                                      outside_value=0,
                                                      output_image=m_L2EDGThresholdImage2_out + ":uint8").getoutput()[
                "out"]
            self._l2edgmasklist.append(m_L2EDGThresholdImage2)

    # Can read method
    def read(self, product_info, app_handler, l2comm, dem, pReadL1Mode):
        """product_info,plugin, l2comm,mode

        :param product_info: L1ImageInformationsBase
        :param pReadL1Mode: ReadL1ModeType
        :return:
        """

        product_filename = product_info.HeaderFilename
        working_dir = app_handler.get_directory_manager().get_temporary_directory("L1Read_",
                                            do_always_remove=True)

        self._plugin.initialize(app_handler)
        self._GIPPL2COMMHandler = l2comm
        LOGGER.info("Start Sentinel2 L1 ImageFileReader ...")
        self._ReadL1Mode = pReadL1Mode
        self._dem = dem

        # --------------------------------------
        # Check the extension of th efile. For Muscate, must be .XML (in upper case)
        IsValidSatellite = (product_info.HeaderHandler is not None)
        if not IsValidSatellite:
            raise MajaExceptionPluginSentinel2(
                "The file <{}> is not a valid Sentinel2 L1 product.".format(product_filename))

        # Check the validity with the schema
        lSchemaLocationFile = os.path.join(app_handler.get_schemas_root_install_dir(),
                                           self._plugin.MAJA_INSTALL_SCHEMAS_L1PRODUCT_FILE)

        if app_handler.get_validate_schemas():
            # remplacer par un appel Ã  pylint ? un check xml
            result = check_xml(product_filename, xsd_file=lSchemaLocationFile)
            if not result:
                raise MajaExceptionPluginSentinel2(
                    "The xml file <{}> is not conform with its schema <{}> !, Log of execution :{}".format(
                        product_filename, lSchemaLocationFile, str(result)))

        # --------------------------------------
        # Load the header tile file in the xml tile handler to read tile information
        xmlTileFilename = product_info.xmlTileFilename

        # *******************************************************************************************************
        # TOA & masks Reader connection
        # *******************************************************************************************************
        l_BandsDefinitions = self._plugin.BandsDefinitions  # BandsDefinitions
        l_ListOfTOAImageFileNames = product_info.HeaderHandler.get_list_of_toa_images()  # ListOfStrings
        l_SatPixFileNames = product_info.TileHandler.ListOfSaturatedPixelsHeaderFileName  # ListOfStrings
        l_DefectivPixFileNames = product_info.TileHandler.ListOfDefectivPixelsHeaderFileName  # ListOfStrings
        l_ZoneMaskFileNames = product_info.TileHandler.ListOfDetFootPrintHeaderFileName  # ListOfStrings
        l_NoDataMaskFileNames = product_info.TileHandler.ListOfNoDataPixelsHeaderFileName  # ListOfStrings
        l_ListOfTOABandCode = product_info.HeaderHandler.get_list_of_band_codes()  # ListOfStrings
        l_ListOfL1Resolution = l_BandsDefinitions.ListOfL1Resolution  # ListOfStrings
        l_ListOfL2Resolution = l_BandsDefinitions.ListOfL2Resolution  # ListOfStrings
        l_NbL1Res = len(l_ListOfL1Resolution)  # int
        l_NbL2Res = len(l_ListOfL2Resolution)  # int
        l_NbBand = len(l_ListOfTOAImageFileNames)  # int
        # TODO: check ConfigUserCameraXMLFileHandler
        # TODO; check GetL2CoarseResolution grep L2CoarseResolution

        l_Areas = dem.L2Areas
        l_L2CoarseArea = dem.CoarseArea
        l_L2CoarseResolution = int(round(dem.CoarseArea.spacing[0]))
        LOGGER.debug(l_L2CoarseResolution)

        l_L1NoData = product_info.L1NoData
        l_ReflectanceQuantificationValue = product_info.ReflectanceQuantification
        l_RealL1NoData = l_L1NoData * l_ReflectanceQuantificationValue  # RealNoDataType

        if (len(l_ListOfTOABandCode) != len(l_ListOfTOAImageFileNames)) or (
                len(l_ListOfTOABandCode) != len(l_SatPixFileNames)) or (
                len(l_ListOfTOABandCode) != len(l_DefectivPixFileNames)):
            raise MajaExceptionPluginSentinel2(
                "Sentinel2L1ImageFileReader.CanRead: Internal error: The number of image file, sat file and band code are different !")

        # =======> GENERATE TOA CACHING
        #
        # * Get calibration coeffs if activated

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

        # ***********************************************************************************************************
        # Generate EDG at L2coarse and L2 resolutions
        # ***********************************************************************************************************
        self.generate_edg_images_from_toa(l_ListOfTOAImageFileNames, working_dir)

        # ***********************************************************************************************************
        # Get the bounding box of each L1 resolution
        # ***********************************************************************************************************
        # list of bounding box per resolution
        l_L1BoundingBoxMap = {}  # BoundingBoxMapType

        for res in range(l_NbL1Res):
            curRes = l_ListOfL1Resolution[res]  # string
            l_IntResolution = l_BandsDefinitions.get_l1_resolution(curRes)
            # Read the bounding box for the current resolution
            l_BoundingBox = product_info.TileHandler.get_geoposition_boundingbox(l_IntResolution)  # BoundingBoxType
            LOGGER.debug("S2 Geoposition BoundingBox computed: xmin, ymin, xmax, ymax: %s, %s, %s, %s.",
                         l_BoundingBox.xmin, l_BoundingBox.ymin, l_BoundingBox.xmax, l_BoundingBox.ymax)

            # Store the bounding box per resolution
            l_L1BoundingBoxMap[curRes] = l_BoundingBox

        # ***********************************************************************************************************
        # ***********************************************************************************************************
        # ***********************************************************************************************************
        #                                     START READ L1 for ALGORITHMS
        # ***********************************************************************************************************
        # ***********************************************************************************************************
        # ***********************************************************************************************************
        if pReadL1Mode == ReadL1Mode.READ_L1_MODE_FOR_ALGORITHMS:
            # --------------------------------------
            # Get information of areas (footprint) of the product (Origin, Spacing and Size for L2 and L2Coarse resolution)
            # --------------------------------------
            l_L2Dems = dem.ALTList
            l_CoarseDem = dem.ALC

            # ***********************************************************************************************************
            # Get the bounding box of each L1 resolution
            # ***********************************************************************************************************
            # list of bounding box per resolution
            l_L2CoarseBoundingBoxMap = {}  # BoundingBoxMapType

            for res in range(l_NbL1Res):
                curRes = l_ListOfL1Resolution[res]  # string
                l_IntResolution = l_BandsDefinitions.get_l1_resolution(curRes)
                l_PointXY = product_info.TileHandler.get_geoposition_upperleftcorner(l_IntResolution)  # PointXYType
                l_L2CoarseBoundingBox = BoundingBox()
                # ATTENTION: For coordinates, cf. FD 73233
                l_L2CoarseBoundingBox.xmin = l_PointXY.x
                l_L2CoarseBoundingBox.ymin = l_PointXY.y - l_L2CoarseArea.size[1] * l_L2CoarseResolution
                l_L2CoarseBoundingBox.xmax = l_PointXY.x + l_L2CoarseArea.size[0] * l_L2CoarseResolution
                l_L2CoarseBoundingBox.ymax = l_PointXY.y

                l_L2CoarseBoundingBoxMap[curRes] = l_L2CoarseBoundingBox

            LOGGER.debug("Start SubSampling ...")

            # =======> GENERATE TOA SUB IMAGES AT L2 COARSE RESOLUTION
            self.generate_toa_sub_images(working_dir)

            LOGGER.debug("Start SubSampling done.")

            # *******************************************************************************************************
            # L2 TOA image pipeline connection
            # ******************* ************************************************************************************

            # =======> GENERATE L2 TOA IMAGES
            self.generate_l2_toa_images(working_dir)

            # *******************************************************************************************************
            # Rasterize the gml mask per L2 resolution per band
            # *******************************************************************************************************

            # =======> GENERATE MASK RASTERS
            self.generate_mask_rasters_gml(l_L1BoundingBoxMap, l_Areas, l_ProjectionRef, l_SatPixFileNames,
                                     l_DefectivPixFileNames, l_ZoneMaskFileNames,
                                     self._plugin.GDAL_RASTERIZE_GML_MASK_ADDITIONAL_COMMAND_LINE_PARAMETERS,
                                     self._plugin.GDAL_RASTERIZE_GML_DETECTOR_ADDITIONAL_COMMAND_LINE_PARAMETERS,
                                     working_dir)

            l_CurrentConfigUserCamera = self._plugin.ConfigUserCamera
            grid_ref_alt = l_CurrentConfigUserCamera.get_Algorithms().get_GRID_Reference_Altitudes()
            l_VIEHRef = grid_ref_alt.get_VIEHRef()  # double
            l_SOLH1 = grid_ref_alt.get_SOLH1()  # double

            # *******************************************************************************************************
            # IPSOL Sub image pipeline connection
            # *******************************************************************************************************
            LOGGER.debug("Start IPSOL SubSampling ...")
            l_solarAngleFile = product_info.TileHandler.angles.sun_angles.write(working_dir)

            # =======> GENERATE SOLAR ANGLE GRIDS
            self.get_solar_grids(self._dem.ALC, l_solarAngleFile, l_SOLH1, working_dir)

            LOGGER.debug("Start IPSOL SubSampling done.")

            # *******************************************************************************************************
            # IPVIE Sub image pipeline connection
            # *******************************************************************************************************
            LOGGER.debug("Start IPVIE SubSampling ...")

            LOGGER.debug("For each band ...")
            for l_band in range(l_NbBand):
                l_L1Resolution = l_BandsDefinitions.get_l1_resolution_for_band_code(l_ListOfTOABandCode[l_band])  # string

                # Get the list of detectors (index)
                l_ListOfZone = product_info.TileHandler.get_list_of_zones(l_band)  # ListOfUIntegers

                l_BoundingBox = l_L2CoarseBoundingBoxMap[l_L1Resolution]  # BoundingBoxType

                # Get the list of viewing angles in the header file of the tile
                l_vieAngles = product_info.TileHandler.angles.viewing_incidence_angle.get_viewing_angles(
                    l_band)  # ListOfListOfStrings
                if len(l_vieAngles) == 0:
                    raise MajaDataException("No viewing angles for band " + str(l_band))
                # =======> GENERATE VIEWING ANGLE GRIDS
                self.get_viewing_grids(l_band, l_L2CoarseArea, l_ProjectionRef, l_VIEHRef, l_SatPixFileNames[l_band],
                                     l_ZoneMaskFileNames[l_band], l_NoDataMaskFileNames[l_band],
                                     l_ListOfZone, l_BoundingBox, l_vieAngles,
                                     self._plugin.GDAL_RASTERIZE_GML_MASK_ADDITIONAL_COMMAND_LINE_PARAMETERS,
                                     self._plugin.GDAL_RASTERIZE_GML_DETECTOR_ADDITIONAL_COMMAND_LINE_PARAMETERS,
                                     self._plugin.GDAL_RASTERIZE_GML_NODATA_ADDITIONAL_COMMAND_LINE_PARAMETERS,
                                     l_NbBand,working_dir)

            LOGGER.debug("Start IPVIE SubSampling done.")
            # To check mean angle values
            # TODO: TBD
            # zones = self.m_ViewingZenithMeanMap.keys()
            # values = zip(zones,
            #             [self.m_ViewingZenithMeanMap.get(zone) for zone in zones],
            #             [self.m_ViewingAzimuthMeanMap.get(zone) for zone in zones])
            # for zone, zenith, azimuth in values:
            #    LOGGER.debug(" Mean for zone %s is [zen;azi] : [%s;%s].", zone, zenith, azimuth)

            # *******************************************************************************************************
            # IPEDGSub and L2EDG pipeline connection
            # *******************************************************************************************************

            # *******************************************************************************************************
            # IPSAT Sub and L2SAT image pipeline connection
            # *******************************************************************************************************

            # =======> GENERATE SAT IMAGES
            self.generate_sat_images(working_dir)

            # *******************************************************************************************************
            # CLA image pipeline connection
            # *******************************************************************************************************

            # =======> GENERATE CLA IMAGES
            self.generate_cla_images(l_RealL1NoData, working_dir)

            # Fill the datas
            self.dict_of_vals[
                "IPEDGSubOutput"] = self._edgsubmask
            self.dict_of_vals[
                "SOL1Image"] = self._sol1image
            l_DTMBandCode = xml_tools.as_string_list(l2comm.get_value("DTMViewingDirectionBandCode"))[0]
            l_DTMBandIdx = self._plugin.BandsDefinitions.get_band_id_in_l2_coarse(l_DTMBandCode)
            LOGGER.info("DTMBandCode= " + l_DTMBandCode)
            self.dict_of_vals[
                "DTMVIEImage"] = self._vieimagelist[l_DTMBandIdx]
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
            self.dict_of_vals["ShadowVIEImage"] = self._vieimagelist[l_CLDBandIdx]
            l_CirrusBandCode = l2comm.get_value("CirrusBandCode")
            l_CirrusBandIdx = self._plugin.BandsDefinitions.get_band_id_in_l2_coarse(l_CirrusBandCode)

            self.dict_of_vals["L1TOACirrusImage"] = self._toa_scalar_list[l_CirrusBandIdx]

            self.dict_of_vals["AngleZoneMaskList"] = self._l2zoneimagelist
            self.dict_of_vals["L2EDGOutputList"] = self._l2edgmasklist
            self.dict_of_vals["L2SATImageList"] = self._l2satmasklist
            self.dict_of_vals["L2PIXImageList"] = self._l2piximagelist


            # ***********************************************************************************************************
            # ***********************************************************************************************************
            # ***********************************************************************************************************
            #                                     END READ L1 for ALGORITHMS
            # ***********************************************************************************************************
            # ***********************************************************************************************************
            # ***********************************************************************************************************
