#!/bin/bash

mkdir -p ../build
pushd ../build
c++ ../src/sdl_axum.cpp -o Axum -g
popd
