# !/bin/sh
# This script intented to be run from ${{ github.workspace }}
cmake -B ./compiler/build 
make -C ./compiler/build -j
