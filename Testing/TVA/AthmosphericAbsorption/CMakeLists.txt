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
# VERSION : 1-0-0 : <TypeFT> : <NumFT> :  07 fevrier 2019 : Creation                                       #
#                                                                                                          #
# FIN-HISTORIQUE                                                                                           #
#                                                                                                          #
# $Id                                                                                                      #
#                                                                                                          #
############################################################################################################

maja_test_application(NAME apTvPressureFilter
                     APP  PressureFilter
                     OPTIONS
                        -dtm ${MAJADATA_TVA_INPUT}/DTM/FORMOSAT/VE_TEST_AUX_REFDE2_SUDOUEST_0001.DBL.DIR/Sudouest_96m.mnt_ALC
                        -pressure ${MAJA_TEST_OUTPUT_ROOT}/TVA/aptvAthmosphericAbsorption_PressureFilter.tif

                     VALID   --compare-image ${EPSILON_7}
                     ${MAJADATA_TVA_BASELINE}/aptvAthmosphericAbsorption_PressureFilter.tif
                     ${MAJA_TEST_OUTPUT_ROOT}/TVA/aptvAthmosphericAbsorption_PressureFilter.tif

                    )


maja_test_application(NAME apTvTOACorrection
                     APP  TOACorrection
                     OPTIONS
                     -toa ${MAJADATA_TVA_INPUT}/AthmosphericAbsorption/Sudouest_20060819_MS_fmsat_ortho_toa.tif
                     -pressure ${MAJADATA_TVA_BASELINE}/aptvAthmosphericAbsorption_PressureFilter.tif
                     -smac ${MAJADATA_TVA_INPUT}/AthmosphericAbsorption/gipsmacmap.xml
                     -wateramountdefault 3
                     -ozoneamount 0.299999999999999988897769753748
                     -thetas 35.5579999999999998294697434176
                     -thetav 22.4879999999999995452526491135 22.4879999999999995452526491135 22.4879999999999995452526491135 22.4879999999999995452526491135
                     -nodata -10
                     -bandlist 0 1 2 3
                     -toac ${MAJA_TEST_OUTPUT_ROOT}/TVA/aptvAthmosphericAbsorption_TOACorrection.tif
                     VALID   --compare-image ${EPSILON_7}
                     ${MAJADATA_TVA_BASELINE}/aptvAthmosphericAbsorption_TOACorrection.tif
                     ${MAJA_TEST_OUTPUT_ROOT}/TVA/aptvAthmosphericAbsorption_TOACorrection.tif

                    )


maja_test_application(NAME apTvWaterAmountGeneratorFilter
                     APP  WaterAmountGeneratorFilter
                     OPTIONS
                     -toa ${MAJADATA_TVA_INPUT}/AthmosphericAbsorption/31TFJ_20150908_S2A_L1Csimu_toa_240m.tif
                     -gipwatv ${MAJADATA_TVA_INPUT}/AthmosphericAbsorption/giplutmap.xml
                     -watervaporreferencebandid 8
                     -watervaporbandid 9
                     -vapnodatavalue 0
                     -watervapormaxthreshold 5
                     -solarzenith 39.999222
                     -viewingzenith 6.191545
                     -wateramount ${MAJA_TEST_OUTPUT_ROOT}/TVA/aptvAthmosphericAbsorption_WaterAmount.tif

                     VALID   --compare-image ${EPSILON_7}
                     ${MAJADATA_TVA_BASELINE}/apTvAthmosphericAbsorption_WaterAmountGenerator.tif
                     ${MAJA_TEST_OUTPUT_ROOT}/TVA/aptvAthmosphericAbsorption_WaterAmount.tif

                    )
