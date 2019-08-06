#!/bin/bash

mkdir -p ../build
pushd ../build
c++ ../src/sdl_axum.cpp -o Axum -g -framework OpenGL `sdl2-config --cflags --libs -lGL -lGLEW`
popd
