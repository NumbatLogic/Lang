#!/bin/bash

./RebuildCPP.sh
./DevBuildCPP.sh
./DevBuildCS.sh

./BackupCreate.sh
./BackupRun.sh