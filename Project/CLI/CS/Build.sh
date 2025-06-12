#!/bin/bash

compiler=csc
if command -v mono-csc >/dev/null 2>&1; then
  compiler=mono-csc
fi

${compiler} -debug:full -reference:System.IO.Compression.dll *.cs ../../../Transpiled/CLI/*.cs ../../../Transpiled/Core/*.cs ../../../Transpiled/Core/AST/*.cs ../../../Shared/CS/*.cs ../../../Transpiled/Shared/*.cs ../../../../LangShared/Assert/CS/*.cs