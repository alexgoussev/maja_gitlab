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
# $Id$
#                                                                                                          #
############################################################################################################
# - Find PUGIXML library
# Find PUGIXML-C includes and libraries
# This module defines
#  PUGIXML_INCLUDE_DIRS,
#  PUGIXML_LIBRARIES,.
#  PUGIXML_FOUND.
#

find_path(PUGIXML_INCLUDE_DIR NAMES pugixml.hpp)

find_library(PUGIXML_LIBRARY NAMES pugixml)

# handle the QUIETLY and REQUIRED arguments and set PUGIXML_FOUND to TRUE if
# all listed variables are TRUE
include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(PUGIXML DEFAULT_MSG
  PUGIXML_LIBRARY PUGIXML_INCLUDE_DIR)

if(PUGIXML_FOUND)
  message(STATUS "  PUGIXML includes    : ${PUGIXML_INCLUDE_DIR}")
  message(STATUS "  PUGIXML library     : ${PUGIXML_LIBRARY}")
endif()

mark_as_advanced(
  PUGIXML_INCLUDE_DIR
  PUGIXML_LIBRARY
)
