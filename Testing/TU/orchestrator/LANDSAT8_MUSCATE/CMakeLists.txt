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

add_test(NAME pyTuL1XMLReaderLandsat8MuscatePlugin
          COMMAND ${TEST_DRIVER}
          Execute
          ${PYTHON_EXECUTABLE} ${TEST_ORCHESTRATOR}/test_maja_l1_image_info.py
          "-i" ${MAJADATA_TV_LANDSAT8_MUSCATE_INPUT}/L8-V-L2INIT-011-F-N-LANDSAT8_MUSCATE-GENERAL
          )

add_test(NAME pyTuL1ImageReaderLandsat8MuscatePlugin
         COMMAND ${TEST_DRIVER}
         --compare-n-images 0.00001 8
         #IPEDGSubOutput
         ${MAJADATA_TU_L1_READER_LANDSAT8_MUSCATE_BASELINE}/apTuL1Reader_LANDSAT8_MUSCATE_IPEDGSubOutput.tif
         ${MAJA_TEST_OUTPUT_ROOT}/TU/LANDSAT8_MUSCATE/tmp_edg_sub_oneBandEqual.tif
         #IPAOTSubOutput
         ${MAJADATA_TU_L1_READER_LANDSAT8_MUSCATE_BASELINE}/apTuL1Reader_LANDSAT8_MUSCATE_IPAOTSubOutput.tif
         ${MAJA_TEST_OUTPUT_ROOT}/TU/LANDSAT8_MUSCATE/aot_sub.tif
         # IPSATSubOutput
         ${MAJADATA_TU_L1_READER_LANDSAT8_MUSCATE_BASELINE}/apTuL1Reader_LANDSAT8_MUSCATE_IPSATSubOutput.tif
         ${MAJA_TEST_OUTPUT_ROOT}/TU/LANDSAT8_MUSCATE/SubSatVector.tif
         #CLAImage
         ${MAJADATA_TU_L1_READER_LANDSAT8_MUSCATE_BASELINE}/apTuL1Reader_LANDSAT8_MUSCATE_CLAImage.tif
         ${MAJA_TEST_OUTPUT_ROOT}/TU/LANDSAT8_MUSCATE/cla_constant_sub.tif
         #L2TOAImageList
         ${MAJADATA_TU_L1_READER_LANDSAT8_MUSCATE_BASELINE}/apTuL1Reader_LANDSAT8_MUSCATE_L2TOAImageOutput.tif
         ${MAJA_TEST_OUTPUT_ROOT}/TU/LANDSAT8_MUSCATE/L2TOAImageListVector_R1.tif
         # L2EDGOutputList
         ${MAJADATA_TU_L1_READER_LANDSAT8_MUSCATE_BASELINE}/apTuL1Reader_LANDSAT8_MUSCATE_L2EDGImageOutput.tif
         ${MAJA_TEST_OUTPUT_ROOT}/TU/LANDSAT8_MUSCATE/IPEDGMaskL2_R1.tif
         #SOL1Image
         ${MAJADATA_TU_L1_READER_LANDSAT8_MUSCATE_BASELINE}/apTuL1Reader_LANDSAT8_MUSCATE_SOL1Image.tif
         ${MAJA_TEST_OUTPUT_ROOT}/TU/LANDSAT8_MUSCATE/sol1_concat.tif
         #L2SAT
         ${MAJADATA_TU_L1_READER_LANDSAT8_MUSCATE_BASELINE}/apTuL1Reader_LANDSAT8_MUSCATE_L2SATMaskOutput.tif
         ${MAJA_TEST_OUTPUT_ROOT}/TU/LANDSAT8_MUSCATE/tmp_sat_resample_0.tif
         Execute
         ${PYTHON_EXECUTABLE} ${TEST_ORCHESTRATOR}/test_maja_l1_image_reader.py
         "-i" ${MAJADATA_TV_LANDSAT8_MUSCATE_INPUT}/L8-V-L2INIT-011-F-N-LANDSAT8_MUSCATE-GENERAL
         "-o" ${MAJA_TEST_OUTPUT_ROOT}/TU/LANDSAT8_MUSCATE
         )


add_test(NAME pyTuL2WriterLandsat8MuscatePlugin_chain
          COMMAND ${TEST_DRIVER}
          Execute
          ${PYTHON_EXECUTABLE} ${TEST_ORCHESTRATOR}/PythonTestDriver.py test_maja_l2_writer
          ${MAJADATA_TV_LANDSAT8_MUSCATE_INPUT}/L8-V-L2INIT-011-F-N-LANDSAT8_MUSCATE-GENERAL
          ${MAJADATA_TU}/L2Writer/LANDSAT8_MUSCATE/Input/
          ${MAJA_TEST_OUTPUT_ROOT}/TU/LANDSAT8_MUSCATE
          "8"
          "70"
          "4"
          )



add_test(NAME pyTuL2WriterLandsat8MuscatePlugin_comp_images
          COMMAND ${MAJA_BINARY_DIR}/bin/vnsTestMainLauncher.sh
          "--from-directory-compare-all-images" "0.001"
          ${MAJADATA_TU_L2_WRITER_LANDSAT8_MUSCATE_BASELINE}/LANDSAT8-OLITIRS-XS_20170501-103532-111_L2A_T31TCH_C_V1-0/
          ${MAJADATA_TV_LANDSAT8_MUSCATE_INPUT}/L8-V-L2INIT-011-F-N-LANDSAT8_MUSCATE-GENERAL
          ${MAJA_TEST_OUTPUT_ROOT}/TU/LANDSAT8_MUSCATE/LANDSAT8-OLITIRS-XS_20170501-103532-111_L2A_T31TCH_C_V1-0/
          "--recursively" "true" "--output-directory"
          ${MAJA_TEST_OUTPUT_ROOT}/TU/LANDSAT8_MUSCATE/testing-compare-output-directory
          ${MAJA_BINARY_DIR}/bin/vnsDummyProgram.sh
          )
set_tests_properties(pyTuL2WriterLandsat8MuscatePlugin_comp_images
    PROPERTIES DEPENDS pyTuL2WriterLandsat8MuscatePlugin_chain)

add_test(NAME pyTuL2WriterLandsat8MuscatePlugin_comp_ascii
          COMMAND ${MAJA_BINARY_DIR}/bin/vnsTestMainLauncher.sh
          "--from-directory-compare-all-ascii" "0.001"
          ${MAJADATA_TU_L2_WRITER_LANDSAT8_MUSCATE_BASELINE}/LANDSAT8-OLITIRS-XS_20170501-103532-111_L2A_T31TCH_C_V1-0/
          ${MAJADATA_TV_LANDSAT8_MUSCATE_INPUT}/L8-V-L2INIT-011-F-N-LANDSAT8_MUSCATE-GENERAL
          ${MAJA_TEST_OUTPUT_ROOT}/TU/LANDSAT8_MUSCATE/LANDSAT8-OLITIRS-XS_20170501-103532-111_L2A_T31TCH_C_V1-0/
          "--exclude-filename-with-key-matching" "8" "MAJAAdminConfig" "MAJAUserConfig" "PMC_LxREPT" "PMC_L1REPT" "PMC_L2REPT" "PMC_L3REPT" "perfos.xml" "JobOrder.xml"
          "--ignore-lines-with" "4" "Creator_Version" "Creation_Date" "Date_Time" "Chain_Version"
          "--recursively" "true" "--output-directory"
          ${MAJA_TEST_OUTPUT_ROOT}/TU/LANDSAT8_MUSCATE/testing-compare-output-directory
          ${MAJA_BINARY_DIR}/bin/vnsDummyProgram.sh
          )
set_tests_properties(pyTuL2WriterLandsat8MuscatePlugin_comp_ascii
    PROPERTIES DEPENDS pyTuL2WriterLandsat8MuscatePlugin_chain)

add_test(NAME pyTuL2HeaderWriter-Landsat8-cross
          COMMAND ${TEST_DRIVER}
          Execute ${PYTHON_EXECUTABLE}
          ${ORCHESTRATOR}/tests/test_maja_l2_cross_writer.py
          "${MAJADATA_TV_LANDSAT8_INPUT}/L8-V-L2INIT-001-F-N-LANDSAT8-GENERAL"
          "${MAJA_TEST_OUTPUT_ROOT}/TU/LANDSAT8_MUSCATE/cross"
          )
