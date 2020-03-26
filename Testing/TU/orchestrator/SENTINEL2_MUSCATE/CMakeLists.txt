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

add_test(NAME pyTuL1XMLReaderSentinel2MuscatePlugin
         COMMAND ${TEST_DRIVER}
         Execute
         ${PYTHON_EXECUTABLE} ${TEST_ORCHESTRATOR}/test_maja_l1_image_info.py
         "-i" ${MAJADATA_TV_SENTINEL2_MUSCATE_INPUT}/S2-V-L2INIT-011-F-N-SENTINEL2_MUSCATE-GENERAL
          )


add_test(NAME pyTuL1ImageReaderSentinel2MuscatePlugin
         COMMAND ${TEST_DRIVER}
         --compare-n-images ${EPSILON_3} 18

         #IPAOTSubOutput
         ${MAJADATA_TU_L1_READER_SENTINEL2_MUSCATE_BASELINE}/apTuL1Reader_SENTINEL2_MUSCATE_IPAOTSubOutput.tif
         ${MAJA_TEST_OUTPUT_ROOT}/TU/SENTINEL2_MUSCATE/IPTOASubOutput.tif


         #IPEDGSubOutput
         ${MAJADATA_TU_L1_READER_SENTINEL2_MUSCATE_BASELINE}/apTuL1Reader_SENTINEL2_MUSCATE_IPEDGSubOutput.tif
         ${MAJA_TEST_OUTPUT_ROOT}/TU/SENTINEL2_MUSCATE/IPEDGSubOutput.tif


         #SOL1Image
         ${MAJADATA_TU_L1_READER_SENTINEL2_MUSCATE_BASELINE}/apTuL1Reader_SENTINEL2_MUSCATE_SOL1Image.tif
         ${MAJA_TEST_OUTPUT_ROOT}/TU/SENTINEL2_MUSCATE/SOL1Image.tif


         #L2EDGOutputList - R1
         ${MAJADATA_TU_L1_READER_SENTINEL2_MUSCATE_BASELINE}/apTuL1Reader_SENTINEL2_MUSCATE_L2EDG_R1.tif
         ${MAJA_TEST_OUTPUT_ROOT}/TU/SENTINEL2_MUSCATE/L2EDGOutputList_R1.tif


         #L2EDGOutputList - R2
         ${MAJADATA_TU_L1_READER_SENTINEL2_MUSCATE_BASELINE}/apTuL1Reader_SENTINEL2_MUSCATE_L2EDG_R2.tif
         ${MAJA_TEST_OUTPUT_ROOT}/TU/SENTINEL2_MUSCATE/L2EDGOutputList_R2.tif


         #IPSATSubOutput
         ${MAJADATA_TU_L1_READER_SENTINEL2_MUSCATE_BASELINE}/apTuL1Reader_SENTINEL2_MUSCATE_IPSATSubOutput.tif
         ${MAJA_TEST_OUTPUT_ROOT}/TU/SENTINEL2_MUSCATE/IPSATSubOutput.tif


         #CLAImage
         ${MAJADATA_TU_L1_READER_SENTINEL2_MUSCATE_BASELINE}/apTuL1Reader_SENTINEL2_MUSCATE_CLAImage.tif
         ${MAJA_TEST_OUTPUT_ROOT}/TU/SENTINEL2_MUSCATE/CLAImage.tif


         #L2DFP - R1
         ${MAJADATA_TU_L1_READER_SENTINEL2_MUSCATE_BASELINE}/apTuL1Reader_SENTINEL2_MUSCATE_L2DFP_R1.tif
         ${MAJA_TEST_OUTPUT_ROOT}/TU/SENTINEL2_MUSCATE/L2DFPImageList_R1.tif


         #L2DFP - R2
         ${MAJADATA_TU_L1_READER_SENTINEL2_MUSCATE_BASELINE}/apTuL1Reader_SENTINEL2_MUSCATE_L2DFP_R2.tif
         ${MAJA_TEST_OUTPUT_ROOT}/TU/SENTINEL2_MUSCATE/L2DFPImageList_R2.tif


         #L2SATMask - R1
         ${MAJADATA_TU_L1_READER_SENTINEL2_MUSCATE_BASELINE}/apTuL1Reader_SENTINEL2_MUSCATE_L2SATMasks_R1.tif
         ${MAJA_TEST_OUTPUT_ROOT}/TU/SENTINEL2_MUSCATE/L2SATMaskList_R1.tif


         #L2SATMask - R2
         ${MAJADATA_TU_L1_READER_SENTINEL2_MUSCATE_BASELINE}/apTuL1Reader_SENTINEL2_MUSCATE_L2SATMasks_R2.tif
         ${MAJA_TEST_OUTPUT_ROOT}/TU/SENTINEL2_MUSCATE/L2SATMaskList_R2.tif


         #L2ZoneMaskList - R1
         ${MAJADATA_TU_L1_READER_SENTINEL2_MUSCATE_BASELINE}/apTuL1Reader_SENTINEL2_MUSCATE_L2ZoneMaskListVector_R1.tif
         ${MAJA_TEST_OUTPUT_ROOT}/TU/SENTINEL2_MUSCATE/AngleZoneMaskList_R1.tif


         #L2ZoneMaskList - R1
         ${MAJADATA_TU_L1_READER_SENTINEL2_MUSCATE_BASELINE}/apTuL1Reader_SENTINEL2_MUSCATE_L2ZoneMaskListVector_R2.tif
         ${MAJA_TEST_OUTPUT_ROOT}/TU/SENTINEL2_MUSCATE/AngleZoneMaskList_R2.tif


         #L2TOAImageLIst - R1
         ${MAJADATA_TU_L1_READER_SENTINEL2_MUSCATE_BASELINE}/apTuL1Reader_SENTINEL2_MUSCATE_L2TOAImageList_R1.tif
         ${MAJA_TEST_OUTPUT_ROOT}/TU/SENTINEL2_MUSCATE/L2TOAImageList_R1.tif


         #L2TOAImageLIst - R2
         ${MAJADATA_TU_L1_READER_SENTINEL2_MUSCATE_BASELINE}/apTuL1Reader_SENTINEL2_MUSCATE_L2TOAImageList_R2.tif
         ${MAJA_TEST_OUTPUT_ROOT}/TU/SENTINEL2_MUSCATE/L2TOAImageList_R2.tif


         #DTMVIEImage
         ${MAJADATA_TU_L1_READER_SENTINEL2_MUSCATE_BASELINE}/apTuL1Reader_SENTINEL2_MUSCATE_DTMVIEImage.tif
         ${MAJA_TEST_OUTPUT_ROOT}/TU/SENTINEL2_MUSCATE/DTMVieImage.tif


         #ShadowVIEImage
         ${MAJADATA_TU_L1_READER_SENTINEL2_MUSCATE_BASELINE}/apTuL1Reader_SENTINEL2_MUSCATE_ShadowVIEImage.tif
         ${MAJA_TEST_OUTPUT_ROOT}/TU/SENTINEL2_MUSCATE/ShadowVIEImage.tif


         #L1TOACirrus
         ${MAJADATA_TU_L1_READER_SENTINEL2_MUSCATE_BASELINE}/apTuL1Reader_SENTINEL2_MUSCATE_L1TOACirrus.tif
         ${MAJA_TEST_OUTPUT_ROOT}/TU/SENTINEL2_MUSCATE/L1TOACirrusImage.tif


         Execute
         ${PYTHON_EXECUTABLE} ${TEST_ORCHESTRATOR}/test_maja_l1_image_reader.py
         "-i" ${MAJADATA_TV_SENTINEL2_MUSCATE_INPUT}/S2-V-L2INIT-011-F-N-SENTINEL2_MUSCATE-GENERAL
         "-o" ${MAJA_TEST_OUTPUT_ROOT}/TU/SENTINEL2_MUSCATE
         )
set_tests_properties(pyTuL1ImageReaderSentinel2MuscatePlugin PROPERTIES TIMEOUT 300000)


add_test(NAME pyTuL2WriterSentinel2MuscatePlugin_chain
          COMMAND ${TEST_DRIVER}
          Execute
          ${PYTHON_EXECUTABLE} ${TEST_ORCHESTRATOR}/PythonTestDriver.py test_maja_l2_writer
          ${MAJADATA_TV_SENTINEL2_MUSCATE_INPUT}/S2-V-L2INIT-011-F-N-SENTINEL2_MUSCATE-GENERAL/
          ${MAJADATA_TU}/L2Writer/SENTINEL2_MUSCATE/Input/
          ${MAJA_TEST_OUTPUT_ROOT}/TU/SENTINEL2_MUSCATE
          "1"
          "0"
          "0"
          )

add_test(NAME pyTuL2WriterSentinel2MuscatePlugin_comp_images
          COMMAND ${MAJA_BINARY_DIR}/bin/vnsTestMainLauncher.sh
          "--from-directory-compare-all-images" ${EPSILON_3}
          ${MAJADATA_TU_L2_WRITER_SENTINEL2_MUSCATE_BASELINE}/SENTINEL2B_20171008-105012-463_L2A_T31TCH_C_V1-0/
          ${MAJADATA_TV_SENTINEL2_MUSCATE_INPUT}/S2-V-L2INIT-011-F-N-SENTINEL2_MUSCATE-GENERAL/
          ${MAJA_TEST_OUTPUT_ROOT}/TU/SENTINEL2_MUSCATE/SENTINEL2B_20171008-105012-463_L2A_T31TCH_C_V1-0/
          "--recursively" "true" "--output-directory"
          ${MAJA_TEST_OUTPUT_ROOT}/TU/SENTINEL2_MUSCATE/testing-compare-output-directory
          ${MAJA_BINARY_DIR}/bin/vnsDummyProgram.sh
          )
set_tests_properties(pyTuL2WriterSentinel2MuscatePlugin_comp_images
    PROPERTIES DEPENDS pyTuL2WriterSentinel2MuscatePlugin_chain)

add_test(NAME pyTuL2WriterSentinel2MuscatePlugin_comp_ascii
          COMMAND ${MAJA_BINARY_DIR}/bin/vnsTestMainLauncher.sh
          "--from-directory-compare-all-ascii" ${EPSILON_3}
          ${MAJADATA_TU_L2_WRITER_SENTINEL2_MUSCATE_BASELINE}/SENTINEL2B_20171008-105012-463_L2A_T31TCH_C_V1-0/
          ${MAJADATA_TV_SENTINEL2_MUSCATE_INPUT}/S2-V-L2INIT-011-F-N-SENTINEL2_MUSCATE-GENERAL/
          ${MAJA_TEST_OUTPUT_ROOT}/TU/SENTINEL2_MUSCATE/SENTINEL2B_20171008-105012-463_L2A_T31TCH_C_V1-0/
          "--exclude-filename-with-key-matching" "8" "MAJAAdminConfig" "MAJAUserConfig" "PMC_LxREPT" "PMC_L1REPT" "PMC_L2REPT" "PMC_L3REPT" "perfos.xml" "JobOrder.xml"
          "--ignore-lines-with" "4" "Creator_Version" "Creation_Date" "Date_Time" "Chain_Version"
          "--recursively" "true" "--output-directory"
          ${MAJADATA_TU_L2_WRITER_SENTINEL2_MUSCATE_DIR}/testing-compare-output-directory
          ${MAJA_BINARY_DIR}/bin/vnsDummyProgram.sh
          )
set_tests_properties(pyTuL2WriterSentinel2MuscatePlugin_comp_ascii
    PROPERTIES DEPENDS pyTuL2WriterSentinel2MuscatePlugin_chain)

add_test(NAME pyTuL2HeaderWriter-Sentinel2-cross
          COMMAND ${TEST_DRIVER}
          Execute ${PYTHON_EXECUTABLE}
          ${TEST_ORCHESTRATOR}/test_maja_l2_cross_writer.py
          "${MAJADATA_TV_SENTINEL2_INPUT}/S2-V-L2INIT-001-F-N-SENTINEL2-GENERAL/"
          "${MAJA_TEST_OUTPUT_ROOT}/TU/SENTINEL2_MUSCATE/cross"
          )
