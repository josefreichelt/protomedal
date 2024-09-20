#!/bin/bash
root_dir=$(basename $(pwd))
if [ $root_dir = "scripts" ]; then
    echo "In scripts directory, moving to root, prefer running this script from root directory."
    cd ..
    root_dir=$(basename $(pwd))
fi

source ./scripts/get_project_info.sh

platform=$(uname -o)
# Create a timestamped archive file with the version number
ARCHIVE_NAME="${project_name}_${project_version}_${platform}_$(date +%Y-%m-%d).zip"

echo "Creating archive: ${ARCHIVE_NAME}"

mkdir -p dist/

# Create the archive
if [[ "$platform" == "Windows" || "$platform" == "Msys" ]]; then
    cd bin
    7z a ${ARCHIVE_NAME} *
    mv ${ARCHIVE_NAME} ../dist/
else
    cd bin
    zip -r "../dist/${ARCHIVE_NAME}" .
fi

echo "Archive created: ${ARCHIVE_NAME}"
