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

set(GDAL_URL "http://download.osgeo.org/gdal/2.2.1/gdal-2.2.1.tar.gz")
set(GDAL_URL_MD5 785acf2b0cbf9d56d37c9044d0ee2505)
set(GDAL_DEPENDS ZLIB EXPAT PNG PROJ JPEG TIFF GEOTIFF SQLITE OPENJPEG GEOS HDF4 NETCDF PYTHON SWIG)

set(GDAL_AUTOCONF_BUILD 1)
build_projects(GDAL_DEPENDS)

set(GDAL_CONFIG_ARGS
  ${SB_CONFIGURE_ARGS}
  --with-libkml=no
  --with-freexl=no
  --with-liblzma=no
  --with-curl=no
  --with-cfitsio=no
  --with-dods-root=no
  --with-ecw=no
  --with-epsilon=no
  --with-fme=no
  --with-gif=no
  --with-grass=no
  --with-gta=no
  --with-idb=no
  --with-ingres=no
  --with-jp2mrsid=no
  --with-kakadu=no
  --with-jasper=no
  --with-libgrass=no
  --with-mrsid=no
  --with-msg=no
  --with-mysql=no
  --with-oci=no
  --with-odbc=no
  --with-ogdi=no
  --with-pam=no
  --with-pcidsk=yes
  --with-pcraster=no
  --with-pcre=no
  --with-perl=no
  --with-php=no
  --with-python=no
  --with-sde=no
  --with-spatialite=no
  --with-xerces=no
  --with-pg=no
  --with-webp=no
  --with-threads=yes
  --with-hdf5=no
  --with-grib=no
  --with-python=${SB_INSTALL_PREFIX}/bin/python3)

add_configure_option(GDAL TIFF      --with-libtiff)
add_configure_option(GDAL GEOTIFF   --with-geotiff)
add_configure_option(GDAL PNG       --with-png)
add_configure_option(GDAL JPEG      --with-jpeg)
add_configure_option(GDAL OPENJPEG  --with-openjpeg)
add_configure_option(GDAL SQLITE    --with-sqlite3)
add_configure_option(GDAL ZLIB      --with-libz)
add_configure_option(GDAL EXPAT     --with-expat)
add_configure_option(GDAL GEOS      --with-geos "${SB_INSTALL_PREFIX}/bin/geos-config")
add_configure_option(GDAL NETCDF    --with-netcdf)
add_configure_option(GDAL HDF4      --with-hdf4)



set(GDAL_BUILD_COMMAND "env" "LD_LIBRARY_PATH=${SB_INSTALL_PREFIX}/lib/" make )
set(GDAL_INSTALL_COMMAND "env" "LD_LIBRARY_PATH=${SB_INSTALL_PREFIX}/lib/" make install)

ExternalProject_Add(GDAL
  PREFIX GDAL
  URL "${GDAL_URL}"
  URL_MD5 ${GDAL_URL_MD5}
  TMP_DIR      GDAL/tmp
  STAMP_DIR    GDAL/stamp
  SOURCE_DIR   GDAL/source
  #BINARY_DIR   GDAL/build #uncomment for BUILD_IN_SOURCE 1
  INSTALL_DIR ${SB_INSTALL_PREFIX}
  DOWNLOAD_DIR ${DOWNLOAD_DIR}
  DEPENDS ${GDAL_DEPENDS}
  CONFIGURE_COMMAND "env" "LD_LIBRARY_PATH=${SB_INSTALL_PREFIX}/lib/" "${SB_ENV_CONFIGURE_CMD};${CMAKE_BINARY_DIR}/GDAL/source/configure"
  ${GDAL_CONFIG_ARGS}
  BUILD_IN_SOURCE 1
  LOG_DOWNLOAD ${WRITE_LOG}
  LOG_CONFIGURE ${WRITE_LOG}
  LOG_INSTALL ${WRITE_LOG}
  )
 


SUPERBUILD_PATCH_SOURCE(GDAL)
