#!/bin/sh
# Example usage:
# run TU, TVA, TV of  (SPOT4_CHAIN, SPOT4_COMP_ASCII, SPOT4_COMP_IMAGE)
#   tu= 1 tva=1 camera_list="SPOT4" /MAJA_SHARED_FOLDER/Logiciel/MAJA/cdash/dashboard.sh

# run TU, TV of (SPOT4_CHAIN, SPOT4_COMP_ASCII, SPOT4_COMP_IMAGE)
#   tu=1 camera_list="SPOT4" /MAJA_SHARED_FOLDER/Logiciel/MAJA/cdash/dashboard.sh

# run only TU and TVA
#   tu=1 tva=1 /MAJA_SHARED_FOLDER/Logiciel/MAJA/cdash/dashboard.sh

# run only TVA
#   tva=1 /MAJA_SHARED_FOLDER/Logiciel/MAJA/cdash/dashboard.sh

# run only TU
#   tu=1 /MAJA_SHARED_FOLDER/Logiciel/MAJA/cdash/dashboard.sh

# run tva with ctest_verbose
#   ctest_verbose=1 /MAJA_SHARED_FOLDER/Logiciel/MAJA/cdash/dashboard.sh

# run tu=1 after cleaning build and install directory. (a.k.a fresh build)
#   clean=1 tu=1 /MAJA_SHARED_FOLDER/Logiciel/MAJA/cdash/dashboard.sh

# run nothing
#   /MAJA_SHARED_FOLDER/Logiciel/MAJA/cdash/dashboard.sh

export LC_ALL="C"
export LANG="en_US.UTF-8"
# find current dir (resolve symlinks)
CUR_DIR=$(readlink -f "$(dirname "$0")")

DASHBOARD_CMAKE_FILE=$CUR_DIR/dashboard.cmake
export PATH=/usr/kerberos/bin:/usr/local/bin:/bin:/usr/bin:$HOME/bin

if [ ! -f "$DASHBOARD_CMAKE_FILE" ]; then
    echo "'$DASHBOARD_CMAKE_FILE' does not exists. Make sure you have checkout out MAJA sources"
    echo "cd; git clone https://https://maja-root_tech@thor.si.c-s.fr/git/maja"
    return -1;
fi

#TEST: force fresh install for one day
rm -rf $HOME/dashboard/build/*
rm -rf $HOME/dashboard/local/*

if [ "x$clean" = "x1" ]; then
    echo "cleaning $HOME/dashboard/{build,local} because clean=$clean"
    rm -rf $HOME/dashboard/build/*
    rm -rf $HOME/dashboard/local/*
else

    if [ -f "$HOME/dashboard/build/MAJA/build/install_manifest.txt" ]; then
	echo "Uninstalling MAJA from $HOME/dashboard/local/"
	make uninstall
    fi
    if [ -d "$HOME/dashboard/build/MAJA/" ]; then
	echo "Deleting $HOME/dashboard/build/MAJA/"
	cd $HOME && rm -rf $HOME/dashboard/build/MAJA/*
    fi
fi

if [ "x$ctest_verbose" = "x1" ]; then
    ctest_verbose="-V"
else
    ctest_verbose="-VV"
fi
echo "ctest_verbose=$ctest_verbose"

if [ "x$tu" = "x1" ]; then
    echo "Running TU because tu='$tu'. output is logged written to $HOME/logs/tu.log"
    echo "View output using: tail -f $HOME/logs/tu.log"
    ctest "$ctest_verbose" -S "$DASHBOARD_CMAKE_FILE" -DENABLE_TU=ON > "$HOME/logs/tu.log" 2>&1
else
    echo "not running TU because tu='$tu'"
fi

if [ "x$tva" = "x1" ]; then
    echo "Running TVA because tu='$tva'. output is logged written to $HOME/logs/tva.log"
    echo "View output using: tail -f $HOME/logs/tva.log"
    ctest "$ctest_verbose" -S "$DASHBOARD_CMAKE_FILE" -DENABLE_TVA=ON > "$HOME/logs/tva.log" 2>&1
else
    echo "not running TVA because tva='$tva'"
fi

for camera in ${camera_list}; do
    echo "Testing '${camera}' CHAIN COMP_IMAGE COMP_ASCII"
    for test_type in CHAIN COMP_IMAGE COMP_ASCII; do
	echo "Running TV ${camera}_${test_type} because camera_list='${camera_list}'."
	echo "output is logged written to $HOME/logs/${camera}_${test_type}.log"
	echo "View output using: tail -f  $HOME/logs/${camera}_${test_type}.log"
	ctest "$ctest_verbose" -S ${DASHBOARD_CMAKE_FILE} -DTEST_CAMERA=${camera} -DTEST_TYPE=${test_type} > "$HOME/logs/${camera}_${test_type}.log" 2>&1
    done
done
