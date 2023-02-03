# Check if all dependencies are installed
CROSSTOOLCHAIN_DEPENDENCIES_TOOL="make wget tar xz gcc g++ "
CROSSTOOLCHAIN_DEPENDENCIES_LIBS=""

# Add gcc dependencies
CROSSTOOLCHAIN_DEPENDENCIES_TOOL+="bison flex texindex "
CROSSTOOLCHAIN_DEPENDENCIES_LIBS+="libgmp libmpc libmpfr "

# Add llvm (optional) dependencies
if [ "$COMPILER" == "llvm" ];
then
    CROSSTOOLCHAIN_DEPENDENCIES_TOOL+="cmake python3 pip3"
    CROSSTOOLCHAIN_DEPENDENCIES_LIBS+="libz"
fi

# Test if all required dependencies are installed
echo "[i] - Checking dependencies..."

# Check if all commands are installed
for name in $CROSSTOOLCHAIN_DEPENDENCIES_TOOL;
do
    if [ -z "$(which "$name" 2>/dev/null)" ];
    then
        echo "[!] - $name is not installed.";
        deps='true';
    fi
done

# Required to check the library install
if [ -z "$(which ldconfig 2>/dev/null)" ];
then
    echo "[x] - Lib config is required to check the library install."
    exit 1
done


# Check if all libraries are installed
for name in $CROSSTOOLCHAIN_DEPENDENCIES_LIBS;
do
    if [ "$(ldconfig -p | grep $name)" == "" ];
    then
        echo "[!] - $name is not installed.";
        deps='true';
    fi
done


if [ "$deps" == "true" ];
then
    echo "[i] - To get more information about dependencies, you can read the documentation."
    echo "[x] - Install dependencies above and rerun this script."
    exit 1
fi