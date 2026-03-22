#!/bin/bash

./DevBuildCS.sh

./RebuildCPP.sh
./DevBuildCPP.sh
./DevBuildCS.sh

./BackupCreate.sh
./BackupRun.sh