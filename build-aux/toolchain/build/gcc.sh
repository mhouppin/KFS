# Build GCC crosstoolchain (For Unix)

BINUTILS_DIRECTORY="binutils"
GCC_DIRECTORY="gcc"

pushd $TOOLCHAIN_DIRECTORY
    # Download and extract Binutils
    if [ ! -d  $BINUTILS_DIRECTORY  ];  then
        if [ ! -f binutils-$BINUTILS_VERSION.tar.xz ];  then
            wget https://ftp.gnu.org/gnu/binutils/binutils-$BINUTILS_VERSION.tar.xz
        fi

        tar -xf binutils-$BINUTILS_VERSION.tar.xz
        mv binutils-$BINUTILS_VERSION $BINUTILS_DIRECTORY
    fi

    # Download GCC
    if [ ! -d  $GCC_DIRECTORY  ];  then
        if [ ! -f gcc-$GCC_VERSION.tar.xz ];  then
            wget https://ftp.gnu.org/gnu/gcc/gcc-$GCC_VERSION/gcc-$GCC_VERSION.tar.xz
        fi

        # Download GMP, MPFR, and MPC (GCC dependencies)
        if [ ! -f gmp-$GMP_VERSION.tar.xz ];  then
            wget https://ftp.gnu.org/gnu/gmp/gmp-$GMP_VERSION.tar.xz
        fi

        if [ ! -f mpfr-$MPFR_VERSION.tar.xz ];  then
            wget https://ftp.gnu.org/gnu/mpfr/mpfr-$MPFR_VERSION.tar.xz
        fi

        if [ ! -f mpc-$MPC_VERSION.tar.gz ];  then
            wget https://ftp.gnu.org/gnu/mpc/mpc-$MPC_VERSION.tar.gz
        fi

        # Extract GCC
        tar -xf gcc-$GCC_VERSION.tar.xz
        mv gcc-$GCC_VERSION $GCC_DIRECTORY

        # Extract GMP, MPFR, and MPC
        pushd $GCC_DIRECTORY
            tar -xf ../gmp-$GMP_VERSION.tar.xz 
            tar -xf ../mpfr-$MPFR_VERSION.tar.xz 
            tar -xf ../mpc-$MPC_VERSION.tar.gz

            mv gmp-$GMP_VERSION gmp
            mv mpfr-$MPFR_VERSION mpfr
            mv mpc-$MPC_VERSION mpc
        popd
    fi
   
    # Build Binutils
    pushd $BINUTILS_DIRECTORY
        mkdir -pv build

        pushd build
            ../configure \
                --target=$TARGET \
                --prefix=$INSTALL_DIRECTORY \
                --with-sysroot \
                --disable-nls \
                --disable-werror \

            make -j $BUILD_THREADS

            make install
            make clean
        popd
    popd

    # Build GCC
    pushd $GCC_DIRECTORY
        mkdir -pv build
        pushd build
            ../configure \
                --target=$TARGET \
                --prefix=$INSTALL_DIRECTORY \
                --disable-nls \
                --enable-languages=c,c++ \
                --without-headers

            make all-gcc -j $BUILD_THREADS
            make all-target-libgcc -j $BUILD_THREADS

            make install-gcc
            make install-target-libgcc
        popd
    popd
popd
