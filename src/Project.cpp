#include "Project.hpp"

Project::Project(std::string path, std::string name) {
  if (std::filesystem::exists(path + "/" + name)) {
    std::cerr << "Error: Project directory already exists." << std::endl;
  }

  std::filesystem::create_directory(path + "/" + name);
  std::filesystem::create_directory(path + "/" + name + "/assets");
  std::filesystem::create_directory(path + "/" + name + "/assets/textures");
  std::filesystem::create_directory(path + "/" + name + "/assets/models");
  std::filesystem::create_directory(path + "/" + name + "/assets/sounds");
  std::filesystem::create_directory(path + "/" + name + "/config");
  std::filesystem::create_directory(path + "/" + name + "/src");

  // Create main.cpp
  std::ofstream mainFile(path + "/" + name + "/src/main.cpp");
  mainFile << "#include <iostream>\n\n";
  mainFile << "int main() {\n";
  mainFile << "    std::cout << \"Hello, " << name << "!\" << std::endl;\n";
  mainFile << "    return 0;\n";
  mainFile << "}\n";
  mainFile.close();

  // Create CMakeLists.txt
  std::ofstream cmakeFile(path + "/" + name + "/CMakeLists.txt");
  cmakeFile << "cmake_minimum_required(VERSION 3.21)\n\n";
  cmakeFile << "project(" << name << ")\n\n";
  cmakeFile << "add_executable(" << name << " src/main.cpp)\n";
  cmakeFile.close();
}