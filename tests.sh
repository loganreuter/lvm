#!/bin/bash
TEST_PATH=./tests/test.c
OUTPUT=tests.exe

echo "Compiling " $TEST_PATH

clang $TEST_PATH -o $OUTPUT &
wait
echo "Done Compiling"
echo "Running " $OUTPUT
./tests.exe