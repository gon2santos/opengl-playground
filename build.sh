#!/bin/bash

CC=g++
CPPFLAGS=`pkg-config --cflags sdl2 assimp`
CPPFLAGS="$CPPFLAGS -I../Include"
LDFLAGS=`pkg-config --libs sdl2 assimp`
LDFLAGS="$LDFLAGS"

$CC ./src/main.cpp ./src/glad.c ./include/Game.cpp ./include/Shader.cpp ./include/stb_image.cpp ./include/Camera.cpp $CPPFLAGS $LDFLAGS -o main
