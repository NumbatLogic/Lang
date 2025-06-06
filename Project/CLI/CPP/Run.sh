#!/bin/bash

gdb -ex "set confirm off" -ex run -ex backtrace -ex quit --args ../../../Bin/CLI -f ../../../Source -f ../../../Shared -f ../../../../LangShared/Assert -f ../../../../LangShared/Console -f ../../../../LangShared/Vector -f ../../../../LangShared/String
