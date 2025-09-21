#!/bin/bash

compiler=csc
if command -v mono-csc >/dev/null 2>&1; then
  compiler=mono-csc
fi

mapfile -t sPackages < ../../../LangShared.package-list
sLangSharedFiles=()
for sPackage in "${sPackages[@]}"; do
	while IFS= read -r -d '' csfile; do
		sLangSharedFiles+=("$csfile")
	done < <(find "../../../../LangShared/$sPackage" -type f -name '*.cs' -print0)

	transpiledDirectory="../../../../LangShared/Transpiled/$sPackage"
	if [ -d "$transpiledDirectory" ]; then
		while IFS= read -r -d '' csfile; do
			sLangSharedFiles+=("$csfile")
		done < <(find "$transpiledDirectory" -type f -name '*.cs' -print0)
	fi
done

${compiler} -debug:full -reference:System.IO.Compression.dll *.cs ../../../Transpiled/Test/*.cs ../../../Transpiled/Core/*.cs ../../../Transpiled/Core/AST/*.cs ${sLangSharedFiles[@]}