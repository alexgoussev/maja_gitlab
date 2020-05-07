# Client maintainer: rashad.kanavath@c-s.fr
cmake_minimum_required(VERSION 2.8)
set(ENV{LC_ALL} C)

# Custom function to remove a folder (divide & conquer ...)
function(remove_folder_recurse dir)
  file(GLOB content "${dir}/*")
  foreach(item ${content})
    if(IS_DIRECTORY ${item})
      execute_process(COMMAND ${CMAKE_COMMAND} -E remove_directory ${item}
	RESULT_VARIABLE ret)
      if(ret)
	remove_folder_recurse(${item})
      endif()
    else()
      execute_process(COMMAND ${CMAKE_COMMAND} -E remove -f ${item})
    endif()
  endforeach()
  execute_process(COMMAND ${CMAKE_COMMAND} -E remove_directory ${dir})
endfunction(remove_folder_recurse)

set(SYSTEM_HOSTNAME)
execute_process(COMMAND hostname -s
  OUTPUT_VARIABLE SYSTEM_HOSTNAME
  RESULT_VARIABLE hostname_rv)

string(STRIP "${SYSTEM_HOSTNAME}" SYSTEM_HOSTNAME)
if(NOT hostname_rv EQUAL 0 OR NOT SYSTEM_HOSTNAME)
  message(FATAL_ERROR "cannot find system hostname. error=${hostname_rv}")
endif()

if(EXISTS "$ENV{HOME}/.cdash_local.cmake")
  message(STATUS "including $ENV{HOME}/.cdash_local.cmake")
  include("$ENV{HOME}/.cdash_local.cmake")
endif()

if(DEFINED ENV{CTEST_DASHBOARD_ROOT})
  file(TO_CMAKE_PATH "$ENV{CTEST_DASHBOARD_ROOT}" CTEST_DASHBOARD_ROOT)
endif()

# Set CTEST_DASHBOARD_ROOT if not defined
if(NOT DEFINED CTEST_DASHBOARD_ROOT)
  set(CTEST_DASHBOARD_ROOT "$ENV{HOME}/dashboard")
else()
  file(TO_CMAKE_PATH "${CTEST_DASHBOARD_ROOT}" CTEST_DASHBOARD_ROOT)
endif()

get_filename_component(CTEST_DASHBOARD_ROOT
  "${CTEST_DASHBOARD_ROOT}" REALPATH)

# Default to a Release build.
if(NOT CTEST_BUILD_CONFIGURATION)
  set(CTEST_BUILD_CONFIGURATION Release)
endif()

if(NOT CTEST_CONFIGURATION_TYPE)
  set(CTEST_CONFIGURATION_TYPE ${CTEST_BUILD_CONFIGURATION})
endif()

# Select the model (Nightly, Experimental, Continuous).
set(dashboard_model Experimental)

if(DEFINED ENV{CTEST_CMAKE_GENERATOR})
  set(CTEST_CMAKE_GENERATOR "$ENV{CTEST_CMAKE_GENERATOR}")
endif()

if(DEFINED ENV{dashboard_maja_branch})
  set(dashboard_maja_branch "$ENV{dashboard_maja_branch}")
endif()

if(DEFINED ENV{DASHBOARD_SUPERBUILD})
  set(DASHBOARD_SUPERBUILD "$ENV{DASHBOARD_SUPERBUILD}")
endif()

if(WITH_PKG)
  set(DASHBOARD_SUPERBUILD FALSE)
endif()

set(build_testing ON)

function(print_summary)
# Print summary information.
foreach(v
    CTEST_SITE
    CTEST_BUILD_NAME
    CTEST_USE_LAUNCHERS
    CTEST_CMAKE_GENERATOR
    CTEST_CHECKOUT_COMMAND
    CTEST_DASHBOARD_ROOT
    CTEST_SOURCE_DIRECTORY
    CTEST_UPDATE_DIRECTORY
    CTEST_BINARY_DIRECTORY
    CTEST_INSTALL_DIRECTORY
    CTEST_BUILD_CONFIGURATION
    CTEST_BUILD_FLAGS
    CTEST_TEST_ARGS
    CTEST_DASHBOARD_TRACK
    CMAKE_MAKE_PROGRAM
    DASHBOARD_SUPERBUILD
    WITH_PKG
    DOWNLOAD_DIR
    CTEST_DROP_LOCATION
    dashboard_maja_branch
    dashboard_test_regex
    CONFIGURE_OPTIONS
    ENABLE_TV
    ENABLE_TVA
    ENABLE_TU
    TEST_CAMERA
    TEST_TYPE
    )
  set(vars "${vars}  ${v}=[${${v}}]\n")
endforeach(v)
message("ENV{PATH}=$ENV{PATH}")
message("Dashboard script configuration:\n${vars}\n")
endfunction() #print_summary

if(DEFINED ENV{CTEST_SITE})
  set(CTEST_SITE "$ENV{CTEST_SITE}")
endif()

if(NOT CTEST_SITE)
  message("CTEST_SITE is set to hostname -s which is '${SYSTEM_HOSTNAME}'")
  set(CTEST_SITE "${SYSTEM_HOSTNAME}")
endif()

#defaults
if(NOT DEFINED dashboard_maja_branch)
  set(dashboard_maja_branch develop)
endif()
string(STRIP "${dashboard_maja_branch}" dashboard_maja_branch)

set(CMAKE_BINARY_DIR "/tmp/dashboard/")
set(CMAKE_PLATFORM_INFO_DIR "/tmp/dashboard/")
include(CMakeDetermineCCompiler)
include(CMakeDetermineCXXCompiler)
unset(CMAKE_BINARY_DIR CACHE)
unset(CMAKE_PLATFORM_INFO_DIR CACHE)
# set build name
if(DEFINED ENV{CTEST_BUILD_NAME_PREFIX})
  set(CTEST_BUILD_NAME_PREFIX "$ENV{CTEST_BUILD_NAME_PREFIX}")
endif()
if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
set(compiler_info "${CMAKE_CXX_COMPILER_ID}-${CTEST_BUILD_CONFIGURATION}")
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
set(compiler_info "gcc-${CTEST_BUILD_CONFIGURATION}")
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Intel")
set(compiler_info "${CMAKE_CXX_COMPILER_ID}-${CTEST_BUILD_CONFIGURATION}")
endif()

if(NOT CTEST_BUILD_NAME)
  if(CTEST_BUILD_NAME_PREFIX)
    set(CTEST_BUILD_NAME "${CTEST_BUILD_NAME_PREFIX}-${compiler_info}")
  else()  
    set(CTEST_BUILD_NAME "${compiler_info}")
  endif()
endif()

#if(DASHBOARD_SUPERBUILD)
##TODO  set(CTEST_BUILD_NAME "${CTEST_BUILD_NAME}-SuperBuild")
#endif()

set(cam_option)
set(ENABLE_TV OFF)
if(DEFINED TEST_CAMERA)
  if(NOT DEFINED TEST_TYPE)
    set(TEST_TYPE "CHAIN")
  endif()
  set(ENABLE_TV ON)
  set(ENABLE_TVA OFF)
  set(ENABLE_TU OFF)
  string(STRIP ${TEST_CAMERA} TEST_CAMERA)
  set(dashboard_label "${TEST_CAMERA}_${TEST_TYPE}")  
  message(STATUS "test TV for '${TEST_CAMERA}_${TEST_TYPE}'")  
  set(cam_disabled "VENUS;SENTINEL2;SENTINEL2_TM;SENTINEL2_GPP;SENTINEL2_MUSCATE;FORMOSAT_MUSCATE_PROTO;SPOT4_MUSCATE_PROTO;LANDSAT_MUSCATE_PROTO;LANDSAT8_MUSCATE_PROTO;LANDSAT_MUSCATE;LANDSAT8_MUSCATE;LANDSAT8")
  if( ${TEST_CAMERA} STREQUAL "VENUS")
    set(cam_enabled "-DPLUGIN_VENUS:BOOL=ON")
    list(REMOVE_ITEM cam_disabled "VENUS")

  elseif( ${TEST_CAMERA} STREQUAL "SENTINEL2")
    set(cam_enabled "-DPLUGIN_SENTINEL2:BOOL=ON")
    list(REMOVE_ITEM cam_disabled "SENTINEL2")
    
  elseif( ${TEST_CAMERA} STREQUAL "SENTINEL2_TM")
    set(cam_enabled "-DPLUGIN_SENTINEL2_TM:BOOL=ON")
    list(REMOVE_ITEM cam_disabled "SENTINEL2_TM")

  elseif( ${TEST_CAMERA} STREQUAL "SENTINEL2_GPP")
    set(cam_enabled "-DPLUGIN_SENTINEL2_GPP:BOOL=ON")
    list(REMOVE_ITEM cam_disabled "SENTINEL2_GPP")

  elseif( ${TEST_CAMERA} STREQUAL "SENTINEL2_MUSCATE")
    set(cam_enabled "-DPLUGIN_SENTINEL2_MUSCATE:BOOL=ON")
    list(REMOVE_ITEM cam_disabled "SENTINEL2_MUSCATE")

  elseif( ${TEST_CAMERA} STREQUAL "FORMO")
    set(cam_enabled "-DPLUGIN_FORMOSAT_MUSCATE_PROTO:BOOL=ON")
    list(REMOVE_ITEM cam_disabled "FORMOSAT_MUSCATE_PROTO")

  elseif( ${TEST_CAMERA} STREQUAL "SPOT4")
    set(cam_enabled "-DPLUGIN_SPOT4_MUSCATE_PROTO:BOOL=ON")
    list(REMOVE_ITEM cam_disabled "SPOT4_MUSCATE_PROTO")

  elseif( ${TEST_CAMERA} STREQUAL "LANDSAT")
    set(cam_enabled "-DPLUGIN_LANDSAT_MUSCATE_PROTO:BOOL=ON")
    list(REMOVE_ITEM cam_disabled "LANDSAT_MUSCATE_PROTO")

  elseif( ${TEST_CAMERA} STREQUAL "LANDSAT8")
    set(cam_enabled "-DPLUGIN_LANDSAT8:BOOL=ON")
    list(REMOVE_ITEM cam_disabled "LANDSAT8")

  elseif( ${TEST_CAMERA} STREQUAL "LANDSAT8_MUSCATE")
    set(cam_enabled "-DPLUGIN_LANDSAT8_MUSCATE:BOOL=ON")
    list(REMOVE_ITEM cam_disabled "LANDSAT8_MUSCATE")

  elseif( ${TEST_CAMERA} STREQUAL "LANDSAT_MUSCATE")
    set(cam_enabled "-DPLUGIN_LANDSAT_MUSCATE:BOOL=ON")
    list(REMOVE_ITEM cam_disabled "LANDSAT_MUSCATE")

  elseif( ${TEST_CAMERA} STREQUAL "LANDSAT8_MUSCATE_PROTO")
    set(cam_enabled "-DPLUGIN_LANDSAT8_MUSCATE_PROTO:BOOL=ON")
    list(REMOVE_ITEM cam_disabled "LANDSAT8_MUSCATE_PROTO")
  elseif( ${TEST_CAMERA} STREQUAL "MIXING")
    set(cam_disabled)
    set(cam_enabled)    
    foreach(plugin "VENUS" "SENTINEL2" "SENTINEL2_GPP" "SENTINEL2_MUSCATE"
	"FORMOSAT_MUSCATE_PROTO" "SPOT4_MUSCATE_PROTO" "LANDSAT_MUSCATE_PROTO" 
	"LANDSAT8_MUSCATE_PROTO" "LANDSAT_MUSCATE" "LANDSAT8_MUSCATE" "LANDSAT8")
      list(APPEND cam_enabled "-DPLUGIN_${plugin}:BOOL=ON")
    endforeach()
    list(APPEND cam_enabled "-DTV_MIXING:BOOL=ON")
  endif() #if( ${TEST_CAMERA} STREQUAL "VENUS")
  set(cam_option ${cam_enabled})
  foreach(cam ${cam_disabled})
    list(APPEND cam_option "-DPLUGIN_${cam}:BOOL=OFF")
  endforeach()
endif() #if(DEFINED TEST_CAMERA)

if(ENABLE_TVA)
  set(dashboard_label "TVA")
  set(CTEST_DASHBOARD_TRACK TVA)
  set(ENABLE_TU OFF)
  set(ENABLE_TV OFF)
  set(TEST_CAMERA)
  set(cam_option)
  foreach(cam "VENUS" "SENTINEL2" "SENTINEL2_TM" "SENTINEL2_GPP" "SENTINEL2_MUSCATE"
      "FORMOSAT_MUSCATE_PROTO" "SPOT4_MUSCATE_PROTO" "LANDSAT_MUSCATE_PROTO" 
      "LANDSAT8_MUSCATE_PROTO" "LANDSAT_MUSCATE" "LANDSAT8_MUSCATE" "LANDSAT8")
    list(APPEND cam_option "-DPLUGIN_${cam}:BOOL=ON")
  endforeach()  
endif()

if(ENABLE_TU)
  message(STATUS "test TU")
  set(CTEST_DASHBOARD_TRACK TU)
  set(CTEST_BUILD_NAME "TU-${CTEST_BUILD_NAME}")
  set(ENABLE_TV OFF)
  set(ENABLE_TVA OFF)
  set(TEST_CAMERA)
  set(cam_option)
  foreach(cam "VENUS" "SENTINEL2" "SENTINEL2_TM" "SENTINEL2_GPP" "SENTINEL2_MUSCATE"
      "FORMOSAT_MUSCATE_PROTO" "SPOT4_MUSCATE_PROTO" "LANDSAT_MUSCATE_PROTO" 
      "LANDSAT8_MUSCATE_PROTO" "LANDSAT_MUSCATE" "LANDSAT8_MUSCATE" "LANDSAT8")
    list(APPEND cam_option "-DPLUGIN_${cam}:BOOL=ON")
  endforeach()
endif()

if(WITH_PKG)
  set(CTEST_BUILD_NAME "Package-${CTEST_BUILD_NAME}")
endif()

if(dashboard_label)
  set(CTEST_BUILD_NAME "${dashboard_label}-${CTEST_BUILD_NAME}")
endif()

if(dashboard_test_regex)
  set(CTEST_BUILD_NAME "${CTEST_BUILD_NAME}-${dashboard_test_regex}")
endif()

if(NOT "${dashboard_maja_branch}" MATCHES "^(master|develop)$")
  if(NOT (DASHBOARD_SUPERBUILD OR WITH_PKG))
    set(CTEST_BUILD_NAME "${dashboard_maja_branch}-${CTEST_BUILD_NAME}")
  endif()
endif()

##message(FATAL_ERROR "CTEST_BUILD_NAME=${CTEST_BUILD_NAME}")

#DEFAULT value for CTEST_CMAKE_GENERATOR
if(NOT CTEST_CMAKE_GENERATOR)
    set(CTEST_CMAKE_GENERATOR "Unix Makefiles")
endif() #if(NOT CTEST_CMAKE_GENERATOR)

include(ProcessorCount)
#set(process_count 0)
ProcessorCount(process_count)
if(NOT process_count EQUAL 0)
  set(CTEST_BUILD_FLAGS -j${process_count})
endif()

#ONLY to report in cmake_summary().
#maja now also check DOWNLOAD_DIR from ENV variable
if(DEFINED ENV{DOWNLOAD_DIR})
  set(DOWNLOAD_DIR "$ENV{DOWNLOAD_DIR}")
else()
  set(DOWNLOAD_DIR "/MAJA_SHARED_FOLDER/superbuild-archives")
endif()
get_filename_component(DOWNLOAD_DIR
  "${DOWNLOAD_DIR}" REALPATH)

# Choose CTest reporting mode.
if(NOT "${CTEST_CMAKE_GENERATOR}" MATCHES "Make")
  # Launchers work only with Makefile generators.
  set(CTEST_USE_LAUNCHERS OFF)
elseif(NOT DEFINED CTEST_USE_LAUNCHERS)
  # The setting is ignored by CTest < 2.8 so we need no version test.
  set(CTEST_USE_LAUNCHERS ON)
endif()

# Configure testing.
if(NOT DEFINED CTEST_TEST_CTEST)
  set(CTEST_TEST_CTEST 1)
endif()
if(NOT CTEST_TEST_TIMEOUT)
  set(CTEST_TEST_TIMEOUT 1500)
endif()

# Set CTEST_SOURCE_DIRECTORY if not defined
if(NOT DEFINED CTEST_SOURCE_DIRECTORY)
  if(DEFINED dashboard_source_name)
    set(CTEST_SOURCE_DIRECTORY ${CTEST_DASHBOARD_ROOT}/${dashboard_source_name})
  else()
    set(CTEST_SOURCE_DIRECTORY "/MAJA_SHARED_FOLDER/Logiciel/MAJA")
  endif()
endif()

# Select Git source to use.
if(NOT DEFINED dashboard_git_url)
  set(dashboard_git_url "https://mkanavat@thor.si.c-s.fr/git/maja")
endif()

if(NOT DEFINED dashboard_git_crlf)
  if(UNIX)
    set(dashboard_git_crlf false)
  else()
    set(dashboard_git_crlf true)
  endif()
endif()
#do not move below code. we must set 
# Set source directory to update right after we decide 
# on first CTEST_SOURCE_DIRECTORY which is actually the git repo dir
if(NOT DEFINED CTEST_UPDATE_DIRECTORY) #CTEST_UPDATE_DIRECTORY
  set(CTEST_UPDATE_DIRECTORY ${CTEST_SOURCE_DIRECTORY})
endif()

#!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
# CTEST_SOURCE_DIRECTORY is changed depending on your config
#!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! 
if(DASHBOARD_SUPERBUILD)
  set(CTEST_SOURCE_DIRECTORY ${CTEST_SOURCE_DIRECTORY}/SuperBuild)
elseif(WITH_PKG)
  set(CTEST_SOURCE_DIRECTORY ${CTEST_SOURCE_DIRECTORY}/Packaging)
endif()
#!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

# DEFAULT values for CTEST_BINARY_DIRECTORY if not defined
if(NOT DEFINED CTEST_BINARY_DIRECTORY)
  if(DEFINED dashboard_binary_name)
    set(CTEST_BINARY_DIRECTORY ${CTEST_DASHBOARD_ROOT}/${dashboard_binary_name})
  else()
    set(CTEST_BINARY_DIRECTORY ${CTEST_DASHBOARD_ROOT}/build)
  endif()
endif()

#other than superbuild, all uses maja/install_<arch>. That includes packaging
# DEFAULT values for CTEST_INSTALL_DIRECTORY if not defined
if(NOT DEFINED CTEST_INSTALL_DIRECTORY)
  if(DEFINED dashboard_install_name)
    set(CTEST_INSTALL_DIRECTORY ${CTEST_DASHBOARD_ROOT}/${dashboard_install_name})
  else()
    set(CTEST_INSTALL_DIRECTORY ${CTEST_DASHBOARD_ROOT}/local)
  endif()
endif()

#cannot move this from here.
if(WITH_PKG)
  if(NOT DEFINED SUPERBUILD_BINARY_DIR)
    set(SUPERBUILD_BINARY_DIR   ${CTEST_BINARY_DIRECTORY})
  endif()
  if(NOT DEFINED SUPERBUILD_INSTALL_DIR)
    set(SUPERBUILD_INSTALL_DIR  ${CTEST_INSTALL_DIRECTORY})
  endif()

  #reset binary directory here!
  set(CTEST_BINARY_DIRECTORY ${CTEST_DASHBOARD_ROOT}/pkg)
endif(WITH_PKG)

if(NOT DEFINED CTEST_DASHBOARD_TRACK)
  set(CTEST_DASHBOARD_TRACK Experimental)
endif()

set(CTEST_TEST_ARGS)
if(dashboard_label)
  set(CTEST_TEST_ARGS INCLUDE_LABEL ${dashboard_label})
endif()

if(dashboard_test_regex)
  set(CTEST_TEST_ARGS INCLUDE ${dashboard_test_regex})
endif()

if(DASHBOARD_SUPERBUILD)
  #if(dashboard_label)
  #set(CTEST_TEST_ARGS BUILD ${CTEST_BINARY_DIRECTORY} INCLUDE_LABEL ${dashboard_label})
  list(APPEND CTEST_TEST_ARGS BUILD ${CTEST_BINARY_DIRECTORY}/MAJA/build)
  #else()
   # set(CTEST_TEST_ARGS BUILD ${CTEST_BINARY_DIRECTORY}/MAJA/build)
    #set(CTEST_TEST_ARGS BUILD ${CTEST_BINARY_DIRECTORY}/MAJA/build INCLUDE AlgorithmsL2AOTChangeValueWithMaskFunctorTest2)
    #set(CTEST_BUILD_NAME "${compiler_info}-Release-TU_AlgorithmsL2AOTChangeValueWithMaskFunctorTest2")
# endif()
endif()

#-----------------------------------------------------------------------------
#TODO: 
#if(NOT process_count EQUAL 0)
  #set(CTEST_TEST_ARGS "${CTEST_TEST_ARGS} PARALLEL_LEVEL ${process_count}")
#endif()

# Send the main script as a note.
list(APPEND CTEST_NOTES_FILES "${CTEST_SCRIPT_DIRECTORY}/${CTEST_SCRIPT_NAME}")

if(DASHBOARD_SUPERBUILD)
  set(CTEST_NOTES_FILES
    "${CTEST_BINARY_DIRECTORY}/MAJA/stamp/MAJA-configure-out.log"
    "${CTEST_BINARY_DIRECTORY}/MAJA/stamp/MAJA-configure-err.log"
    "${CTEST_BINARY_DIRECTORY}/MAJA/build/CMakeCache.txt"
    )
  set(CTEST_ENVIRONMENT 
    "GDAL_DATA=${CTEST_INSTALL_DIRECTORY}/share/gdal
GEOTIFF_CSV=${CTEST_INSTALL_DIRECTORY}/share/epsg_csv
PROJ_LIB=${CTEST_INSTALL_DIRECTORY}/share/proj
PATH=${CTEST_INSTALL_DIRECTORY}/bin:$ENV{PATH}" 
)

else()
  set(CTEST_ENVIRONMENT 
    "GDAL_DATA=$ENV{GDAL_DATA}
GEOTIFF_CSV=$ENV{GEOTIFF_CSV}
PROJ_LIB=$ENV{PROJ_LIB}
PATH=${CTEST_INSTALL_DIRECTORY}/bin:$ENV{PATH}" 
)
endif()
  


#!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
#!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
# Creation of DEFAULT_CMAKE_CACHE starts here. That means all 
# common variables are set.

set(DEFAULT_CMAKE_CACHE	
"CMAKE_INSTALL_PREFIX:PATH=${CTEST_INSTALL_DIRECTORY}")

if(NOT DEFINED dashboard_build_shared)
  set(dashboard_build_shared ON)
endif()

set(DEFAULT_CMAKE_CACHE 
  "${DEFAULT_CMAKE_CACHE}
BUILD_SHARED_LIBS:BOOL=${dashboard_build_shared}

")

if(WITH_PKG)
  set(dashboard_cache "
CMAKE_INSTALL_PREFIX:PATH=${CTEST_INSTALL_DIRECTORY}
BUILD_TESTING:BOOL=ON
DOWNLOAD_DIR:PATH=${DOWNLOAD_DIR}
SUPERBUILD_BINARY_DIR:PATH=${SUPERBUILD_BINARY_DIR}
SUPERBUILD_INSTALL_DIR:PATH=${SUPERBUILD_INSTALL_DIR}
")

endif() #WITH_PKG

# CTest delayed initialization is broken, so we put the
# CTestConfig.cmake info here.
set(CTEST_PROJECT_NAME "MAJA")
set(CTEST_NIGHTLY_START_TIME "20:00:00 CEST")
set(CTEST_DROP_METHOD "http")
set(CTEST_DROP_SITE "172.26.46.217/cdash")
set(CTEST_DROP_LOCATION "submit.php?project=MAJA")
set(CTEST_DROP_SITE_CDASH TRUE)

#!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
#!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
#                              .
#                              .
#                              .
#                              .
#                              .
#    NO MORE SET/UPDATE OF VARIABLES GOES BELOW THIS BLOCK
#    IF YOU SEEM TO FIND ANY STRANGE SET/UPDATE CALLS BELOW, 
#    PLEASE FIX OR REPORT ON BUG MANTIS
#
#
# WE STARTING THE PROCESS.... CHECK, UPDATE, CONFIGURE, BUILD, INSTALL
#                              .
#                              .
#                              .
#                              .
#                              .
#!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
#!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

# Helper macro to write the initial cache.
macro(write_cache)
  set(cache_make_program "")
  file(WRITE ${CTEST_BINARY_DIRECTORY}/CMakeCache.txt "
SITE:STRING=${CTEST_SITE}
BUILDNAME:STRING=${CTEST_BUILD_NAME}
CTEST_USE_LAUNCHERS:BOOL=${CTEST_USE_LAUNCHERS}
CTEST_TEST_TIMEOUT:STRING=${CTEST_TEST_TIMEOUT}
CMAKE_BUILD_TYPE:STRING=${CTEST_BUILD_CONFIGURATION}
${dashboard_cache}
BUILD_TESTING:BOOL=${build_testing}
${DEFAULT_CMAKE_CACHE}
")
endmacro(write_cache)

if(EXISTS "${CTEST_BINARY_DIRECTORY}/MAJA/stamp/")
  execute_process(COMMAND ${CMAKE_COMMAND} 
    -E remove
    ${CTEST_BINARY_DIRECTORY}/MAJA/stamp/MAJA-configure
    ${CTEST_BINARY_DIRECTORY}/MAJA/stamp/MAJA-build
    ${CTEST_BINARY_DIRECTORY}/MAJA/stamp/MAJA-install
    ${CTEST_BINARY_DIRECTORY}/MAJA/stamp/MAJA-done
    WORKING_DIRECTORY ${CTEST_BINARY_DIRECTORY})
endif()

# # Start with a fresh build tree.
#RK: cleaning now done in dashboard.sh
#deleting build & install directory is response of
#ye who runs its

#create ctestconfig.cmake if not exists in source and binary directory
if(NOT EXISTS "${CTEST_BINARY_DIRECTORY}/CTestConfig.cmake" AND 
    NOT EXISTS "${CTEST_SOURCE_DIRECTORY}/CTestConfig.cmake" 
    )
  message("CTestConfig.cmake does not exists in CTEST_BINARY_DIRECTORY and CTEST_SOURCE_DIRECTORY. we create one now in CTEST_BINARY_DIRECTORY")
  file(WRITE "${CTEST_BINARY_DIRECTORY}/CTestConfig.cmake"
    "
set(CTEST_PROJECT_NAME \"${CTEST_PROJECT_NAME}\")
set(CTEST_NIGHTLY_START_TIME \"${CTEST_NIGHTLY_START_TIME}\")
set(CTEST_DROP_METHOD \"${CTEST_DROP_METHOD}\")
set(CTEST_DROP_SITE \"${CTEST_DROP_SITE}\")
set(CTEST_DROP_LOCATION \"/${CTEST_DROP_LOCATION}\")
set(CTEST_DROP_SITE_CDASH ${CTEST_DROP_SITE_CDASH})
")
endif()

if(COMMAND dashboard_hook_start)
  dashboard_hook_start()
endif()

print_summary()
#message(FATAL_ERROR "dry run..")
if(COMMAND dashboard_hook_init)
  dashboard_hook_init()
endif()

ctest_start(${dashboard_model} TRACK ${CTEST_DASHBOARD_TRACK})

# special setting for ctest_submit(), issue with CA checking
#set(CTEST_CURL_OPTIONS "CURLOPT_SSL_VERIFYPEER_OFF")
#set(CTEST_CURL_OPTIONS "CURLOPT_SSL_VERIFYHOST_OFF")
#if(dashboard_fresh OR NOT dashboard_continuous OR count GREATER 0)
set(CCONFIGURE_OPTIONS)
if(NOT dashboard_no_configure)
  if(NOT EXISTS "${CTEST_BINARY_DIRECTORY}/CMakeCache.txt")
    write_cache()
  endif()
   set(CONFIGURE_OPTIONS
     "-DENABLE_TV=${ENABLE_TV}"
     "-DENABLE_TVA=${ENABLE_TVA}"
     "-DENABLE_TU=${ENABLE_TU}"
     "-DTEST_TYPE=${TEST_TYPE}"
     "${cam_option}"
     )

  if(DASHBOARD_SUPERBUILD)
    set(CONFIGURE_OPTIONS
      ${CONFIGURE_OPTIONS}
      "-DDOWNLOAD_DIR=${DOWNLOAD_DIR}"
      )
  endif()
  message("Running ctest_configure() on ${CTEST_BINARY_DIRECTORY} with args=${CONFIGURE_OPTIONS}")
  if(CONFIGURE_OPTIONS)
    ctest_configure(BUILD "${CTEST_BINARY_DIRECTORY}" 
    OPTIONS "${CONFIGURE_OPTIONS}"
    RETURN_VALUE _configure_rv)
  else()
    ctest_configure(BUILD "${CTEST_BINARY_DIRECTORY}" 
    RETURN_VALUE _configure_rv)
  endif()
  ctest_read_custom_files(${CTEST_BINARY_DIRECTORY})

  if(NOT _configure_rv EQUAL 0)
    # Send error log in case of configure error"
    set(CTEST_NOTES_FILES
      "${CTEST_BINARY_DIRECTORY}/CMakeFiles/CMakeOutput.log"
      "${CTEST_BINARY_DIRECTORY}/CMakeFiles/CMakeCache.txt"
      "${CTEST_SCRIPT_DIRECTORY}/${CTEST_SCRIPT_NAME}"
      "${CMAKE_CURRENT_LIST_FILE}"
      )
  if(NOT dashboard_no_submit)
    ctest_submit()
  endif()
    return()
  endif()
endif() #NOT dashboard_no_configure

if(COMMAND dashboard_hook_build)
  dashboard_hook_build()
endif()

#must have install target.
#keep these two if condition here because it's used in next loop
if(WITH_PKG)
  set(dashboard_build_target install)
endif()

if(NOT dashboard_no_build)
  set(build_dir ${CTEST_BINARY_DIRECTORY})
  if(dashboard_build_target)
    message("building requested target ${dashboard_build_target} on ${build_dir}")
    ctest_build( BUILD "${build_dir}" 
      TARGET "${dashboard_build_target}"
      RETURN_VALUE _build_rv)
  else()
    ctest_build( BUILD "${build_dir}" RETURN_VALUE _build_rv)
  endif()
endif() #if(NOT dashboard_no_build)

if(NOT dashboard_no_test)
  if(COMMAND dashboard_hook_test)
    dashboard_hook_test()
  endif()
  ctest_test(${CTEST_TEST_ARGS})
endif()

if(dashboard_do_coverage)
  if(COMMAND dashboard_hook_coverage)
    dashboard_hook_coverage()
  endif()
  ctest_coverage()
endif()

if(dashboard_do_memcheck)
  if(COMMAND dashboard_hook_memcheck)
    dashboard_hook_memcheck()
  endif()
  ctest_memcheck()
endif()

if(COMMAND dashboard_hook_submit)
  dashboard_hook_submit()
endif()

if(NOT dashboard_no_submit)
  ctest_submit()
endif()

if(COMMAND dashboard_hook_end)
  dashboard_hook_end()
endif()

#if(WITH_PKG)
#  dashboard_copy_packages()
#endif()

