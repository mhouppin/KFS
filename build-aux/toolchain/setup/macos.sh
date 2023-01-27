# Check if brew is install
if [ ! "$(command -v brew)" ]; then
    echo "[x] - brew is required to setup toolchain Please visit https://brew.sh/"
    exit 1
fi

# Fix architecture for brew (i386 -> i686)
if [ $ARCH = "i386" ]; then
    ARCH="i686"
    TARGET="$ARCH-elf"
fi

# Installing all dependencies available on brew
brew install $TARGET-gcc xorriso qemu

# Create the toolchain install directory
if [ ! -d  $INSTALL_DIRECTORY ];  then 
    mkdir $INSTALL_DIRECTORY
fi

# Build Grub
source ./build-aux/toolchain/build/grub.sh


exit 0;