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
# VERSION : 5-1-0 : FA : LAIG-FA-MAC-144674-CS : 6 juin 2016 : Modification passage des COTS en parametre  #
# VERSION : 3-0-0 : DM : LAIG-DM-MAC-239-CNES : 10 mai 2013 : Creation pour la prise en compte de la DM du  #
#                                                            MACCS generique (PM LAIG-NT-MAC-0239-CNES)    #
#                                                                                                          #
# FIN-HISTORIQUE                                                                                           #
#                                                                                                          #
# $Id: FindPugixml.cmake 5694 2013-05-25 16:27:12Z tfeuvrie $
#                                                                                                          #
############################################################################################################
# - Find PUGIXML library
# Find PUGIXML-C includes and libraries
# This module defines
#  PUGIXML_INCLUDE_DIRS,
#  PUGIXML_LIBRARIES,.
#  PUGIXML_FOUND.
#

FIND_PATH(GD_INCLUDE_DIR gd.h 
  HINTS
  $ENV{GD_DIR}
  PATH_SUFFIXES include
)

FIND_LIBRARY(GD_LIBRARY
  NAMES libgd gd
  HINTS
  $ENV{GD_DIR}
  PATH_SUFFIXES lib64 lib
)

# set the user variables

# handle the QUIETLY and REQUIRED arguments and set GD_FOUND to TRUE if 
# all listed variables are TRUE
INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(GD  DEFAULT_MSG  GD_LIBRARY  GD_INCLUDE_DIR)

MARK_AS_ADVANCED(GD_LIBRARY GD_INCLUDE_DIR)

# IF(GD_FOUND)
#   SET(GD_INCLUDE_DIRS "${GD_INCLUDE_DIR}")
#   SET(GD_LIBRARIES "${GD_LIBRARY}")
# endif()
#MESSAGE(STATUS "  GD includes         : ${GD_INCLUDE_DIRS}")
#  MESSAGE(STATUS "  GD library          : ${GD_LIBRARY}")

