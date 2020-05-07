#!/bin/sh -x

INSTALL_DIR=$1
CMAKE_BINARY_DIR=$2
PATCHELF_EXE=$CMAKE_BINARY_DIR/PATCHELF/src/patchelf/src/patchelf

"$PATCHELF_EXE" "--set-rpath" "$INSTALL_DIR/lib" "$INSTALL_DIR/bin/python3.7"
"$PATCHELF_EXE" "--set-rpath" "$INSTALL_DIR/lib" "$INSTALL_DIR/bin/python3.7m"
"chmod" "u+w" "$INSTALL_DIR/lib/libpython3.so"
"chmod" "u+w" "$INSTALL_DIR/lib/libpython3.7m.so.1.0"

pylibs=$(find "$INSTALL_DIR/lib/" -type f -name libpython3*.so*)
binaries=$(find "$INSTALL_DIR/lib/python3.7/lib-dynload" -type f -exec file {} \; | grep -i elf| grep -i dynamically | cut -f1 -d':')
for bfile in $binaries $pylibs; do
    if [ -f "$bfile" ]; then
        "$PATCHELF_EXE" "--set-rpath" "$INSTALL_DIR/lib" "$bfile"
    fi
done

rm -rf $INSTALL_DIR/lib/python3.7/test
