# !/bin/sh
# This script intented to be run from ${{ github.workspace }}

# TODO(@abadr99): Avoid calling this scripts twice in CI
# 1) in this script 
# 2) in test jobs

sh scripts/github/configureTests.sh
cd ./compiler
cmake -B ./build 

if [ $? -gt 0 ]
then 
    exit 1
fi

make  -C ./build cbit -j

if [ $? -gt 0 ]
then 
    exit 1
fi

cd -