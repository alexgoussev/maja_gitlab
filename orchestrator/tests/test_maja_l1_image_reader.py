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

orchestrator.tests.plugins.test_maja_sentinel2_l1_pimage_file_reader -- shortdesc

orchestrator.tests.plugins.test_maja_sentinel2_l1_pimage_file_reader is a description

It defines classes_and_methods

###################################################################################################

:copyright: 2019 CNES. All rights reserved.
:license: license

###################################################################################################
"""

from __future__ import absolute_import

from orchestrator.plugins.common.factory.maja_l1_image_reader_provider import L1ImageReaderProvider
from orchestrator.common.logger.maja_logging import configure_logger
from orchestrator.plugins.common.factory.plugin_activate import register_all

from orchestrator.launcher.app_handler import AppHandler
import orchestrator.plugins.common.factory.product_utils as product_utils
import orchestrator.common.constants as constants
from orchestrator.cots.otb.otb_file_utils import otb_copy_file
import orchestrator.common.file_utils as file_utils

from orchestrator.common.dem.dem_base import DEMBase
from orchestrator.common.directory_manager import DirectoryManager
from orchestrator.common.earth_explorer.gipp_l2_comm_earth_explorer_xml_file_handler import \
    GippL2COMMEarthExplorerXMLFileHandler
import orchestrator.common.gipp_utils as gipp_utils
import argparse, sys, os
LOGGER = configure_logger(__name__)


argParser = argparse.ArgumentParser()
required_arguments = argParser.add_argument_group('required arguments')
required_arguments.add_argument('-i', '--input_dir', required=True,
                                    help='Path to input folder')
required_arguments.add_argument('-o', '--output_dir', required=True,
                                    help='Path to output directory')
required_arguments.add_argument('-t', '--tile_id', required=False,
                                    help='Tile id of the L1 product')
args = argParser.parse_args(sys.argv[1:])

register_all()
app_handler = AppHandler()

l1product = product_utils.get_input_l1_image_product(args.input_dir, args.tile_id)
LOGGER.debug(l1product.Satellite)

# Read and load L2COM
gip_l2comm_filename = gipp_utils.get_gipp_filename_with_mission(args.input_dir, "GIP_L2COMM", l1product.Satellite)
LOGGER.debug("L2COMM filename : " + gip_l2comm_filename)
l_gippl2commhandler = GippL2COMMEarthExplorerXMLFileHandler(gip_l2comm_filename)

# Read and initialize DEM
dem_filename = gipp_utils.get_gipp_filename_with_mission(args.input_dir, "AUX_REFDE2", l1product.UniqueSatellite)
LOGGER.debug("DEM filename : " + dem_filename)
dem = DEMBase()
dem.initialize(dem_filename, args.output_dir, True)
app_handler._directory_manager = DirectoryManager(working_dir=args.output_dir)

# Read L1 product
l1_reader = L1ImageReaderProvider.create(l1product.PluginName, l1product, app_handler, l_gippl2commhandler, dem,
                             constants.ReadL1Mode.READ_L1_MODE_FOR_ALGORITHMS)


#Copy files to the output directory
if l1_reader.has_value("IPEDGSubOutput") and l1_reader.get_value("IPEDGSubOutput"):
    file_utils.copy_file_to_directory(l1_reader.get_value("IPEDGSubOutput"), args.output_dir)

if l1_reader.has_value("SOL1Image") and l1_reader.get_value("SOL1Image"):
    file_utils.copy_file_to_directory(l1_reader.get_value("SOL1Image"), args.output_dir)

if l1_reader.has_value("SOL2Image") and l1_reader.get_value("SOL2Image"):
    file_utils.copy_file_to_directory(l1_reader.get_value("SOL2Image"), args.output_dir)

if l1_reader.has_value("DTMVIEImage") and l1_reader.get_value("DTMVIEImage"):
    file_utils.copy_file_to_directory(l1_reader.get_value("DTMVIEImage"), args.output_dir)

if l1_reader.has_value("IPTOASubOutput") and l1_reader.get_value("IPTOASubOutput"):
    file_utils.copy_file_to_directory(l1_reader.get_value("IPTOASubOutput"), args.output_dir)

if l1_reader.has_value("IPSATSubOutput") and l1_reader.get_value("IPSATSubOutput"):
    file_utils.copy_file_to_directory(l1_reader.get_value("IPSATSubOutput"), args.output_dir)

if l1_reader.has_value("L1TOACirrusImage") and l1_reader.get_value("L1TOACirrusImage"):
    otb_copy_file(l1_reader.get_value("L1TOACirrusImage"), os.path.join(args.output_dir, "L1TOACirrusImage.tif"))

if l1_reader.has_value("CLAImage") and l1_reader.get_value("CLAImage"):
    file_utils.copy_file_to_directory(l1_reader.get_value("CLAImage"), args.output_dir)

if l1_reader.has_value("ShadowVIEImage") and l1_reader.get_value("ShadowVIEImage"):
    file_utils.copy_file_to_directory(l1_reader.get_value("ShadowVIEImage"), args.output_dir)

if l1_reader.has_value("L2TOAImageList") and l1_reader.get_value("L2TOAImageList"):
    for i in range(0,len(l1_reader.get_value("L2TOAImageList"))):
        file_utils.copy_file_to_directory(l1_reader.get_value("L2TOAImageList")[i], args.output_dir)

if l1_reader.has_value("L2EDGOutputList") and l1_reader.get_value("L2EDGOutputList"):
    for i in range(0,len(l1_reader.get_value("L2EDGOutputList"))):
        file_utils.copy_file_to_directory(l1_reader.get_value("L2EDGOutputList")[i], args.output_dir)

if l1_reader.has_value("L2SATImageList") and l1_reader.get_value("L2SATImageList"):
    LOGGER.debug(l1_reader.get_value("L2SATImageList"))
    for i in range(0,len(l1_reader.get_value("L2SATImageList"))):
        if l1_reader.get_value("L2SATImageList")[i]:
            file_utils.copy_file_to_directory(l1_reader.get_value("L2SATImageList")[i], args.output_dir)

if l1_reader.has_value("L2PIXImageList") and l1_reader.get_value("L2PIXImageList"):
    for i in range(0,len(l1_reader.get_value("L2PIXImageList"))):
        file_utils.copy_file_to_directory(l1_reader.get_value("L2PIXImageList")[i], args.output_dir)

if l1_reader.has_value("L2DFPImageList") and l1_reader.get_value("L2DFPImageList"):
    for i in range(0,len(l1_reader.get_value("L2DFPImageList"))):
        file_utils.copy_file_to_directory(l1_reader.get_value("L2DFPImageList")[i], args.output_dir)

if l1_reader.has_value("L1PIXImageList") and l1_reader.get_value("L1PIXImageList"):
    for i in range(0,len(l1_reader.get_value("L1PIXImageList"))):
        file_utils.copy_file_to_directory(l1_reader.get_value("L1PIXImageList")[i], args.output_dir)

if l1_reader.has_value("L1CLDImageList") and l1_reader.get_value("L1CLDImageList"):
    for i in range(0,len(l1_reader.get_value("L1CLDImageList"))):
        file_utils.copy_file_to_directory(l1_reader.get_value("L1CLDImageList")[i], args.output_dir)

if l1_reader.has_value("AngleZoneMaskList") and l1_reader.get_value("AngleZoneMaskList"):
    for i in range(0, len(l1_reader.get_value("AngleZoneMaskList"))):
        file_utils.copy_file_to_directory(l1_reader.get_value("AngleZoneMaskList")[i], args.output_dir)


if l1_reader.has_value("L1TOAImageList") and l1_reader.get_value("L1TOAImageList"):
    for i in range(0, len(l1_reader.get_value("L1TOAImageList"))):
        LOGGER.debug("toa image list test: " + str(l1_reader.get_value("L1TOAImageList")[i]) )
        file_utils.copy_file_to_directory(l1_reader.get_value("L1TOAImageList")[i], args.output_dir)

