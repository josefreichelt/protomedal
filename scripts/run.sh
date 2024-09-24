#!/usr/bin/env bash
root_dir=$(basename $(pwd))
if [ $root_dir = "scripts" ]; then
    echo "In scripts directory, moving to root, prefer running this script from root directory."
    cd ..
    root_dir=$(basename $(pwd))
fi

source ./scripts/get_project_info.sh

./scripts/build_clang.sh
res=$?
if [ $res -eq 0 ]
then
    echo "💿 Starting $project_name project..."
    ./bin/$project_name
fi
