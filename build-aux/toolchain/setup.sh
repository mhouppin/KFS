#!/bin/bash
# Setup the toolchain using the available system package manager

# Stop this script if error occur
set -e

source ./build-aux/toolchain/config.sh

# Get operating system name
OS=$(uname);

# Install linux dependency
if [ "${OS}" = "Linux" ];
then
    source ./build-aux/toolchain/setup/linux.sh
fi

# Install macos dependency
if [ "${OS}" = "Darwin" ];
then
    source ./build-aux/toolchain/setup/macos.sh
fi

echo "[x] - Unsuported operating system by toolschain installer."
exit 1