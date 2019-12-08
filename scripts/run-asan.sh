#!/bin/bash

export CTEST_OUTPUT_ON_FAILURE=1
export ASAN_OPTIONS=strict_string_checks=1:detect_stack_use_after_return=1:check_initialization_order=1:strict_init_order=1:detect_container_overflow=1

mkdir build
pushd build || exit
echo "Running ASAN in $PWD"
cmake .. -DENABLE_ADDRESS_SANITIZER=ON || exit
make -j"$(nproc)" all test
popd || exit
