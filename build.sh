#!/bin/bash

cp -f ./libs/imgui/backends/imgui_impl_glfw.cpp ./libs/imgui
cp -f ./libs/imgui/backends/imgui_impl_glfw.h ./libs/imgui
cp -f ./libs/imgui/backends/imgui_impl_opengl3.cpp ./libs/imgui
cp -f ./libs/imgui/backends/imgui_impl_opengl3.h ./libs/imgui
cp -f ./libs/imgui/backends/imgui_impl_opengl3_loader.h ./libs/imgui
cp -f ./libs/imgui/misc/cpp/imgui_stdlib.cpp ./libs/imgui
cp -f ./libs/imgui/misc/cpp/imgui_stdlib.h ./libs/imgui
rm -r ./tests/Generated

cmake -DBUILD_SHARED_LIBS=OFF -G "Unix Makefiles" -B "./build" . -DFLAGS="$1"

cd build
make
cd ..