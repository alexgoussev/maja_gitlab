#set(dashboard_no_configure 1)
#set(dashboard_no_build 1)
#set(dashboard_no_test 1)
#set(dashboard_no_submit 1)

#set(CTEST_BUILD_CONFIGURATION Debug)
#set(dashboard_test_regex AlgorithmsCheckingTool)
#set(dashboard_test_regex dataManagerVenusL2ImageFilenamesProviderVenus)
#set(dashboard_test_regex AlgorithmsL3CirrusFlagRainFlagAndSumWeightTest)
#set(dashboard_test_regex AlgorithmsL3CloudWeightImageFilterTest_CESBIO)
set(DASHBOARD_SUPERBUILD 1)

set(dashboard_cache 
"
#all values are default.

")

include(${CMAKE_CURRENT_LIST_DIR}/windows_common.cmake)

