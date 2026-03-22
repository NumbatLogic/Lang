#!/bin/bash

mapfile -t sPackages < ../../../LangShared.package-list
sLangSharedArgs=()
for sPackage in "${sPackages[@]}"; do
	sLangSharedArgs+=("-f")
	sLangSharedArgs+=("../../../../LangShared/Source/$sPackage")
done

gdb -ex "set confirm off" -ex run -ex backtrace -ex quit --args ../../../Bin/CLI -f ../../../Source "${sLangSharedArgs[@]}"

# valgrind --trace-children=yes --track-fds=yes --log-file=valgrind.txt --error-limit=no --leak-check=full --show-possibly-lost=yes --track-origins=yes --show-reachable=yes ../../../Bin/CLI -f ../../../Source "${sLangSharedArgs[@]}"
