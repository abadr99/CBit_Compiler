# !/bin/sh
# This script intented to be run from ${{ github.workspace }}
cd ./compiler
cmake -B ./build 
make  -C ./build -j
cd -