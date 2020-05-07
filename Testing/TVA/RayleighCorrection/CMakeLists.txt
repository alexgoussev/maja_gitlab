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
# VERSION : 1-0-0 : <TypeFT> : <NumFT> : 25 janvier 2019 : Creation                                        #
#                                                                                                          #
#                                                                                                          #
# FIN-HISTORIQUE                                                                                           #
#                                                                                                          #
# $Id                                                                                                      #
#                                                                                                          #
############################################################################################################

maja_test_application(NAME apTvRayleighCorrection
                     APP  RayleighCorrection
                     OPTIONS
                     -lutimage ${MAJADATA_TVA_INPUT}/RayleighCorrection/lut.mha
                     -lutheader ${MAJADATA_TVA_INPUT}/RayleighCorrection/giplut.xml
                     -toa ${MAJADATA_TVA_INPUT}/RayleighCorrection/Sudouest_20060819_MS_fmsat_ortho_toa_96m_AOTnull.tif
                     -edg ${MAJADATA_TVA_INPUT}/RayleighCorrection/Sudouest_20060819_MS_fmsat_ortho_toa_bord_96m
                     -dtm ${MAJADATA_TVA_INPUT}/DTM/FORMOSAT/VE_TEST_AUX_REFDE2_SUDOUEST_0001.DBL.DIR/Sudouest_96m.mnt_ALC
                     -nodata -10
                     -defaultaot 0
                     -tocr ${MAJA_TEST_OUTPUT_ROOT}/TVA/apTvRayleighCorrection.tif


                     VALID   --compare-image ${EPSILON_5}
                             ${MAJADATA_TVA_BASELINE}/apTvRayleighCorrection.tif
                             ${MAJA_TEST_OUTPUT_ROOT}/TVA/apTvRayleighCorrection.tif

                   )