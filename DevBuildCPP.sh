#!/bin/bash

cd Project/CLI/CPP
./Build.sh
./Run.sh
./Build.sh
./Run.sh
cd ../../..

cd Project/Test/CPP
./Build.sh
./Run.sh
cd ../../..