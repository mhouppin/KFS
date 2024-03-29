
#Set default values
if [ -z "$ARCH" ];
then
    ARCH="i386"
fi

if [ -z "$TARGET" ];
then
    TARGET="$ARCH-elf"
fi

if [ -z "$COMPILER" ];
then
    COMPILER="gcc"
fi

if [ -z "$BUILD_THREADS" ];
then
    BUILD_THREADS=$(nproc --all --ignore=1)
fi

# Build directory
TOOLCHAIN_DIRECTORY=toolchain

if [ -z "$INSTALL_DIRECTORY" ];
then
    INSTALL_DIRECTORY=$(pwd)/$TOOLCHAIN_DIRECTORY
fi

# Toolchain paths
PATH="$INSTALL_DIRECTORY/bin:$PATH"

# Tools versions
BINUTILS_VERSION=2.36.1

GCC_VERSION=12.2.0
GDB_VERSION=10.1 # TODO: Add GDB
GMP_VERSION=6.2.1
MPFR_VERSION=4.2.0
MPC_VERSION=1.3.1

LLVM_VERSION=15.0.6

GRUB_VERSION=2.06
XORRISO_VERSION=1.5.4

export TOOLCHAIN_DIRECTORY INSTALL_DIRECTORY
