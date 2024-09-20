#!/usr/bin/env bash
root_dir=$(basename $(pwd))
if [ $root_dir = "scripts" ]; then
    echo "In scripts directory, moving to root, prefer running this script from root directory."
    cd ..
    root_dir=$(basename $(pwd))
fi

source ./scripts/get_project_info.sh


if [ ! -d "$asset_dir" ]; then
    exit 1
fi

echo "📦 Copying assets to bin directory..."
asset_dir="assets"

mkdir -p ./bin/assets
platform=$(uname -o)
# Create the archive
if [[ "$platform" == "Windows" || "$platform" == "Msys" ]]; then
    cp -ruv ./assets/* ./bin/assets/
else
    rsync -rutpp --progress ./assets/ ./bin/assets/
fi
