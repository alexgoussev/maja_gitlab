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
############################################################################################################
#                                                                                                          #
# Author: CS Systemes d'Information  (France)                                                              #
#                                                                                                          #
############################################################################################################
# HISTORIQUE                                                                                               #
#                                                                                                          #
# VERSION : 1-0-0 : <TypeFT> : <NumFT> : 26 aout 2019 : Creation                                           #
#                                                                                                          #
# FIN-HISTORIQUE                                                                                           #
#                                                                                                          #
# $Id                                                                                                      #
#                                                                                                          #
#                                                                                                          #
############################################################################################################


if(ENABLE_TU)
    file(MAKE_DIRECTORY ${MAJA_TEST_OUTPUT_ROOT}/TU)
    file(MAKE_DIRECTORY ${MAJA_TEST_OUTPUT_ROOT}/TU/SENTINEL2)
    file(MAKE_DIRECTORY ${MAJA_TEST_OUTPUT_ROOT}/TU/SENTINEL2_MUSCATE)
    file(MAKE_DIRECTORY ${MAJA_TEST_OUTPUT_ROOT}/TU/LANDSAT8_MUSCATE)
    file(MAKE_DIRECTORY ${MAJA_TEST_OUTPUT_ROOT}/TU/VENUS_MUSCATE)
    file(MAKE_DIRECTORY ${MAJA_TEST_OUTPUT_ROOT}/TU/LANDSAT8)
    file(MAKE_DIRECTORY ${MAJA_TEST_OUTPUT_ROOT}/TU/VENUS)
endif()


SET(MAJADATA_TU_L1_READER_LANDSAT8_BASELINE ${MAJADATA_TU}/L1Reader/LANDSAT8/Baseline)
SET(MAJADATA_TU_L1_READER_VENUS_BASELINE ${MAJADATA_TU}/L1Reader/VENUS/Baseline)


SET(MAJADATA_TU_L1_READER_LANDSAT8_MUSCATE_BASELINE ${MAJADATA_TU}/L1Reader/LANDSAT8_MUSCATE/Baseline)
SET(MAJADATA_TU_L2_WRITER_LANDSAT8_MUSCATE_BASELINE ${MAJADATA_TU}/L2Writer/LANDSAT8_MUSCATE/Baseline)
SET(MAJADATA_TU_L1_READER_SENTINEL2_DIR ${MAJADATA_TU}/L1Reader/SENTINEL2)
SET(MAJADATA_TU_L1_READER_SENTINEL2_MUSCATE_BASELINE ${MAJADATA_TU}/L1Reader/SENTINEL2_MUSCATE/Baseline)
SET(MAJADATA_TU_L2_WRITER_SENTINEL2_MUSCATE_BASELINE ${MAJADATA_TU}/L2Writer/SENTINEL2_MUSCATE/Baseline)
SET(MAJADATA_TU_L1_READER_VENUS_MUSCATE_BASELINE ${MAJADATA_TU}/L1Reader/VENUS_MUSCATE/Baseline)
SET(MAJADATA_TU_L2_WRITER_VENUS_MUSCATE_BASELINE ${MAJADATA_TU}/L2Writer/VENUS_MUSCATE/Baseline)

ADD_SUBDIRECTORY(LANDSAT8)
ADD_SUBDIRECTORY(LANDSAT8_MUSCATE)
ADD_SUBDIRECTORY(SENTINEL2_MUSCATE)
ADD_SUBDIRECTORY(VENUS_MUSCATE)
ADD_SUBDIRECTORY(VENUS)
ADD_SUBDIRECTORY(SENTINEL2)



