# Get linux distribution name
DIS_NAME=$(lsb_release -is)

if [ $DIS_NAME = "Ubuntu" ];
then
	echo "[i] - Installing Ubuntu software requierments."
    if [ "$COMPILER" == "llvm" ];
    then
        sudo apt install -y clang lld grub2 xorriso qemu
    fi

    if [ "$COMPILER" == "gcc" ];
    then
        sudo apt install -y crossbuild-essential-$ARCH grub2 xorriso qemu
    fi
    exit 0
fi

echo "[x] - Unsupported linux distribution."
exit 1
