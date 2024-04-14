import os
import shutil
import subprocess

definitions = """
#include "maths/vector.hpp"

#define IM_VEC2_CLASS_EXTRA                                                     \
        constexpr ImVec2(const SpaceEngine::Vec2f& f) : x(f.x), y(f.y) {}                   \
        operator SpaceEngine::Vec2f() const { return SpaceEngine::Vec2f(x,y); }

#define IM_VEC4_CLASS_EXTRA                                                     \
        constexpr ImVec4(const SpaceEngine::Vec4f& f) : x(f.x), y(f.y), z(f.z), w(f.w) {}   \
        operator SpaceEngine::Vec4f() const { return SpaceEngine::Vec4f(x,y,z,w); }
"""

subprocess.run(['git', 'submodule', 'init'])
subprocess.run(['git', 'submodule', 'update'])

shutil.copy2('./libs/imgui/backends/imgui_impl_glfw.cpp', './libs/imgui')
shutil.copy2('./libs/imgui/backends/imgui_impl_glfw.h', './libs/imgui')
shutil.copy2('./libs/imgui/backends/imgui_impl_opengl3.cpp', './libs/imgui')
shutil.copy2('./libs/imgui/backends/imgui_impl_opengl3.h', './libs/imgui')
shutil.copy2('./libs/imgui/backends/imgui_impl_opengl3_loader.h', './libs/imgui')
shutil.copy2('./libs/imgui/misc/cpp/imgui_stdlib.cpp', './libs/imgui')
shutil.copy2('./libs/imgui/misc/cpp/imgui_stdlib.h', './libs/imgui')

# Modify imconfig.h to allow for custom vector types
with open("./libs/imgui/imconfig.h", 'r+') as file:
  contents = file.read()
  if definitions not in contents:
    file.write(definitions)

generated_tests_path = './tests/Generated'
if os.path.exists(generated_tests_path):
  shutil.rmtree(generated_tests_path)

if os.name == 'nt':
  subprocess.run(['build.bat'])
else:
  subprocess.run(['./build.sh'], shell=True)
