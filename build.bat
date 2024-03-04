@echo off
cmake -DBUILD_SHARED_LIBS=OFF -G "MinGW Makefiles" -B "./build" .

cd build
make
cd ..
