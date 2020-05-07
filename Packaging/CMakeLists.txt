#TODO
#
# Copyright (C) 2005-2017 Centre National d'Etudes Spatiales (CNES)
#
# This file is part of Orfeo Toolbox
#
#     https://www.orfeo-toolbox.org/
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#

cmake_minimum_required(VERSION 3.3.0)

project(MAJAPackaging)

include(CMakeParseArguments)
include(CMakeDetermineSystem)
include(GetPrerequisites)
include(CTest)
if(BUILD_TESTING)
  enable_testing()
endif()

#setting this variable prints a lot of debug information
set(PKG_DEBUG OFF)
#set( PKG_DEBUG 1)

set(CMAKE_BUILD_TYPE    Release)

option(WITH_VALIDATION  "Build validation package." OFF)

#user-defined variables and option
set(SUPERBUILD_BINARY_DIR  "" CACHE PATH "path to Maja build directory")
set(SUPERBUILD_INSTALL_DIR "" CACHE PATH "path to superbuild install directory")
set(DOWNLOAD_DIR "/MAJA_SHARED_FOLDER/superbuild-archives" CACHE PATH "path to superbuild download archives")

# find maja in binary dir: support Superbuild and standard builds
if(EXISTS "${SUPERBUILD_BINARY_DIR}/MAJA/build/bin/maja")
  set(MAJA_TEST_EXE_DIR ${SUPERBUILD_BINARY_DIR}/MAJA/build/bin)
elseif(EXISTS "${SUPERBUILD_BINARY_DIR}/bin/maja")
  set(MAJA_TEST_EXE_DIR ${SUPERBUILD_BINARY_DIR}/bin)
endif()
if(NOT EXISTS "${MAJA_TEST_EXE_DIR}/maja")
  message(FATAL_ERROR "${MAJA_TEST_EXE_DIR}/maja not found")
endif()

if(PROJECT_NAME STREQUAL "MAJAPackaging")
  if(EXISTS "${SUPERBUILD_INSTALL_DIR}/maja/")
    file(GLOB maja_install_dirs "${SUPERBUILD_INSTALL_DIR}/maja/*.*")
    set(dirnames)
    #message("maja_install_dirs=${maja_install_dirs}")
    foreach(maja_install_dir ${maja_install_dirs})
      if(IS_DIRECTORY "${maja_install_dir}")
	get_filename_component(maja_install_dirname "${maja_install_dir}" NAME)
	list(APPEND dirnames ${maja_install_dirname})
      endif()
    endforeach()
    # list(APPEND dirnames "3.3.0")
    # list(APPEND dirnames "4.1.0")
    list(SORT dirnames)
    list(REVERSE dirnames)
    list(GET dirnames 0 latest_release)
    #message(FATAL_ERROR "latest_release=${latest_release}")
    set(SUPERBUILD_INSTALL_DIR "${SUPERBUILD_INSTALL_DIR}/maja/${latest_release}")
  endif() #if(EXISTS "${SUPERBUILD_INSTALL_DIR}/local/")
endif()

find_program(FILE_COMMAND NAMES  "file")
find_program(READLINK NAMES "readlink")

set(CMAKE_INSTALL_PREFIX "${SUPERBUILD_INSTALL_DIR}")

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR})
set(camera_list)
include(${CMAKE_SOURCE_DIR}/../CMakeConfig/CommonCmakeOptions.cmake)

if(NOT EXISTS "${SUPERBUILD_INSTALL_DIR}/bin/maja")
  message(FATAL_ERROR "${SUPERBUILD_INSTALL_DIR}/bin/maja not found.")
endif()

file(STRINGS "${SUPERBUILD_BINARY_DIR}/CMakeCache.txt"
  enable_camera_vars
  REGEX "PLUGIN_(VENUS|SPOT4|FORMOSAT_MUSCATE_PROTO|LANDSAT8|LANDSAT8_MUSCATE|LANDSAT8_MUSCATE_PROTO|LANDSAT_MUSCATE|LANDSAT_MUSCATE_PROTO|SENTINEL2|SENTINEL2_GPP|SENTINEL2_MUSCATE).BOOL.")
foreach(camera_option ${enable_camera_vars})
  if(${camera_option} MATCHES "^PLUGIN_*.*BOOL=ON$")
    string(REPLACE "PLUGIN_" "" camera_option "${camera_option}")
    string(REPLACE ":BOOL=ON" "" camera_option "${camera_option}")
    list(APPEND camera_list "${camera_option}")
  endif()
endforeach()
string(REPLACE ";" " " camera_list "${camera_list}")
message(STATUS "specrtal camera enabled:\n '${camera_list}'")

set(PKG_MAJA_VERSION_STRING ${MAJA_VERSION})

set(PACKAGE_LONG_NAME MAJA)
set(PACKAGE_NAME MAJA)

# This directory is important.
# We stage/keep files that goes into final package in this directory
set(PKG_STAGE_DIR ${PACKAGE_NAME}-${PKG_MAJA_VERSION_STRING})
if(WITH_VALIDATION)
  set(PKG_STAGE_DIR ${PACKAGE_NAME}-${PKG_MAJA_VERSION_STRING}-VALIDATION)
endif()

# try to detect patchelf
find_program(PATCHELF_PROGRAM NAMES patchelf)
if(NOT PATCHELF_PROGRAM)
  set(PATCHELF_PROGRAM "${CMAKE_BINARY_DIR}/PATCHELF/src/patchelf/src/patchelf")
  include(External_patchelf)
endif()

include(PackageGlobals)

# Note that MANY or ALL of function use global variables set in this CMakeLists.txt
# The order in which the functions in these "included" files are called is only important.
# We tried not to share variables which are created inside functions or macro. In such cases,
# function return the value. 

include(setif_value_in_list)
include(get_variables_ending_with)
include(clear_cmakecache_variables)
include(check_cmake_variables)
include(configure_loader)
include(search_library)
include(prepare_search_dirs)
include(prepare_file_list)
include(process_file_recurse)
include(install_without_message)
include(install_rule)
include(isfile_symlink)
include(update_make_symlinks_script)
include(detect_using_file_command)
include(cleanup_package)
include(install_orchestrator)
include(install_python_bindings)
include(install_share_dirs)
include(installer_files)
include(validation_files)
include(create_package)

configure_loader(LOADER_PROGRAM LOADER_ARGS LOADER_REGEX)
set(PACKAGE_OUTPUT_FILE "${CMAKE_CURRENT_BINARY_DIR}/${PKG_STAGE_DIR}.run")

check_cmake_variables()

cleanup_package()

if(WITH_VALIDATION)
  update_make_symlinks_script(
    "bin/vnsInstallDataCxx-${MAJA_VERSION}"
    "bin/vnsInstallDataCxx")
endif()

#remove all *_USED|*_RESOLVED variables from CMakeCache.txt
clear_cmakecache_variables()

set(PKG_SEARCHDIRS)
prepare_search_dirs(PKG_SEARCHDIRS)

set(PKG_PEFILES)
prepare_file_list(PKG_PEFILES)
foreach(pfile ${PKG_PEFILES})
  if(NOT EXISTS ${pfile})
    message(FATAL_ERROR "${pfile} not found")
  endif()
  message(${pfile})
  process_file_recurse(${pfile})
endforeach()

install_python_bindings()

install_orchestrator()

install_share_dirs()

install(DIRECTORY "${SUPERBUILD_INSTALL_DIR}/etc" DESTINATION ${PKG_STAGE_DIR})

installer_files()

if(WITH_VALIDATION)
  validation_files()
endif()

create_package()
