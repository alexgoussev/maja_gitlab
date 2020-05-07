############################################################################################################
#                                                                                                          #
#                                        __  __    __     ____   __                                        #
#                                       (  \/  )  /__\   (_  _) /__\                                       #
#                                        )    (  /(__)\ .-_)(  /(__)\                                      #
#                                       (_/\/\_)(__)(__)\____)(__)(__)                                     #
#                                                                                                          #
#                                                                                                          #
############################################################################################################
# HISTORIQUE                                                                                               #
#                                                                                                          #
# VERSION : 3.1.0 : DM : LAIG-DM-MAJA-2526-CNES : 9 avril 2018 : Montée de version de d'OTB 6.0            #
#                                                                                                          #
# FIN-HISTORIQUE                                                                                           #
#                                                                                                          #
# $Id$                                                                                                     #
#                                                                                                          #
############################################################################################################

set(MUPARSER_URL "https://github.com/beltoforion/muparser/archive/v2.2.5.tar.gz")
set(MUPARSER_URL_MD5 02dae671aa5ad955fdcbcd3fee313fb7)

ExternalProject_Add(MUPARSER
  URL "${MUPARSER_URL}"
  URL_MD5 ${MUPARSER_URL_MD5}
  PREFIX MUPARSER
  TMP_DIR      MUPARSER/tmp
  STAMP_DIR    MUPARSER/stamp
  SOURCE_DIR   MUPARSER/source
  BINARY_DIR   MUPARSER/build  
  INSTALL_DIR  ${SB_INSTALL_PREFIX}
  DOWNLOAD_DIR ${DOWNLOAD_DIR}
  DEPENDS ${MUPARSER_DEPENDS}
  CMAKE_COMMAND ${SB_CMAKE_COMMAND}
  CMAKE_CACHE_ARGS ${SB_CMAKE_CACHE_ARGS} ${DISABLE_CXX_WARNING_OPTION}
  PATCH_COMMAND ${CMAKE_COMMAND} -E copy
  ${CMAKE_SOURCE_DIR}/patches/MUPARSER/CMakeLists.txt ${CMAKE_BINARY_DIR}/MUPARSER/source/
  LOG_DOWNLOAD ${WRITE_LOG}
  LOG_CONFIGURE ${WRITE_LOG}
  LOG_BUILD ${WRITE_LOG}
  LOG_INSTALL ${WRITE_LOG}
  )
SUPERBUILD_PATCH_SOURCE(MUPARSER)


