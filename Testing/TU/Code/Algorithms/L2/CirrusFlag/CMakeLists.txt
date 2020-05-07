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
# VERSION : 1-0-0 : <TypeFT> : <NumFT> : 09 avril 2009 : Creation                                                           
#                                                                                                          #
# FIN-HISTORIQUE                                                                                           #
#                                                                                                          #
# $Id$
#                                                                                                          #
############################################################################################################

IF( NOT MAJA_DISABLE_CXX_TESTING )
SET(PREFIX "AlgorithmsL2Cirrus")


SET(TESTS1 ${CXX_TEST_PATH}/vnsL2CirrusTests1)

# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ vnsL2CirrusTests1 ~~~~~~~~~~~~~~~~~~~~~~~~~~
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

# -------    XMLFileHolder class with .xml file test
ADD_TEST(${PREFIX}CountCirrusPixelGeneratorNew ${TESTS1}
    vnsCountCirrusPixelGeneratorNew
    )
    
ADD_TEST(${PREFIX}CountCirrusPixelGeneratorTest ${TESTS1}
   --compare-n-ascii ${NOTOL} 1
    ${BASELINEDATATU_FILES}/${PREFIX}CountCirrusPixelGeneratorTest.txt
    ${TEMP}/${PREFIX}CountCirrusPixelGeneratorTest.txt
    vnsCountCirrusPixelGeneratorTest
    ${INPUT_MAJADATATU_IMAGES}/mask_B01.tif
    ${INPUT_MAJADATATU_IMAGES}/mask_EDG.tif
    ${TEMP}/${PREFIX}CountCirrusPixelGeneratorTest.txt
    0
    0
    )
    
        
# Src1 sources files
SET(SRCS1
vnsL2CirrusTests1.cxx
vnsCountCirrusPixelGeneratorNew.cxx
vnsCountCirrusPixelGeneratorTest.cxx
)


ADD_EXECUTABLE(vnsL2CirrusTests1 ${SRCS1})
TARGET_LINK_LIBRARIES(vnsL2CirrusTests1 ${OTB_LIBRARIES}
${MAJA_LIBRARY_PREFIXNAME}DataIO 
${MAJA_LIBRARY_PREFIXNAME}DataCommon 
${MAJA_LIBRARY_PREFIXNAME}AlgorithmsCommon
${MAJA_LIBRARY_PREFIXNAME}TestHelperLibrary )


ENDIF( NOT MAJA_DISABLE_CXX_TESTING )
