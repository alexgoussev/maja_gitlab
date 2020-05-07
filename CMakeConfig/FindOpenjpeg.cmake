############################################################################################################
#                                                                                                          #
#                                        __  __    __     ____   __                                        #
#                                       (  \/  )  /__\   (_  _) /__\                                       #
#                                        )    (  /(__)\ .-_)(  /(__)\                                      #
#                                       (_/\/\_)(__)(__)\____)(__)(__)                                     #
#                                                                                                          #
#                                                                                                          #
############################################################################################################
#                                                                                                          #
# Author: CS Systemes d'Information  (France)                                                              #
#                                                                                                          #
############################################################################################################
# HISTORIQUE                                                                                               #
#                                                                                                          #
# VERSION : 5-1-0 : FA : LAIG-FA-MAC-144674-CS : 6 juin 2016 : Creation                                    #
#                                                                                                          #
# FIN-HISTORIQUE                                                                                           #
#                                                                                                          #
# $Id: FindPugixml.cmake 5694 2013-05-25 16:27:12Z tfeuvrie $
#                                                                                                          #
############################################################################################################
# - Find OpenJpeg library
# Find OPENJPEG and libraries
# This module defines
#  OPENJPEG_LIBRARIES,.
#

FIND_LIBRARY(OPENJPEG_LIBRARY 
    NAME openjp2
    HINTS ${MAJA_COTS_INSTALL_DIR}/openjpeg/lib
    PATHS ${MAJA_COTS_INSTALL_DIR}/openjpeg/lib)

if(OPENJPEG_LIBRARY)
  set(OPENJPEG_LIBRARIES ${OPENJPEG_LIBRARY})
  message(STATUS "  OPENJPEG library    : ${OPENJPEG_LIBRARIES}")
endif(OPENJPEG_LIBRARY)

mark_as_advanced(
  OPENJPEG_LIBRARY
)
