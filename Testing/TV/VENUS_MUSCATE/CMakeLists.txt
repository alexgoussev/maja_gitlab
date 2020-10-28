#
# Copyright (C) 2020 Centre National d'Etudes Spatiales (CNES)
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#    http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#
#
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
#########################################################################################REA###################
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

set(TEST_DRIVER_MAJA vnsTestMainLauncher)
set(TEST_DRIVER ${CMAKE_INSTALL_PREFIX}/bin/otbTestDriver.sh)
SET(MAJADATA_TV_VENUS_MUSCATE_BASELINE ${MAJADATA_TV}/VENUS_MUSCATE/Baseline)

if(ENABLE_TV)
    file(MAKE_DIRECTORY ${MAJA_TEST_OUTPUT_ROOT}/TV_VENUS_MUSCATE)
endif()


add_test(NAME pyTv-VE-L2INIT-VENUS-MUSCATE_CHAIN
          COMMAND ${TEST_DRIVER}
          Execute
          ${PYTHON_EXECUTABLE} ${ORCHESTRATOR}/launcher/maja.py
          "--input" "${MAJADATA_TV_VENUS_MUSCATE_INPUT}/VE-P-L2INIT-001-F-N-VENUS_MUSCATE-GENERAL"
          "--output" "${MAJA_TEST_OUTPUT_ROOT}/TV_VENUS_MUSCATE/"
          "-m" "L2INIT"
          "-l" "DEBUG"
          "-p" "VENUS_MUSCATE"
          "-ucs" ${MAJADATA_TV_VENUS_MUSCATE_INPUT}/../userconf
          "--stylesheet" "${MAJADATA_TV_VENUS_MUSCATE_INPUT}/VE-P-L2INIT-001-F-N-VENUS_MUSCATE-GENERAL/styleSheet_Overloading_GIPPs_Values.xsl"
          )
set_tests_properties(pyTv-VE-L2INIT-VENUS-MUSCATE_CHAIN PROPERTIES TIMEOUT 300000)



add_test(NAME pyTv-VE-L2INIT-VENUS-MUSCATE_COMP_IMAGE
        COMMAND ${TEST_DRIVER_MAJA}
        "--from-directory-compare-all-images" ${EPSILON_3}
        ${MAJADATA_TV_VENUS_MUSCATE_BASELINE}/VE-P-L2INIT-001-F-N-VENUS_MUSCATE-GENERAL/VENUS-XS_20120103-105148-000_L2A_CAMARGUE_C_V1-0/
        ${MAJADATA_TV_VENUS_MUSCATE_INPUT}/VE-P-L2INIT-001-F-N-VENUS_MUSCATE-GENERAL
        ${MAJA_TEST_OUTPUT_ROOT}/TV_VENUS_MUSCATE/VENUS-XS_20120103-105148-000_L2A_CAMARGUE_C_V1-0/
        "--recursively" "true" "--output-directory"
        ${MAJA_TEST_OUTPUT_ROOT}/TV_VENUS_MUSCATE/testing-compare-output-directory
        ${MAJA_BINARY_DIR}/bin/vnsDummyProgram.sh
        )


add_test(NAME pyTv-VE-L2INIT-VENUS-MUSCATE_COMP_ASCII
        COMMAND ${TEST_DRIVER_MAJA}
        "--from-directory-compare-all-ascii" ${EPSILON_3}
        ${MAJADATA_TV_VENUS_MUSCATE_BASELINE}/VE-P-L2INIT-001-F-N-VENUS_MUSCATE-GENERAL/VENUS-XS_20120103-105148-000_L2A_CAMARGUE_C_V1-0/
        ${MAJADATA_TV_VENUS_MUSCATE_INPUT}/VE-P-L2INIT-001-F-N-VENUS_MUSCATE-GENERAL
        ${MAJA_TEST_OUTPUT_ROOT}/TV_VENUS_MUSCATE/VENUS-XS_20120103-105148-000_L2A_CAMARGUE_C_V1-0/
        "--exclude-filename-with-key-matching" "8" "MAJAAdminConfig" "MAJAUserConfig" "PMC_LxREPT" "PMC_L1REPT" "PMC_L2REPT" "PMC_L3REPT" "perfos.xml" "JobOrder.xml"
        "--ignore-lines-with" "4" "Creator_Version" "Creation_Date" "Date_Time" "Chain_Version"
        "--recursively" "true" "--output-directory"
        ${MAJA_TEST_OUTPUT_ROOT}/TV_VENUS_MUSCATE/testing-compare-output-directory
        ${MAJA_BINARY_DIR}/bin/vnsDummyProgram.sh
        )