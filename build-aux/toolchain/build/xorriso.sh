# Build xorriso

# Build directory
XORRISO_DIRECTORY="xorriso"

pushd $TOOLCHAIN_DIRECTORY
    # Download and extract xorriso
    if [ ! -d  $XORRISO_DIRECTORY  ];  then
        if [ ! -f xorriso-$XORRISO_VERSION.tar.gz ];  then
            wget https://ftp.gnu.org/gnu/xorriso/xorriso-$XORRISO_VERSION.tar.gz
        fi

        tar -xf xorriso-$XORRISO_VERSION.tar.gz
        mv xorriso-$XORRISO_VERSION xorriso
    fi

    # Build xorriso
    pushd $XORRISO_DIRECTORY
        ./configure --prefix=$INSTALL_DIRECTORY

        make -j $BUILD_THREADS

        make install
        
        make clean
    popd
popd
