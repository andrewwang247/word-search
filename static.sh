#!/bin/bash

# Copyright 2020 Siwei Wang.
# Run static checks on all C++ code.

set -Euo pipefail

# List of all C++ files.
cppfiles="*.h *.cpp"

printf "Running clang-format...\n\n"
clang-format -i -style=file $cppfiles

printf "Running cppcheck...\n\n"
cppcheck --language=c++ --std=c++11 --enable=all --quiet \
    --template=gcc --suppress=missingIncludeSystem $cppfiles

printf "\nRunning cpplint...\n\n"
cpplint --filter=-build/include_subdir --quiet $cppfiles
