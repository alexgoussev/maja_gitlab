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

OTB_CREATE_APPLICATION(NAME           IncidenceAngle
                       SOURCES        vnsAppIncidenceAngle.cxx
                       LINK_LIBRARIES OTBImageIO ${MAJA_LIBRARY_PREFIXNAME}DataIO)

OTB_CREATE_APPLICATION(NAME           SolarAngle
                       SOURCES        vnsAppSolarAngle.cxx
                       LINK_LIBRARIES OTBImageIO ${MAJA_LIBRARY_PREFIXNAME}DataIO)
                       
OTB_CREATE_APPLICATION(NAME           Resampling
                       SOURCES        vnsAppResampling.cxx
                       LINK_LIBRARIES OTBImageIO ${MAJA_LIBRARY_PREFIXNAME}DataIO ${MAJA_LIBRARY_PREFIXNAME}AlgorithmsCommon)
                       
OTB_CREATE_APPLICATION(NAME           Stats
                       SOURCES        vnsAppStats.cxx
                       LINK_LIBRARIES OTBImageIO ${MAJA_LIBRARY_PREFIXNAME}DataIO)
                       
OTB_CREATE_APPLICATION(NAME           SmoothingBis
                       SOURCES        vnsSmoothing.cxx
                       LINK_LIBRARIES OTBImageIO ${MAJA_LIBRARY_PREFIXNAME}DataIO)                       
                       
OTB_CREATE_APPLICATION(NAME           ConcatenatePerZone
                       SOURCES        vnsAppConcatenatePerZone.cxx
                       LINK_LIBRARIES OTBImageIO ITKMetaIO ${MAJA_LIBRARY_PREFIXNAME}DataIO)   
                       
OTB_CREATE_APPLICATION(NAME           AngleListToImage
                       SOURCES        vnsAppAngleListToImage.cxx
                       LINK_LIBRARIES OTBImageIO ITKMetaIO ${MAJA_LIBRARY_PREFIXNAME}DataIO ${MAJA_LIBRARY_PREFIXNAME}AlgorithmsCommon)       

OTB_CREATE_APPLICATION(NAME           BinaryConcatenate
                       SOURCES        vnsAppBinaryConcatenate.cxx
                       LINK_LIBRARIES OTBImageIO ITKMetaIO ${MAJA_LIBRARY_PREFIXNAME}DataIO ${MAJA_LIBRARY_PREFIXNAME}AlgorithmsCommon)       

OTB_CREATE_APPLICATION(NAME           BinaryToVector
                       SOURCES        vnsAppBinaryToVector.cxx
                       LINK_LIBRARIES OTBImageIO ITKMetaIO ${MAJA_LIBRARY_PREFIXNAME}DataIO ${MAJA_LIBRARY_PREFIXNAME}AlgorithmsCommon)       
                       
OTB_CREATE_APPLICATION(NAME           MultiplyByScalar
                       SOURCES        vnsAppMultiplyByScalarVectorImage.cxx
                       LINK_LIBRARIES OTBImageIO ITKMetaIO ${MAJA_LIBRARY_PREFIXNAME}DataIO ${MAJA_LIBRARY_PREFIXNAME}AlgorithmsCommon)       
                       
OTB_CREATE_APPLICATION(NAME           ImageListWriter
                       SOURCES        vnsAppImageListWriter.cxx
                       LINK_LIBRARIES OTBImageIO ITKMetaIO ${MAJA_LIBRARY_PREFIXNAME}DataIO)
                       
OTB_CREATE_APPLICATION(NAME           OzoneExtractor
                       SOURCES        vnsAppOzoneExtractor.cxx
                       LINK_LIBRARIES OTBImageIO ITKMetaIO ${MAJA_LIBRARY_PREFIXNAME}DataIO)

OTB_CREATE_APPLICATION(NAME           OneBandEqualThreshold
                       SOURCES        vnsAppOneBandEqualThreshold.cxx
                       LINK_LIBRARIES OTBImageIO ITKMetaIO ${MAJA_LIBRARY_PREFIXNAME}DataIO)
                      
OTB_CREATE_APPLICATION(NAME           RoundImage
                       SOURCES        vnsAppRoundImage.cxx
                       LINK_LIBRARIES OTBImageIO ITKMetaIO ${MAJA_LIBRARY_PREFIXNAME}DataIO)

OTB_CREATE_APPLICATION(NAME           RoundVectorImage
                       SOURCES        vnsAppRoundVectorImage.cxx
                       LINK_LIBRARIES OTBImageIO ITKMetaIO ${MAJA_LIBRARY_PREFIXNAME}DataIO)

OTB_CREATE_APPLICATION(NAME           RescaleIntensity
                       SOURCES        vnsAppRescaleIntensity.cxx
                       LINK_LIBRARIES OTBImageIO ITKMetaIO ${MAJA_LIBRARY_PREFIXNAME}DataIO)
                    
OTB_CREATE_APPLICATION(NAME           ChangeValues
                       SOURCES        vnsAppChangeValues.cxx
                       LINK_LIBRARIES OTBImageIO ITKMetaIO ${MAJA_LIBRARY_PREFIXNAME}DataIO)
                       