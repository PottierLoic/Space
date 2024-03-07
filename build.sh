#!/bin/bash
cmake -DBUILD_SHARED_LIBS=OFF -G "Unix Makefiles" -B "./build" .

cd build
make
cd ..