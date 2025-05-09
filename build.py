import os
import shutil
import subprocess

# subprocess.run(['git', 'submodule', 'init'])
# subprocess.run(['git', 'submodule', 'update'])

shutil.copy2('./libs/imgui/backends/imgui_impl_glfw.cpp', './libs/imgui')
shutil.copy2('./libs/imgui/backends/imgui_impl_glfw.h', './libs/imgui')
shutil.copy2('./libs/imgui/backends/imgui_impl_opengl3.cpp', './libs/imgui')
shutil.copy2('./libs/imgui/backends/imgui_impl_opengl3.h', './libs/imgui')
shutil.copy2('./libs/imgui/backends/imgui_impl_opengl3_loader.h', './libs/imgui')
shutil.copy2('./libs/imgui/misc/cpp/imgui_stdlib.cpp', './libs/imgui')
shutil.copy2('./libs/imgui/misc/cpp/imgui_stdlib.h', './libs/imgui')

generated_tests_path = './tests/generated'
if os.path.exists(generated_tests_path):
  shutil.rmtree(generated_tests_path)

if os.name == 'nt':
  cmake_command = [
    'cmake',
    '-DBUILD_SHARED_LIBS=OFF',
    '-G', 'MinGW Makefiles',
    '-DCMAKE_MAKE_PROGRAM=make',
    '-DCMAKE_C_COMPILER=gcc',
    '-DCMAKE_CXX_COMPILER=g++',
    '-B', './build',
    '.'
  ]
  make_command = ['make', '-C', './build']
else:
  cmake_command = ['cmake', '-DBUILD_SHARED_LIBS=OFF', '-G', 'Unix Makefiles', '-B', './build', '.']
  make_command = ['make', '-C', './build']

subprocess.run(cmake_command)
subprocess.run(make_command)
