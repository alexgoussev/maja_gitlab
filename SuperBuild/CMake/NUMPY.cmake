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
# to get the original .whl just change .tar.gz to  .whl in the following URL
set(NUMPY_URL "https://files.pythonhosted.org/packages/fc/d1/45be1144b03b6b1e24f9a924f23f66b4ad030d834ad31fb9e5581bd328af/numpy-1.16.4-cp37-cp37m-manylinux1_x86_64.whl")
set(NUMPY_URL_MD5 e98fc6a8d90ff7ed26d0ed7faad3aa8d)
set(NUMPY_DEPENDS PYTHON)
set(NUMPY_AUTOCONF_BUILD 1)
build_projects(NUMPY_DEPENDS)

set(NUMPY_SB_SRC ${CMAKE_BINARY_DIR}/NUMPY/source/)

ExternalProject_Add(NUMPY
  PREFIX NUMPY
  URL "${NUMPY_URL}"
  URL_MD5 ${NUMPY_URL_MD5}
  TMP_DIR      NUMPY/tmp
  STAMP_DIR    NUMPY/stamp
  SOURCE_DIR   NUMPY/source
  INSTALL_DIR ${SB_INSTALL_PREFIX}
  DEPENDS ${NUMPY_DEPENDS}
  DOWNLOAD_DIR ${DOWNLOAD_DIR}
  DOWNLOAD_NO_EXTRACT ON
  CONFIGURE_COMMAND ${SB_INSTALL_PREFIX}/bin/pip3.7 -v --disable-pip-version-check --no-cache-dir --no-color
    install <DOWNLOADED_FILE>
  BUILD_COMMAND ""
  INSTALL_COMMAND ""
  LOG_DOWNLOAD ${WRITE_LOG}
  LOG_CONFIGURE ${WRITE_LOG}
  LOG_BUILD ${WRITE_LOG}
  LOG_INSTALL ${WRITE_LOG}
  )

SUPERBUILD_PATCH_SOURCE(NUMPY)
