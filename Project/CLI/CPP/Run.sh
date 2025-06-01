#!/bin/bash

gdb -ex "set confirm off" -ex run -ex backtrace -ex quit --args ../../../Bin/CLI -f ../../../../Unstable/Source -f ../../../../Unstable/Shared
