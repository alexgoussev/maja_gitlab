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
SET(PREFIX "Venus")

add_test(NAME pyTu${PREFIX}_L1ImageInfo
         COMMAND ${TEST_DRIVER}
         Execute
         ${PYTHON_EXECUTABLE} ${TEST_ORCHESTRATOR}/test_maja_l1_image_info.py
         "-i" ${MAJADATA_TV_VENUS_INPUT}/VE-V-L2INIT-002-F-N-VENUS-IFPDS
         )


add_test(NAME pyTu${PREFIX}_L1ImageFileReader
          COMMAND ${TEST_DRIVER}
          Execute
          ${PYTHON_EXECUTABLE} ${TEST_ORCHESTRATOR}/test_maja_l1_image_reader.py
          "-i" ${MAJADATA_TV_VENUS_INPUT}/VE-V-L2INIT-002-F-N-VENUS-IFPDS
          "-o" ${MAJA_TEST_OUTPUT_ROOT}/TU/VENUS
          )


add_test(NAME pyTu${PREFIX}_L1ImageReader_L1PIX
          COMMAND ${VNS_TEST_DRIVER}
          --compare-image ${EPSILON_4}
          ${MAJADATA_TU_L1_READER_VENUS_BASELINE}/l1pix.tif
          ${MAJA_TEST_OUTPUT_ROOT}/TU/VENUS/l1pix.tif
          "--output-directory"
          ${MAJA_TEST_OUTPUT_ROOT}/TU/VENUS/testing-compare-output-directory
          ${MAJA_BINARY_DIR}/bin/vnsDummyProgram.sh
          )


add_test(NAME pyTu${PREFIX}_L1ImageReader_L1TOA
          COMMAND ${VNS_TEST_DRIVER}
          --compare-image ${EPSILON_4}
          ${MAJADATA_TU_L1_READER_VENUS_BASELINE}/l1toa.tif
          ${MAJA_TEST_OUTPUT_ROOT}/TU/VENUS/l1toa.tif
          "--output-directory"
          ${MAJA_TEST_OUTPUT_ROOT}/TU/VENUS/testing-compare-output-directory
          ${MAJA_BINARY_DIR}/bin/vnsDummyProgram.sh
          )


add_test(NAME pyTu${PREFIX}_L1ImageReader_L2PIX
          COMMAND ${VNS_TEST_DRIVER}
          --compare-image ${EPSILON_4}
          ${MAJADATA_TU_L1_READER_VENUS_BASELINE}/l2pix.tif
          ${MAJA_TEST_OUTPUT_ROOT}/TU/VENUS/l2pix.tif
          "--output-directory"
          ${MAJA_TEST_OUTPUT_ROOT}/TU/VENUS/testing-compare-output-directory
          ${MAJA_BINARY_DIR}/bin/vnsDummyProgram.sh
          )


add_test(NAME pyTu${PREFIX}_L1ImageReader_EDGSub
          COMMAND ${VNS_TEST_DRIVER}
          --compare-image ${EPSILON_4}
          ${MAJADATA_TU_L1_READER_VENUS_BASELINE}/edgsub.tif
          ${MAJA_TEST_OUTPUT_ROOT}/TU/VENUS/edgsub.tif
          "--output-directory"
          ${MAJA_TEST_OUTPUT_ROOT}/TU/VENUS/testing-compare-output-directory
          ${MAJA_BINARY_DIR}/bin/vnsDummyProgram.sh
          )

add_test(NAME pyTu${PREFIX}_L1ImageReader_L2TOA
          COMMAND ${VNS_TEST_DRIVER}
          --compare-image ${EPSILON_4}
          ${MAJADATA_TU_L1_READER_VENUS_BASELINE}/l2toa.tif
          ${MAJA_TEST_OUTPUT_ROOT}/TU/VENUS/l2toa.tif
          "--output-directory"
          ${MAJA_TEST_OUTPUT_ROOT}/TU/VENUS/testing-compare-output-directory
          ${MAJA_BINARY_DIR}/bin/vnsDummyProgram.sh
          )

add_test(NAME pyTu${PREFIX}_L1ImageReader_TOASub
          COMMAND ${VNS_TEST_DRIVER}
          --compare-image ${EPSILON_4}
          ${MAJADATA_TU_L1_READER_VENUS_BASELINE}/toasub.tif
          ${MAJA_TEST_OUTPUT_ROOT}/TU/VENUS/toasub.tif
          "--output-directory"
          ${MAJA_TEST_OUTPUT_ROOT}/TU/VENUS/testing-compare-output-directory
          ${MAJA_BINARY_DIR}/bin/vnsDummyProgram.sh
          )


add_test(NAME pyTu${PREFIX}_L1ImageReader_L2EDG
          COMMAND ${VNS_TEST_DRIVER}
          --compare-image ${EPSILON_4}
          ${MAJADATA_TU_L1_READER_VENUS_BASELINE}/l2edg.tif
          ${MAJA_TEST_OUTPUT_ROOT}/TU/VENUS/l2edg.tif
          "--output-directory"
          ${MAJA_TEST_OUTPUT_ROOT}/TU/VENUS/testing-compare-output-directory
          ${MAJA_BINARY_DIR}/bin/vnsDummyProgram.sh
          )


add_test(NAME pyTu${PREFIX}_L1ImageReader_L2SAT
          COMMAND ${VNS_TEST_DRIVER}
          --compare-image ${EPSILON_4}
          ${MAJADATA_TU_L1_READER_VENUS_BASELINE}/l2sat.tif
          ${MAJA_TEST_OUTPUT_ROOT}/TU/VENUS/l2sat.tif
          "--output-directory"
          ${MAJA_TEST_OUTPUT_ROOT}/TU/VENUS/testing-compare-output-directory
          ${MAJA_BINARY_DIR}/bin/vnsDummyProgram.sh
          )

add_test(NAME pyTu${PREFIX}_L1ImageReader_SATSub
          COMMAND ${VNS_TEST_DRIVER}
          --compare-image ${EPSILON_4}
          ${MAJADATA_TU_L1_READER_VENUS_BASELINE}/satsub.tif
          ${MAJA_TEST_OUTPUT_ROOT}/TU/VENUS/satsub.tif
          "--output-directory"
          ${MAJA_TEST_OUTPUT_ROOT}/TU/VENUS/testing-compare-output-directory
          ${MAJA_BINARY_DIR}/bin/vnsDummyProgram.sh
          )


add_test(NAME pyTu${PREFIX}_L1ImageReader_SOL1
          COMMAND ${VNS_TEST_DRIVER}
          --compare-image ${EPSILON_4}
          ${MAJADATA_TU_L1_READER_VENUS_BASELINE}/sol1.tif
          ${MAJA_TEST_OUTPUT_ROOT}/TU/VENUS/sol1.tif
          "--output-directory"
          ${MAJA_TEST_OUTPUT_ROOT}/TU/VENUS/testing-compare-output-directory
          ${MAJA_BINARY_DIR}/bin/vnsDummyProgram.sh
          )

add_test(NAME pyTu${PREFIX}_L1ImageReader_SOL2
          COMMAND ${VNS_TEST_DRIVER}
          --compare-image ${EPSILON_4}
          ${MAJADATA_TU_L1_READER_VENUS_BASELINE}/sol2.tif
          ${MAJA_TEST_OUTPUT_ROOT}/TU/VENUS/sol2.tif
          "--output-directory"
          ${MAJA_TEST_OUTPUT_ROOT}/TU/VENUS/testing-compare-output-directory
          ${MAJA_BINARY_DIR}/bin/vnsDummyProgram.sh
          )


add_test(NAME pyTu${PREFIX}_L1ImageReader_DTMVIE
          COMMAND ${VNS_TEST_DRIVER}
          --compare-image ${EPSILON_4}
          ${MAJADATA_TU_L1_READER_VENUS_BASELINE}/dtmvie.tif
          ${MAJA_TEST_OUTPUT_ROOT}/TU/VENUS/dtmvie.tif
          "--output-directory"
          ${MAJA_TEST_OUTPUT_ROOT}/TU/VENUS/testing-compare-output-directory
          ${MAJA_BINARY_DIR}/bin/vnsDummyProgram.sh
          )

add_test(NAME pyTu${PREFIX}_L1ImageReader_ShadowVIE
          COMMAND ${VNS_TEST_DRIVER}
          --compare-image ${EPSILON_4}
          ${MAJADATA_TU_L1_READER_VENUS_BASELINE}/shadowvie.tif
          ${MAJA_TEST_OUTPUT_ROOT}/TU/VENUS/shadowvie.tif
          "--output-directory"
          ${MAJA_TEST_OUTPUT_ROOT}/TU/VENUS/testing-compare-output-directory
          ${MAJA_BINARY_DIR}/bin/vnsDummyProgram.sh
          )
