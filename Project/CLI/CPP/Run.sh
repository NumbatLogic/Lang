#!/bin/bash

mapfile -t sPackages < ../../../LangShared.package-list
sLangSharedArgs=()
for sPackage in "${sPackages[@]}"; do
	sLangSharedArgs+=("-f")
	sLangSharedArgs+=("../../../../LangShared/$sPackage")
done

gdb -ex "set confirm off" -ex run -ex backtrace -ex quit --args ../../../Bin/CLI -f ../../../Source "${sLangSharedArgs[@]}"