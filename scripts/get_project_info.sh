#!/usr/bin/env bash
root_dir=$(basename $(pwd))
if [ $root_dir = "scripts" ]; then
    echo "In scripts directory, moving to root, prefer running this script from root directory."
    cd ..
    root_dir=$(basename $(pwd))
fi


project_name_line=$(grep CMakeLists.txt -e "CLIENT_TARGET_NAME\s\"")
project_name=$(cut -d "\"" -f 2 <<< $project_name_line)
project_version_line=$(grep CMakeLists.txt -e "CLIENT_PROJECT_VERSION\s\"")
project_version=$(cut -d "\"" -f 2 <<< $project_version_line)
