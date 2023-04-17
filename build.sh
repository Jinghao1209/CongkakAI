#!/bin/sh

set -xe

CC="g++"
CFLAGS="-Wall -Wextra -std=c++11"
LIBS=-lm
INCLUDES="-Iinclude/"

$CC $CFLAGS src/*.cpp $LIBS $INCLUDES -o main.out
