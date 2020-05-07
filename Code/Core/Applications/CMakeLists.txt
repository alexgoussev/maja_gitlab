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
# VERSION : 2-3-0 : DM : LAIG-DM-MAC-399-CNES : 28 aout 2012 : Modification suite a l'install relocatable  #
# VERSION : 2-0-0 : DM : LAIG-DM-MAC-146-CNES : 14 octobre 2011 : Modification pour prise en compte        #
#                                                            d'evolutions liees a MACCS                    #
#                                                                                                          #
# VERSION : 1-0-0 : <TypeFT> : <NumFT> : 24 mars 2010 : Creation
#                                                                                                          #
# FIN-HISTORIQUE                                                                                           #
#                                                                                                          #
# $Id$
#                                                                                                          #
############################################################################################################

ADD_SUBDIRECTORY(DTMProcessing)
ADD_SUBDIRECTORY(AthmosphericAbsorption)
ADD_SUBDIRECTORY(CirrusCorrection)
ADD_SUBDIRECTORY(ReduceLutComputation)
ADD_SUBDIRECTORY(RayleighCorrection)
ADD_SUBDIRECTORY(WaterVaporPostProcessing)
ADD_SUBDIRECTORY(AOTEstimation)
ADD_SUBDIRECTORY(CirrusMask)
ADD_SUBDIRECTORY(CirrusFlag)
ADD_SUBDIRECTORY(SnowMask)
ADD_SUBDIRECTORY(WaterMask)
ADD_SUBDIRECTORY(Composite)
ADD_SUBDIRECTORY(CloudMasking)
ADD_SUBDIRECTORY(ScatteringCorrection)
ADD_SUBDIRECTORY(SlopeCorrection)
ADD_SUBDIRECTORY(EnvCorrection)
ADD_SUBDIRECTORY(Common)


SET(processing "python3.7 $MAJA_INSTALL_DIR/lib/python/orchestrator/launcher/maja.py")
CONFIGURE_FILE(${MAJA_SOURCE_DIR}/Code/Core/script.sh.in
  ${MAJA_BINARY_DIR}/bin/maja @ONLY)

INSTALL(PROGRAMS ${MAJA_BINARY_DIR}/bin/maja DESTINATION ${MAJA_INSTALL_BIN_DIR})
