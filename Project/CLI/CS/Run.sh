#!/bin/bash

mapfile -t sPackages < ../../../LangShared.package-list
sLangSharedArgs=()
for sPackage in "${sPackages[@]}"; do
	sLangSharedArgs+=("-f")
	sLangSharedArgs+=("../../../../LangShared/$sPackage")
done

mono --debug Main.exe -f ../../../Source "${sLangSharedArgs[@]}"
