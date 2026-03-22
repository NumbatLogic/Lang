#!/bin/bash

mapfile -t sPackages < ../../../LangShared.package-list
sLangSharedArgs=()
for sPackage in "${sPackages[@]}"; do
	sLangSharedArgs+=("-f")
	sLangSharedArgs+=("../../../../LangShared/Source/$sPackage")
done

mono --debug CLI.exe -f ../../../Source "${sLangSharedArgs[@]}"
