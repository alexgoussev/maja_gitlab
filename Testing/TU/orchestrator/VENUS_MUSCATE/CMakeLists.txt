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



add_test(NAME pyTuL1XMLReaderVenusMuscatePlugin
         COMMAND ${TEST_DRIVER}
         Execute
         ${PYTHON_EXECUTABLE} ${TEST_ORCHESTRATOR}/test_maja_l1_image_info.py
         "-i" ${MAJADATA_TV_VENUS_MUSCATE_INPUT}/VE-P-L2INIT-001-F-N-VENUS_MUSCATE-GENERAL
          )

add_test(NAME pyTuL1ImageReaderVenusMuscatePlugin
          COMMAND ${TEST_DRIVER}
          --compare-n-images ${EPSILON_4} 12
          #IPEDGSubOutput
          ${MAJADATA_TU_L1_READER_VENUS_MUSCATE_BASELINE}/apTuL1Reader_VENUS_MUSCATE_IPEDGSubOutput.tif
          ${MAJA_TEST_OUTPUT_ROOT}/TU/VENUS_MUSCATE/IPEDGSubOutput.tif

          #IPAOTSubOutput
          ${MAJADATA_TU_L1_READER_VENUS_MUSCATE_BASELINE}/apTuL1Reader_VENUS_MUSCATE_IPAOTSubOutput.tif
          ${MAJA_TEST_OUTPUT_ROOT}/TU/VENUS_MUSCATE/IPTOASubOutput.tif

          # IPSATSubOutput
          ${MAJADATA_TU_L1_READER_VENUS_MUSCATE_BASELINE}/apTuL1Reader_VENUS_MUSCATE_IPSATSubOutput.tif
          ${MAJA_TEST_OUTPUT_ROOT}/TU/VENUS_MUSCATE/IPSATSubOutput.tif

          #CLAImage
          ${MAJADATA_TU_L1_READER_VENUS_MUSCATE_BASELINE}/apTuL1Reader_VENUS_MUSCATE_CLAImage.tif
          ${MAJA_TEST_OUTPUT_ROOT}/TU/VENUS_MUSCATE/CLAImage.tif
          

          # L2EDGOutputList
          ${MAJADATA_TU_L1_READER_VENUS_MUSCATE_BASELINE}/apTuL1Reader_VENUS_MUSCATE_L2EDGOutput.tif
          ${MAJA_TEST_OUTPUT_ROOT}/TU/VENUS_MUSCATE/L2EDGOutputList_R1.tif
          #SOL1Image
          ${MAJADATA_TU_L1_READER_VENUS_MUSCATE_BASELINE}/apTuL1Reader_VENUS_MUSCATE_SOL1Image.tif
          ${MAJA_TEST_OUTPUT_ROOT}/TU/VENUS_MUSCATE/SOL1Image.tif

          #SOL2Image
          ${MAJADATA_TU_L1_READER_VENUS_MUSCATE_BASELINE}/apTuL1Reader_VENUS_MUSCATE_SOL2Image.tif
          ${MAJA_TEST_OUTPUT_ROOT}/TU/VENUS_MUSCATE/SOL2Image.tif

          #L2SATMaskList
          ${MAJADATA_TU_L1_READER_VENUS_MUSCATE_BASELINE}/apTuL1Reader_VENUS_MUSCATE_L2SATMaskOutput.tif
          ${MAJA_TEST_OUTPUT_ROOT}/TU/VENUS_MUSCATE/L2SATMaskList_R1.tif

          #L2TOAImageList
          ${MAJADATA_TU_L1_READER_VENUS_MUSCATE_BASELINE}/apTuL1Reader_VENUS_MUSCATE_L2TOAImageOutput.tif
          ${MAJA_TEST_OUTPUT_ROOT}/TU/VENUS_MUSCATE/L2TOAImageList_R1.tif

          #DTMVieImage
          ${MAJADATA_TU_L1_READER_VENUS_MUSCATE_BASELINE}/apTuL1Reader_VENUS_MUSCATE_DTMVIEImage.tif
          ${MAJA_TEST_OUTPUT_ROOT}/TU/VENUS_MUSCATE/DTMVieImage.tif

          #ShadowVIEImage
          ${MAJADATA_TU_L1_READER_VENUS_MUSCATE_BASELINE}/apTuL1Reader_VENUS_MUSCATE_ShadowVIEImage.tif
          ${MAJA_TEST_OUTPUT_ROOT}/TU/VENUS_MUSCATE/ShadowVIEImage.tif

          #L2PIX
          ${MAJADATA_TU_L1_READER_VENUS_MUSCATE_BASELINE}/apTuL1Reader_VENUS_MUSCATE_L2PIXImageOutput.tif
          ${MAJA_TEST_OUTPUT_ROOT}/TU/VENUS_MUSCATE/L2PIXImageList_R1.tif

          Execute
          ${PYTHON_EXECUTABLE} ${TEST_ORCHESTRATOR}/test_maja_l1_image_reader.py
          "-i" ${MAJADATA_TV_VENUS_MUSCATE_INPUT}/VE-P-L2INIT-001-F-N-VENUS_MUSCATE-GENERAL
          "-o" ${MAJA_TEST_OUTPUT_ROOT}/TU/VENUS_MUSCATE
          )


add_test(NAME pyTuL2WriterVenusMuscatePlugin_chain
          COMMAND ${TEST_DRIVER}
          Execute
          ${PYTHON_EXECUTABLE} ${TEST_ORCHESTRATOR}/PythonTestDriver.py test_maja_l2_writer
          ${MAJADATA_TV_VENUS_MUSCATE_INPUT}/VE-P-L2INIT-001-F-N-VENUS_MUSCATE-GENERAL
          ${MAJADATA_TU}/L2Writer/VENUS_MUSCATE/Input/
          ${MAJA_TEST_OUTPUT_ROOT}/TU/VENUS_MUSCATE
          "1"
          "3"
          "0"
          )

add_test(NAME pyTuL2WriterVenusMuscatePlugin_comp_images
          COMMAND ${MAJA_BINARY_DIR}/bin/vnsTestMainLauncher.sh
          "--from-directory-compare-all-images" ${EPSILON_3}
          ${MAJADATA_TU_L2_WRITER_VENUS_MUSCATE_BASELINE}/VENUS-XS_20120103-105148-000_L2A_CAMARGUE_C_V1-0/
          ${MAJADATA_TV_VENUS_MUSCATE_INPUT}/VE-P-L2INIT-001-F-N-VENUS_MUSCATE-GENERAL
          ${MAJA_TEST_OUTPUT_ROOT}/TU/VENUS_MUSCATE/VENUS-XS_20120103-105148-000_L2A_CAMARGUE_C_V1-0/
          "--recursively" "true" "--output-directory"
          ${MAJA_TEST_OUTPUT_ROOT}/TU/VENUS_MUSCATE/testing-compare-output-directory
          ${MAJA_BINARY_DIR}/bin/vnsDummyProgram.sh
          )

add_test(NAME pyTuL2WriterVenusMuscatePlugin_comp_ascii
          COMMAND ${MAJA_BINARY_DIR}/bin/vnsTestMainLauncher.sh
          "--from-directory-compare-all-ascii" ${EPSILON_3}
          ${MAJADATA_TU_L2_WRITER_VENUS_MUSCATE_BASELINE}/VENUS-XS_20120103-105148-000_L2A_CAMARGUE_C_V1-0/
          ${MAJADATA_TV_VENUS_MUSCATE_INPUT}/VE-P-L2INIT-001-F-N-VENUS_MUSCATE-GENERAL
          ${MAJA_TEST_OUTPUT_ROOT}/TU/VENUS_MUSCATE/VENUS-XS_20120103-105148-000_L2A_CAMARGUE_C_V1-0/
          "--exclude-filename-with-key-matching" "8" "MAJAAdminConfig" "MAJAUserConfig" "PMC_LxREPT" "PMC_L1REPT" "PMC_L2REPT" "PMC_L3REPT" "perfos.xml" "JobOrder.xml"
          "--ignore-lines-with" "4" "Creator_Version" "Creation_Date" "Date_Time" "Chain_Version"
          "--recursively" "true" "--output-directory"
          ${MAJA_TEST_OUTPUT_ROOT}/TU/VENUS_MUSCATE/testing-compare-output-directory
          ${MAJA_BINARY_DIR}/bin/vnsDummyProgram.sh
          )

add_test(NAME pyTuL2HeaderWriter-Venus-cross
          COMMAND ${TEST_DRIVER}
          Execute ${PYTHON_EXECUTABLE}
          ${TEST_ORCHESTRATOR}/test_maja_l2_cross_writer.py
          "${MAJADATA_TV_VENUS_INPUT}/VE-V-L2INIT-002-F-N-VENUS-IFPDS"
          "${MAJA_TEST_OUTPUT_ROOT}/TU/VENUS_MUSCATE/cross"
          )
