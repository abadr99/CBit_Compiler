# !/bin/sh
# This script intented to be run from ${{ github.workspace }}
cd ./compiler
cmake -B ./build 

if [ $? -gt 0 ]
then 
    exit 1
fi

make  -C ./build cbit-tests -j

if [ $? -gt 0 ]
then 
    exit 1
fi

cd -