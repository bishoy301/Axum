#!/bin/bash

mkdir -p ../build
pushd ../build
c++ ../src/sdl_axum.cpp -o Axum -g `sdl2-config --cflags --libs`
popd
