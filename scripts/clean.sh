#!/bin/sh
if echo "$0" | grep -q "scripts"
then
    rm -rf build
else
    rm -rf ../build
fi
