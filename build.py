import os
import shutil
import subprocess

shutil.copy2('./libs/imgui/backends/imgui_impl_glfw.cpp', './libs/imgui')
shutil.copy2('./libs/imgui/backends/imgui_impl_glfw.h', './libs/imgui')
shutil.copy2('./libs/imgui/backends/imgui_impl_opengl3.cpp', './libs/imgui')
shutil.copy2('./libs/imgui/backends/imgui_impl_opengl3.h', './libs/imgui')
shutil.copy2('./libs/imgui/backends/imgui_impl_opengl3_loader.h', './libs/imgui')
shutil.copy2('./libs/imgui/misc/cpp/imgui_stdlib.cpp', './libs/imgui')
shutil.copy2('./libs/imgui/misc/cpp/imgui_stdlib.h', './libs/imgui')

generated_tests_path = './tests/Generated'
if os.path.exists(generated_tests_path):
    shutil.rmtree(generated_tests_path)

if os.name == 'nt':
  subprocess.run(['build.bat'])
else:
  subprocess.run(['./build.sh'], shell=True)
