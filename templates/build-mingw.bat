@echo off
cmake -DBUILD_SHARED_LIBS=OFF -G "MinGW Makefiles" -B "./build" . -DFLAGS=%1

cd build
make
cd ..
