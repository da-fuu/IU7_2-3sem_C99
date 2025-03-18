#!/bin/bash

# Скрипт прогона модульного тестирования

make -s clean

if ! make -s unit_tests.exe; then
    echo "Failed build with make unit_tests.exe"
    exit 2
fi

if ! ./unit_tests.exe; then
    echo "Failed unit testing!"
    exit 1
fi
exit 0
