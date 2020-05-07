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

# checking for supported version of jpeg library... configure: error:
#   jpeg library version 7 and higher is not currently supported.
#   Please use version 6b, obtainable at:
#     http://www.hdfgroup.org/ftp/lib-external/jpeg/src/jpegsrc.v6b.tar.gz
#   For further questions, please contact help@hdfgroup.org.
# make[2]: *** [deps/Stamp/HDF4/HDF4-configure] Error 127

#  URL "http://downloads.sourceforge.net/project/libjpeg-turbo/1.4.1/libjpeg-turbo-1.4.1.tar.gz"
#  URL_MD5 b1f6b84859a16b8ebdcda951fa07c3f2

set(JPEG_URL "http://www.ijg.org/files/jpegsrc.v6b.tar.gz")
set(JPEG_URL_MD5 dbd5f3b47ed13132f04c685d608a7547)
set(JPEG_DEPENDS ZLIB)

ExternalProject_Add(JPEG
  URL "${JPEG_URL}"
  URL_MD5 ${JPEG_URL_MD5}
  PREFIX JPEG
  TMP_DIR      JPEG/tmp
  STAMP_DIR    JPEG/stamp
  SOURCE_DIR   JPEG/source
  BINARY_DIR   JPEG/build
  INSTALL_DIR ${SB_INSTALL_PREFIX}
  DOWNLOAD_DIR ${DOWNLOAD_DIR}
  DEPENDS ${JPEG_DEPENDS}
  CONFIGURE_COMMAND "${SB_ENV_CONFIGURE_CMD};${CMAKE_BINARY_DIR}/JPEG/source/configure"
  ${SB_CONFIGURE_ARGS}
  INSTALL_COMMAND ${CMAKE_MAKE_PROGRAM} install-lib
  LOG_DOWNLOAD ${WRITE_LOG}
  LOG_CONFIGURE ${WRITE_LOG}
  LOG_BUILD ${WRITE_LOG}
  LOG_INSTALL ${WRITE_LOG}
  )
SUPERBUILD_PATCH_SOURCE(JPEG)
