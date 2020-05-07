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

SET(MAJADATA_TU_CODE ${MAJADATA_TU}/Code)
SET(INPUT_MAJADATATU_IMAGES                    ${MAJADATA_TU_CODE}/Images)
SET(INPUT_MAJADATATU_FILES                     ${MAJADATA_TU_CODE}/Files)
SET(INPUT_MAJADATATU_IMAGES_DTM  ${INPUT_MAJADATATU_IMAGES}/dtm)
SET(BASELINEDATATU_FILES              ${MAJADATA_TU_CODE}/Baseline/Files)

ADD_SUBDIRECTORY(Code)
ADD_SUBDIRECTORY(Utilities)
ADD_SUBDIRECTORY(orchestrator)
