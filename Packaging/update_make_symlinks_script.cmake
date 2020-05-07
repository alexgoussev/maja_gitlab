# target_path and link_path are relative to OUT_DIR

function(update_make_symlinks_script target_path link_path)
  if(target_path)
    file(APPEND
      ${CMAKE_BINARY_DIR}/make_symlinks
      "ln -sf \"$OUT_DIR/${target_path}\" \"$OUT_DIR/${link_path}\"\n")
  endif()
endfunction()
