# !/bin/sh
# This script intented to be run from ${{ github.workspace }}
sudo apt update
sudo apt install cmake
mkdir ./compiler/build
