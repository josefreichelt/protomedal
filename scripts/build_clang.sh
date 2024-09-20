#!/usr/bin/env bash
root_dir=$(basename $(pwd))
if [ $root_dir = "scripts" ]; then
    echo "In scripts directory, moving to root, prefer running this script from root directory."
    cd ..
    root_dir=$(basename $(pwd))
fi

source ./scripts/get_project_info.sh
platform=$(uname -o)
cmake_build() {
    echo "🔨 Building $project_name project with CMake..."
    if [[ "$platform" == "Windows" || "$platform" == "Msys" ]]; then
        if [ $1 ] && [ "$1" = "-r" ]; then
            cmake --build --preset clang_release_win
            exit $?
        else
            cmake --build --preset clang_debug_win
            exit $?
        fi
    else
        if [ $1 ] && [ "$1" = "-r" ]; then
            cmake --build --preset clang_release
            exit $?
        else
            cmake --build --preset clang_debug
            exit $?
        fi
    fi
}

cmake_build $1
./scripts/copy_assets.sh
