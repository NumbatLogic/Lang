#!/bin/bash

cd Backup/Project/CLI/CS
./Build.sh
mono --debug Main.exe -f ../../../../Source -f ../../../../Shared

