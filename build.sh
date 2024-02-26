#!/bin/bash
cmake -DBUILD_SHARED_LIBS=OFF -G "Unix Makefiles" -B "./build" . -DFLAGS="$1"

cd build
make
cd ..