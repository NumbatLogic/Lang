#!/bin/bash

./LangSharedCopy.sh

./RebuildCPP.sh
./DevBuildCPP.sh
./DevBuildCS.sh

./BackupCreate.sh
./BackupRun.sh