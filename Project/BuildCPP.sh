#!/bin/bash
set -x

build="debugx64"

if [ $(uname -m) = "aarch64" ];
then
        build="debuga64"
fi

cd ProjectGen
cd linux_gmake
make config=${build} 2>&1 | stdbuf -o0 sed 's/\.\.\/\.\.\/\.\.\//\.\//g'
cd ..
cd ..
