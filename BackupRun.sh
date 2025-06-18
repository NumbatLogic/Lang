#!/bin/bash

rm -rf Transpiled
cd Backup/Project/CLI/CS
./Build.sh

mapfile -t sPackages < ../../../LangShared.package-list
sLangSharedArgs=()
for sPackage in "${sPackages[@]}"; do
	sLangSharedArgs+=("-f")
	sLangSharedArgs+=("../../../../../LangShared/$sPackage")
done

mono --debug Main.exe -f ../../../../Source "${sLangSharedArgs[@]}"