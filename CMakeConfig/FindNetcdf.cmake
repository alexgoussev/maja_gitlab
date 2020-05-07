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
# VERSION : 3.0.0 : DM : LAIG-DM-MAJA-2369-CNES : 28 aout 2017 : Introduction données des CAMS             #
#                                                                                                          #
# FIN-HISTORIQUE                                                                                           #
#                                                                                                          #
# $Id: FindPugixml.cmake 5694 2013-05-25 16:27:12Z tfeuvrie $
#                                                                                                          #
############################################################################################################
# - Find Netcdf library
# Find Netcdf and libraries
# This module defines
#  NETCDF_LIBRARIES,.
#

FIND_LIBRARY(NETCDF_LIBRARY 
    NAME netcdf
    HINTS ${MAJA_COTS_INSTALL_DIR}/netcdf/lib
    PATHS ${MAJA_COTS_INSTALL_DIR}/netcdf/lib)

if(NETCDF_LIBRARY)
  set(NETCDF_LIBRARIES ${NETCDF_LIBRARY})
  message(STATUS "  NETCDF library    : ${NETCDF_LIBRARIES}")
endif(NETCDF_LIBRARY)

mark_as_advanced(
  NETCDF_LIBRARY
)
