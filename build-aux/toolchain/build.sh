#!/bin/bash
# Build the toolchain

# Stop this script if error occur
set -e

# Check dependency is install
source ./build-aux/toolchain/build/dependencies.sh

# Load the configuration file
source ./build-aux/toolchain/config.sh

# Create the toolchain install directory
if [ ! -d  $INSTALL_DIRECTORY ];  then 
    mkdir $INSTALL_DIRECTORY
fi

source ./build-aux/toolchain/build/gcc.sh

if [ $COMPILER = "llvm" ]; then 
    source ./build-aux/toolchain/build/llvm.sh
fi

# Build Grub
source ./build-aux/toolchain/build/grub.sh

# Build Xorrsiso
source ./build-aux/toolchain/build/xorriso.sh

echo "[v] - Toolchain build complete".