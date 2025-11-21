#!/bin/bash

find ./projects -iname '*.h' -o -iname '*.cpp' -o -iname '*.c' | clang-format --style=file -i --files=/dev/stdin
