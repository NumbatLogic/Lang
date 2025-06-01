#!/bin/bash

gdb -ex "set confirm off" -ex run -ex backtrace -ex quit --args ../../../Bin/Test
#valgrind --trace-children=yes --track-fds=yes --log-file=valgrind.txt --error-limit=no --leak-check=full --show-possibly-lost=yes --track-origins=yes --show-reachable=yes ../../../Bin/Test