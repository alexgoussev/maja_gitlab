option(BUILD_DOCUMENTATION
  "Build doxygen-based code documentation." OFF)

mark_as_advanced(BUILD_DOCUMENTATION)

# -------------------------------------------------------------
#
# Generate Doxygen configuration file in all configuration file
#
if( ${DOXYGEN_DOT_FOUND} )
  set( ITK_HAVE_DOT "YES" )
else()
  set( ITK_HAVE_DOT "NO" )
endif()



if (BUILD_DOCUMENTATION)
   set( DOXYGEN_TEST_DIR ${MACCS_SOURCE_DIR}/Doxygen )
   configure_file(${MACCS_SOURCE_DIR}/Doxygen/Doxyfile.config.in
	            ${MAJA_BINARY_DIR}/Doxygen/Doxyfile.config)

   add_custom_target(Documentation ALL
    COMMAND doxygen ${MAJA_BINARY_DIR}/Doxygen/Doxyfile.config 
    MAIN_DEPENDENCY ${MAJA_BINARY_DIR}/Doxygen/Doxyfile.config
    WORKING_DIRECTORY ${MAJA_BINARY_DIR}/Doxygen
    )
endif (BUILD_DOCUMENTATION)
