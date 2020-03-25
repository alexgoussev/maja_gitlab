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
set(VNS_TEST_DRIVER ${MAJA_BINARY_DIR}/bin/vnsTestMainLauncher.sh)
SET(PREFIX "Landsat8")

add_test(NAME pyTu${PREFIX}_L1ImageInfo
          COMMAND ${TEST_DRIVER}
          Execute
          ${PYTHON_EXECUTABLE} ${TEST_ORCHESTRATOR}/test_maja_l1_image_info.py
          "-i" ${MAJADATA_TV_LANDSAT8_INPUT}/L8-V-L2INIT-001-F-N-LANDSAT8-GENERAL
          )


add_test(NAME pyTu${PREFIX}_L1ImageFileReader
          COMMAND ${TEST_DRIVER}
          Execute
          ${PYTHON_EXECUTABLE} ${TEST_ORCHESTRATOR}/test_maja_l1_image_reader.py
          "-i" ${MAJADATA_TV_LANDSAT8_INPUT}/L8-V-L2INIT-001-F-N-LANDSAT8-GENERAL
          "-o" ${MAJA_TEST_OUTPUT_ROOT}/TU/LANDSAT8
          )


add_test(NAME pyTu${PREFIX}_L1ImageReader_L1TOA
          COMMAND ${VNS_TEST_DRIVER}
         --compare-image ${EPSILON_4}
         ${MAJADATA_TU_L1_READER_LANDSAT8_BASELINE}/l1toa_0.tif
         ${MAJA_TEST_OUTPUT_ROOT}/TU/LANDSAT8/l1toa_0.tif
         "--output-directory"
          ${MAJA_TEST_OUTPUT_ROOT}/TU/LANDSAT8/testing-compare-output-directory
          ${MAJA_BINARY_DIR}/bin/vnsDummyProgram.sh
         )


add_test(NAME pyTu${PREFIX}_L1ImageReader_L1PIX
          COMMAND ${VNS_TEST_DRIVER}
          --compare-image ${EPSILON_4}
          ${MAJADATA_TU_L1_READER_LANDSAT8_BASELINE}/PIX_Masks_const_R1.tif
          ${MAJA_TEST_OUTPUT_ROOT}/TU/LANDSAT8/PIX_Masks_const_R1.tif
          "--output-directory"
          ${MAJA_TEST_OUTPUT_ROOT}/TU/LANDSAT8/testing-compare-output-directory
          ${MAJA_BINARY_DIR}/bin/vnsDummyProgram.sh
          )


add_test(NAME pyTu${PREFIX}_L1ImageReader_L2SAT
          COMMAND ${VNS_TEST_DRIVER}
          --compare-image ${EPSILON_4}
          ${MAJADATA_TU_L1_READER_LANDSAT8_BASELINE}/L2SATImageList_R1.tif
          ${MAJA_TEST_OUTPUT_ROOT}/TU/LANDSAT8/L2SATImageList_R1.tif
          "--output-directory"
          ${MAJA_TEST_OUTPUT_ROOT}/TU/LANDSAT8/testing-compare-output-directory
          ${MAJA_BINARY_DIR}/bin/vnsDummyProgram.sh
          )


add_test(NAME pyTu${PREFIX}_L1ImageReader_L2TOA
          COMMAND ${VNS_TEST_DRIVER}
          --compare-image ${EPSILON_4}
          ${MAJADATA_TU_L1_READER_LANDSAT8_BASELINE}/L2TOAImageList_R1.tif
          ${MAJA_TEST_OUTPUT_ROOT}/TU/LANDSAT8/L2TOAImageList_R1.tif
          "--output-directory"
          ${MAJA_TEST_OUTPUT_ROOT}/TU/LANDSAT8/testing-compare-output-directory
          ${MAJA_BINARY_DIR}/bin/vnsDummyProgram.sh
          )


add_test(NAME pyTu${PREFIX}_L1ImageReader_EDGSub
          COMMAND ${VNS_TEST_DRIVER}
          --compare-image ${EPSILON_4}
          ${MAJADATA_TU_L1_READER_LANDSAT8_BASELINE}/IPEDGSubOutput.tif
          ${MAJA_TEST_OUTPUT_ROOT}/TU/LANDSAT8/IPEDGSubOutput.tif
          "--output-directory"
          ${MAJA_TEST_OUTPUT_ROOT}/TU/LANDSAT8/testing-compare-output-directory
          ${MAJA_BINARY_DIR}/bin/vnsDummyProgram.sh
          )


add_test(NAME pyTu${PREFIX}_L1ImageReader_L2EDG
          COMMAND ${VNS_TEST_DRIVER}
          --compare-image ${EPSILON_4}
          ${MAJADATA_TU_L1_READER_LANDSAT8_BASELINE}/IPEDGMaskL2_R1.tif
          ${MAJA_TEST_OUTPUT_ROOT}/TU/LANDSAT8/IPEDGMaskL2_R1.tif
          "--output-directory"
          ${MAJA_TEST_OUTPUT_ROOT}/TU/LANDSAT8/testing-compare-output-directory
          ${MAJA_BINARY_DIR}/bin/vnsDummyProgram.sh
          )


add_test(NAME pyTu${PREFIX}_L1ImageReader_TOASub
          COMMAND ${VNS_TEST_DRIVER}
          --compare-image ${EPSILON_4}
          ${MAJADATA_TU_L1_READER_LANDSAT8_BASELINE}/aot_sub.tif
          ${MAJA_TEST_OUTPUT_ROOT}/TU/LANDSAT8/aot_sub.tif
          "--output-directory"
          ${MAJA_TEST_OUTPUT_ROOT}/TU/LANDSAT8/testing-compare-output-directory
          ${MAJA_BINARY_DIR}/bin/vnsDummyProgram.sh
          )


add_test(NAME pyTu${PREFIX}_L1ImageReader_SATSub
          COMMAND ${VNS_TEST_DRIVER}
          --compare-image ${EPSILON_4}
          ${MAJADATA_TU_L1_READER_LANDSAT8_BASELINE}/sat_sub.tif
          ${MAJA_TEST_OUTPUT_ROOT}/TU/LANDSAT8/sat_sub.tif
          "--output-directory"
          ${MAJA_TEST_OUTPUT_ROOT}/TU/LANDSAT8/testing-compare-output-directory
          ${MAJA_BINARY_DIR}/bin/vnsDummyProgram.sh
          )


add_test(NAME pyTu${PREFIX}_L1ImageReader_CLA
          COMMAND ${VNS_TEST_DRIVER}
          --compare-image ${EPSILON_4}
          ${MAJADATA_TU_L1_READER_LANDSAT8_BASELINE}/cla_constant_sub.tif
          ${MAJA_TEST_OUTPUT_ROOT}/TU/LANDSAT8/cla_constant_sub.tif
          "--output-directory"
          ${MAJA_TEST_OUTPUT_ROOT}/TU/LANDSAT8/testing-compare-output-directory
          ${MAJA_BINARY_DIR}/bin/vnsDummyProgram.sh
          )


add_test(NAME pyTu${PREFIX}_L1ImageReader_SOL1
          COMMAND ${VNS_TEST_DRIVER}
          --compare-image ${EPSILON_4}
          ${MAJADATA_TU_L1_READER_LANDSAT8_BASELINE}/sol1_concat.tif
          ${MAJA_TEST_OUTPUT_ROOT}/TU/LANDSAT8/sol1_concat.tif
          "--output-directory"
          ${MAJA_TEST_OUTPUT_ROOT}/TU/LANDSAT8/testing-compare-output-directory
          ${MAJA_BINARY_DIR}/bin/vnsDummyProgram.sh
          )


add_test(NAME pyTu${PREFIX}_L1ImageReader_VIE
          COMMAND ${VNS_TEST_DRIVER}
          --compare-image ${EPSILON_4}
          ${MAJADATA_TU_L1_READER_LANDSAT8_BASELINE}/vie_concat.tif
          ${MAJA_TEST_OUTPUT_ROOT}/TU/LANDSAT8/vie_concat.tif
          "--output-directory"
          ${MAJA_TEST_OUTPUT_ROOT}/TU/LANDSAT8/testing-compare-output-directory
          ${MAJA_BINARY_DIR}/bin/vnsDummyProgram.sh
          )





