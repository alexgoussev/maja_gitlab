function(validation_files)
  # MAJAPackaging_SOURCE_DIR is available because we have
  # project(MAJAPackaging) in CMakeLists.txt
  get_filename_component(maja_src_dir ${MAJAPackaging_SOURCE_DIR} PATH)
  #copy src/tv_tva_tests to STAGE_DIR
  install(DIRECTORY
    ${maja_src_dir}/tv_tva_tests
    DESTINATION ${PKG_STAGE_DIR})

  install(FILES
    ${maja_src_dir}/CMakeConfig/CommonCmakeOptions.cmake
    ${maja_src_dir}/CMakeConfig/MAJAConfigurationSetting.cmake
    ${maja_src_dir}/CMakeConfig/vnsMAJAGlobalConfiguration.cmake
    DESTINATION ${PKG_STAGE_DIR}/tv_tva_tests)
  
  #copy maja validation to STAGE_DIR/
  install(DIRECTORY
    "${MAJA_VALIDATION_SRC_DIR}"
    DESTINATION ${PKG_STAGE_DIR}
    PATTERN ".git" EXCLUDE)
  
  install(FILES
    Files/CMakeLists.txt
    DESTINATION ${PKG_STAGE_DIR})
endfunction()
