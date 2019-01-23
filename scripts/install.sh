#!/bin/bash

if echo "$0" | grep -q "scripts"
then
    mkdir -p build && cd build && conan install .. --build=missing && cmake .. -G "Unix Makefiles" && cmake --build .
else
    mkdir ../build && cd ../build && conan install .. --build=missing && cmake .. -G "Unix Makefiles" && cmake --build .
fi
