# Build clang crosstoolchain (For Mac OS X)

# Build directory
LLVM_DIRECTORY="llvm"

pushd $TOOLCHAIN_DIRECTORY

    if [ ! -d  $LLVM_DIRECTORY  ];  then
        if [ ! -f llvmorg-$LLVM_VERSION.tar.gz ];  then
            wget https://github.com/llvm/llvm-project/archive/refs/tags/llvmorg-$LLVM_VERSION.tar.gz
        fi

        tar -xf llvmorg-$LLVM_VERSION.tar.gz
        mv llvm-project-llvmorg-$LLVM_VERSION llvm
    fi

    pushd $LLVM_DIRECTORY
        mkdir -pv build

        cmake \
            -S llvm \
            -B build \
            -G "Unix Makefiles" \
            -DCMAKE_BUILD_TYPE=Release \
            -DLLVM_ENABLE_PROJECTS="clang;lld;lldb;" \
            -DLLVM_TARGETS_TO_BUILD="X86" \
            -DLLVM_ENABLE_ASSERTIONS=ON \
            -DCMAKE_INSTALL_PREFIX=$INSTALL_DIRECTORY

        pushd build
            make -j $BUILD_THREADS

            make install

            make clean
        popd
    popd
popd