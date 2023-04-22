@echo off

set TEST_PATH=./tests/test.c
set OUTPUT=tests.exe

echo Compiling  %TEST_PATH%
clang %TEST_PATH% -o %OUTPUT%
echo Done Compiling

echo Running  %OUTPUT%
tests.exe