cmake_minimum_required(VERSION 2.8.11)
project(MAJAValidation2)

set(BUILD_TESTING ON)
include(CTest)
include(${CMAKE_ROOT}/Modules/Dart.cmake)

set(CTEST_PROJECT_NAME "MAJA")
set(CTEST_NIGHTLY_START_TIME "20:00:00 CEST")

set(CTEST_DROP_METHOD "http")
set(CTEST_DROP_SITE "172.26.46.217/cdash")
set(CTEST_DROP_LOCATION "/submit.php?project=MAJA")
set(CTEST_DROP_SITE_CDASH TRUE)

set(CMAKE_INSTALL_PREFIX "OUT_DIR")
set(MAJA_BINARY_DIR "OUT_DIR")

include(${CMAKE_CURRENT_LIST_DIR}/tv_tva_tests/vnsMAJAGlobalConfiguration.cmake)
set(LAUNCHER_TEST_NAME vnsTestMainLauncher.sh)
set(DUMMY_PROGRAM_NAME vnsDummyProgram.sh)
set(STAND_ALONE_PROCESSING_NAME maja)
add_subdirectory(tv_tva_tests)
set(MAJA_TEST_OUTPUT_ROOT "")

foreach(v
    CMAKE_HOST_SYSTEM_NAME
    MAJADATA_SOURCE_DIR
    CMAKE_INSTALL_PREFIX
    MAJA_BINARY_DIR
    MAJA_TEST_OUTPUT_ROOT
    ENABLE_TV
    ENABLE_TVA
    )
  message(STATUS "${v}=[${${v}}]")
endforeach(v)

