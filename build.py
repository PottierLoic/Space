import os
import shutil

# Move files from imgui/backends to imgui
shutil.copy2('./libs/imgui/backends/imgui_impl_glfw.cpp', './libs/imgui')
shutil.copy2('./libs/imgui/backends/imgui_impl_glfw.h', './libs/imgui')
shutil.copy2('./libs/imgui/backends/imgui_impl_opengl3.cpp', './libs/imgui')
shutil.copy2('./libs/imgui/backends/imgui_impl_opengl3.h', './libs/imgui')
shutil.copy2('./libs/imgui/backends/imgui_impl_opengl3_loader.h', './libs/imgui')
shutil.copy2('./libs/imgui/misc/cpp/imgui_stdlib.cpp', './libs/imgui')
shutil.copy2('./libs/imgui/misc/cpp/imgui_stdlib.h', './libs/imgui')

# Remove Generated tests files
shutil.rmtree('./tests/Generated')

if os.name == 'nt':
  user_os = 'windows'
else:
  user_os = 'unix'

