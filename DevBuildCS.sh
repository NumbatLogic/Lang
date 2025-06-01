#!/bin/bash

cd Project/CLI/CS
./Build.sh
./Run.sh
./Build.sh
./Run.sh
cd ../../..

cd Project/Test/CS
./Build.sh
./Run.sh
cd ../../..