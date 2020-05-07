############################################################################################################
#                                                                                                          #
#                                ooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo         #
#                             o                                                                            #
#                          o                                                                               #
#                        o                                                                                 #
#                      o                                                                                   #
#                     o       ooooooo       ooooooo    o         o      oo                                 #
#    o              o       o        o     o       o   o         o     o   o                               #
#      o           o       o          o   o         o  o         o    o      o                             #
#        o        o       o           o   o         o  o         o    o        o                           #
#         o      o        o      oooo     o         o  o         o   o           o                         #
#          o    o          o              o         o  o         o   o           o                         #
#           o  o            o             o         o  o o      o   o          o                           #
#            oo              oooooooo    o         o   o  oooooo   o      oooo                             #
#                                                     o                                                    #
#                                                     o                                                    #
#                                                    o                            o                        #
#                                                    o            o      oooo     o   o      oooo          #
#                                                   o             o         o    o    o         o          #
#                                                   o            o       ooo     o   o       ooo           #
#                                                               o       o       o   o          o           #
#                                                               ooooo   oooo    o   ooooo  oooo            #
#                                                                              o                           #
#                                                                                                          #
############################################################################################################
#                                                                                                          #
# Author: CS Systemes d'Information  (France)                                                              #
#                                                                                                          #
############################################################################################################
# HISTORIQUE                                                                                               #
#                                                                                                          #
# VERSION : 1-0-0 : <TypeFT> : <NumFT> : 15 novembre 2009 : Creation                                                           
#                                                                                                          #
# FIN-HISTORIQUE                                                                                           #
#                                                                                                          #
# $Id$
#                                                                                                          #
############################################################################################################


IF( NOT MAJA_DISABLE_CXX_TESTING )
SET(PREFIX "DirectionalCorrection")

SET(TESTS1 ${CXX_TEST_PATH}/vnsDirectionalCorrectionTest1)

ADD_TEST(${PREFIX}DirectionalCorrectionComputeTest ${TESTS1}
    --compare-n-ascii ${NOTOL} 1
    ${BASELINEDATATU_FILES}/${PREFIX}vnsDirectionalCorrectionComputeTest.txt
    ${TEMP}/${PREFIX}vnsDirectionalCorrectionComputeTest.txt
     vnsDirectionalCorrectionComputeTest
     ${TEMP}/${PREFIX}vnsDirectionalCorrectionComputeTest.txt
    )


# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ vnsDirectionalCorrectionTests1 ~~~~~~~~~~~~~~~~~~~~~~~~
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~



# Src1 sources files
SET(SRCS1
vnsDirectionalCorrectionTests1.cxx
vnsDirectionalCorrectionComputeTest.cxx
)

ADD_EXECUTABLE(vnsDirectionalCorrectionTest1 ${SRCS1})
TARGET_LINK_LIBRARIES(vnsDirectionalCorrectionTest1 ${OTB_LIBRARIES}
${MAJA_LIBRARY_PREFIXNAME}DataIO 
${MAJA_LIBRARY_PREFIXNAME}DataCommon
${MAJA_LIBRARY_PREFIXNAME}TestHelperLibrary )


ENDIF( NOT MAJA_DISABLE_CXX_TESTING )
