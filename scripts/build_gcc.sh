#!/usr/bin/env bash
root_dir=$(basename $(pwd))
if [ $root_dir = "scripts" ]; then
    echo "In scripts directory, moving to root, prefer running this script from root directory."
    cd ..
    root_dir=$(basename $(pwd))
fi

source ./scripts/get_project_info.sh

cmake_build() {
    echo "🔨 Building $project_name project with CMake..."
    if  [ $1 ] && [ "$1" = "-r" ]; then
        cmake --build --preset gcc_release
        exit $?
    else
        cmake --build --preset gcc_debug
        exit $?
    fi
}

cmake_build $1
