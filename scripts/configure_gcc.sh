#!/usr/bin/env bash
root_dir=$(basename $(pwd))
if [ $root_dir = "scripts" ]; then
    echo "In scripts directory, moving to root, prefer running this script from root directory."
    cd ..
    root_dir=$(basename $(pwd))
fi

source ./scripts/get_project_info.sh

cmake_configure() {
    echo "⚙️ Configuring $project_name project with CMake..."
    if [ $1 ] && [ "$1" = "-r" ]; then
        cmake --preset gcc_release
        exit $?
    else
        cmake --preset gcc_debug
        exit $?
    fi
}

cmake_configure $1
