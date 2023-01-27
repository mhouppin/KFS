# Build Grub

# Build directory
GRUB_DIRECTORY="grub"

pushd  $TOOLCHAIN_DIRECTORY
    # Download and extract grub
    if  [ ! -d  $GRUB_DIRECTORY  ];  then 
        if [ ! -f grub-2.06.tar.xz ];  then
            wget https://ftp.gnu.org/gnu/grub/grub-2.06.tar.xz
        fi

        tar -xf grub-2.06.tar.xz
        mv grub-2.06 grub
    fi

    # Build grub
    pushd $GRUB_DIRECTORY
        ./configure \
            --prefix=$INSTALL_DIRECTORY \
            --disable-werror \
            --target=$TARGET
            # BUILD_CC=gcc \
            # TARGET_CC=$GRUB_CC \
            # TARGET_OBJCOPY=$GRUB_OBJCOPY \
            # TARGET_STRIP=$GRUB_STRIP \
            # TARGET_NM=$GRUB_NM \
            # TARGET_RANLIB=$GRUB_RANLIB

        make -j $(nproc --all)

        make install
        
        make clean
    popd
popd
