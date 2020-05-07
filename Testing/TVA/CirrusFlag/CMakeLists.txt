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
# VERSION : 1-0-0 : <TypeFT> : <NumFT> : 04 janvier 2019 : Creation                                        #
#                                                                                                          #
# FIN-HISTORIQUE                                                                                           #
#                                                                                                          #
# $Id                                                                                                      #
#                                                                                                          #
############################################################################################################

maja_test_application(NAME apTvCirrusFlag
                     APP  CirrusFlag
                     OPTIONS -cla ${MAJADATA_TVA_INPUT}/CirrusFlagTest/CAMARGUE_20120103_CLA_sub.tif
                     -edg ${MAJADATA_TVA_INPUT}/CirrusFlagTest/CAMARGUE_20120103_VE_ortho_toa_bord_100m
                     -altthreshold 1000
                     -minpercentcirrus 10
                     -minpercentcloud 15
                     -minstdcirrus 10
                     -minpercentstdcirrus 500
                     -nodata -10
                     TESTENVOPTIONS ${MAJA_TEST_OUTPUT_ROOT}/TVA/apTvcirrusFlag.txt

                     VALID --compare-ascii ${EPSILON_8}
                     ${MAJADATA_TVA_BASELINE}/apTvcirrusFlag.txt
                     ${MAJA_TEST_OUTPUT_ROOT}/TVA/apTvcirrusFlag.txt

                    )
