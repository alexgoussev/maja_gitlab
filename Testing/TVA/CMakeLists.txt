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


if(ENABLE_TVA)
    file(MAKE_DIRECTORY ${MAJA_TEST_OUTPUT_ROOT}/TVA)
endif()

SET(MAJADATA_TVA_INPUT ${MAJADATA_TVA}/Input)
SET(MAJADATA_TVA_BASELINE ${MAJADATA_TVA}/Baseline)



ADD_SUBDIRECTORY(Common)
ADD_SUBDIRECTORY(AOTEstimation)
ADD_SUBDIRECTORY(AthmosphericAbsorption)
ADD_SUBDIRECTORY(CirrusCorrection)
ADD_SUBDIRECTORY(CirrusFlag)
ADD_SUBDIRECTORY(CirrusMask)
ADD_SUBDIRECTORY(Composite)
ADD_SUBDIRECTORY(DTMProcessing)
ADD_SUBDIRECTORY(EnvCorrection)
ADD_SUBDIRECTORY(CloudMasking)
ADD_SUBDIRECTORY(RayleighCorrection)
ADD_SUBDIRECTORY(ReduceLutComputation)
ADD_SUBDIRECTORY(ScatteringCorrection)
ADD_SUBDIRECTORY(SlopeCorrection)
ADD_SUBDIRECTORY(SnowMask)
ADD_SUBDIRECTORY(WaterMask)
ADD_SUBDIRECTORY(WaterVaporPostProcessing)



