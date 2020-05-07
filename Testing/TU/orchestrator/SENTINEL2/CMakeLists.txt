############################################################################################################
#                                                                                                          #
#                        o     o                                                                           #
#                        oo   oo   oo        o   oo        ,-.                                             #
#                        o o o o  o  o       o  o  o       \_/                                             #
#                        o  o  o o    o      o o    o     {|||D                                            #
#                        o     o oooooo      o oooooo      / \                                             #
#                        o     o o    o o    o o    o      `-^                                             #
#                        o     o o    o  oooo  o    o                                                      #
#                                                                                                          #
############################################################################################################
#                                                                                                          #
# Author: CS Systemes d'Information  (France)                                                              #
#                                                                                                          #
############################################################################################################
# HISTORIQUE                                                                                               #
#                                                                                                          #
# VERSION : 1-0-0 : <TypeFT> : <NumFT> : 22 mars 2019 : Creation                                           #
#                                                                                                          #
# FIN-HISTORIQUE                                                                                           #
#                                                                                                          #
# $Id                                                                                                      #
#                                                                                                          #
#                                                                                                          #
############################################################################################################


set(TEST_DRIVER ${CMAKE_INSTALL_PREFIX}/bin/otbTestDriver.sh)


add_test(NAME pyTuGenerateEDGImagefromTOAImages
          COMMAND ${TEST_DRIVER}
          --compare-n-images ${EPSILON_4} 3
          ${MAJADATA_TU_L1_READER_SENTINEL2_DIR}/TestGenerateEDGImageFromTOAImages/Baseline/apTuIPEDGSubMask0.tif
          ${MAJA_TEST_OUTPUT_ROOT}/TU/SENTINEL2/MaskOrMask12.tif
          ${MAJADATA_TU_L1_READER_SENTINEL2_DIR}/TestGenerateEDGImageFromTOAImages/Baseline/apTuIPEDGMaskL2_R0.tif
          ${MAJA_TEST_OUTPUT_ROOT}/TU/SENTINEL2/IPEDGMaskL2_R1.tif
          ${MAJADATA_TU_L1_READER_SENTINEL2_DIR}/TestGenerateEDGImageFromTOAImages/Baseline/apTuIPEDGMaskL2_R1.tif
          ${MAJA_TEST_OUTPUT_ROOT}/TU/SENTINEL2/IPEDGMaskL2_R2.tif
          Execute
          ${PYTHON_EXECUTABLE} ${TEST_ORCHESTRATOR}/PythonTestDriver.py test_maja_sentinel2_generate_edg_images_from_toa
          ${MAJADATA_TU_L1_READER_SENTINEL2_DIR}/TestGenerateEDGImageFromTOAImages/Input/
          ${MAJADATA_TU_L1_READER_SENTINEL2_DIR}/TestGenerateEDGImageFromTOAImages/Input/S2__TEST_AUX_REFDE2_36JTT____5001.HDR
          ${MAJA_TEST_OUTPUT_ROOT}/TU/SENTINEL2/
          )

add_test(NAME pyTuL1ImageInfoReaderSentinel2Plugin
         COMMAND ${TEST_DRIVER}
         Execute
         ${PYTHON_EXECUTABLE} ${TEST_ORCHESTRATOR}/test_maja_l1_image_info.py
         "-i" ${MAJADATA_TV_SENTINEL2_INPUT}/S2-V-L2NOMINAL-001-F-N-SENTINEL2-ALGO/
         "-t" "36JTT"

          )
          
 add_test(NAME pyTuL1ImageReaderSentinel2Plugin
          COMMAND ${TEST_DRIVER}
          --compare-n-images ${EPSILON_4} 18

          #IPEDGSubOutput
          ${MAJADATA_TU_L1_READER_SENTINEL2_DIR}/TestL1ImageReader/Baseline//apTuL1Reader_SENTINEL2_IPEDGSubOutput.tif
          ${MAJA_TEST_OUTPUT_ROOT}/TU/SENTINEL2/MaskOrMask12.tif

          #L1TOACirrus
          ${MAJADATA_TU_L1_READER_SENTINEL2_DIR}/TestL1ImageReader/Baseline//apTuL1Reader_SENTINEL2_L1TOACirrus.tif
          ${MAJA_TEST_OUTPUT_ROOT}/TU/SENTINEL2/L1TOACirrusImage.tif

          #IPAOTSubOutput
          ${MAJADATA_TU_L1_READER_SENTINEL2_DIR}/TestL1ImageReader/Baseline//apTuL1Reader_SENTINEL2_IPAOTSubOutput.tif
          ${MAJA_TEST_OUTPUT_ROOT}/TU/SENTINEL2/aot_sub.tif

          # IPSATSubOutput
          ${MAJADATA_TU_L1_READER_SENTINEL2_DIR}/TestL1ImageReader/Baseline//apTuL1Reader_SENTINEL2_IPSATSubOutput.tif
          ${MAJA_TEST_OUTPUT_ROOT}/TU/SENTINEL2/SubSatVector.tif

          #CLAImage
          ${MAJADATA_TU_L1_READER_SENTINEL2_DIR}/TestL1ImageReader/Baseline//apTuL1Reader_SENTINEL2_CLAImage.tif
          ${MAJA_TEST_OUTPUT_ROOT}/TU/SENTINEL2/cla_constant_sub.tif

          # L2EDGOutputList
          ${MAJADATA_TU_L1_READER_SENTINEL2_DIR}/TestL1ImageReader/Baseline//apTuL1Reader_SENTINEL2_L2EDGOutput_R1.tif
          ${MAJA_TEST_OUTPUT_ROOT}/TU/SENTINEL2/IPEDGMaskL2_R1.tif
          ${MAJADATA_TU_L1_READER_SENTINEL2_DIR}/TestL1ImageReader/Baseline//apTuL1Reader_SENTINEL2_L2EDGOutput_R2.tif
          ${MAJA_TEST_OUTPUT_ROOT}/TU/SENTINEL2/IPEDGMaskL2_R2.tif

          #SOL1Image
          ${MAJADATA_TU_L1_READER_SENTINEL2_DIR}/TestL1ImageReader/Baseline//apTuL1Reader_SENTINEL2_SOL1Image.tif
          ${MAJA_TEST_OUTPUT_ROOT}/TU/SENTINEL2/solar_grid_resamp.tif

          #L2SATMaskList
          ${MAJADATA_TU_L1_READER_SENTINEL2_DIR}/TestL1ImageReader/Baseline//apTuL1Reader_SENTINEL2_L2SATMaskOutput_R1.tif
          ${MAJA_TEST_OUTPUT_ROOT}/TU/SENTINEL2/L2SATVector_R1.tif
          ${MAJADATA_TU_L1_READER_SENTINEL2_DIR}/TestL1ImageReader/Baseline//apTuL1Reader_SENTINEL2_L2SATMaskOutput_R2.tif
          ${MAJA_TEST_OUTPUT_ROOT}/TU/SENTINEL2/L2SATVector_R2.tif
          
          #L2TOAImageList
          ${MAJADATA_TU_L1_READER_SENTINEL2_DIR}/TestL1ImageReader/Baseline//apTuL1Reader_SENTINEL2_L2TOAImageOutput_R1.tif
          ${MAJA_TEST_OUTPUT_ROOT}/TU/SENTINEL2/L2TOAImageListVector_R1.tif
          ${MAJADATA_TU_L1_READER_SENTINEL2_DIR}/TestL1ImageReader/Baseline//apTuL1Reader_SENTINEL2_L2TOAImageOutput_R2.tif
          ${MAJA_TEST_OUTPUT_ROOT}/TU/SENTINEL2/L2TOAImageListVector_R2.tif

          #DTMVieImage
          ${MAJADATA_TU_L1_READER_SENTINEL2_DIR}/TestL1ImageReader/Baseline//apTuL1Reader_SENTINEL2_DTMVIEImage.tif
          ${MAJA_TEST_OUTPUT_ROOT}/TU/SENTINEL2/viewing_grid_mult_3.tif

          #ShadowVIEImage
          ${MAJADATA_TU_L1_READER_SENTINEL2_DIR}/TestL1ImageReader/Baseline//apTuL1Reader_SENTINEL2_ShadowVIEImage.tif
          ${MAJA_TEST_OUTPUT_ROOT}/TU/SENTINEL2/viewing_grid_mult_2.tif

          #L2PIX
          ${MAJADATA_TU_L1_READER_SENTINEL2_DIR}/TestL1ImageReader/Baseline//apTuL1Reader_SENTINEL2_L2PIXImageOutput_R1.tif
          ${MAJA_TEST_OUTPUT_ROOT}/TU/SENTINEL2/const_0.tif
          ${MAJADATA_TU_L1_READER_SENTINEL2_DIR}/TestL1ImageReader/Baseline//apTuL1Reader_SENTINEL2_L2PIXImageOutput_R2.tif
          ${MAJA_TEST_OUTPUT_ROOT}/TU/SENTINEL2/const_1.tif

          # AngleZoneMaskList
          ${MAJADATA_TU_L1_READER_SENTINEL2_DIR}/TestL1ImageReader/Baseline//apTuL1Reader_SENTINEL2_AngleZoneMaskList_R1.tif
          ${MAJA_TEST_OUTPUT_ROOT}/TU/SENTINEL2/Masks_Zone_0.tif
          ${MAJADATA_TU_L1_READER_SENTINEL2_DIR}/TestL1ImageReader/Baseline//apTuL1Reader_SENTINEL2_AngleZoneMaskList_R2.tif
          ${MAJA_TEST_OUTPUT_ROOT}/TU/SENTINEL2/Masks_Zone_1.tif


          Execute
          ${PYTHON_EXECUTABLE} ${TEST_ORCHESTRATOR}/test_maja_l1_image_reader.py
          "-i" ${MAJADATA_TV_SENTINEL2_INPUT}/S2-V-L2NOMINAL-001-F-N-SENTINEL2-ALGO/
          "-o" ${MAJA_TEST_OUTPUT_ROOT}/TU/SENTINEL2
          "-t" "36JTT"
          )
  set_tests_properties(pyTuL1ImageReaderSentinel2Plugin PROPERTIES TIMEOUT 300000)
     