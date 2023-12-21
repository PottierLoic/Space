@echo off
copy /Y .\libs\imgui\backends\imgui_impl_glfw.cpp .\libs\imgui
copy /Y .\libs\imgui\backends\imgui_impl_glfw.h .\libs\imgui
copy /Y .\libs\imgui\backends\imgui_impl_opengl3.cpp .\libs\imgui
copy /Y .\libs\imgui\backends\imgui_impl_opengl3.h .\libs\imgui
copy /Y .\libs\imgui\backends\imgui_impl_opengl3_loader.h .\libs\imgui


cmake -DBUILD_SHARED_LIBS=OFF -G "MinGW Makefiles" -B "./build" . -DFLAGS=%1

cd build
make
cd ..
