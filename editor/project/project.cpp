#include "project.hpp"

namespace SpaceEditor {

Project::Project(const std::string path, const std::string name) {
  if (std::filesystem::exists(path + "/" + name)) {
    std::cerr << "Error: Project directory already exists." << std::endl;
  }

  std::string projectPath = path + "/" + name;

  std::filesystem::create_directory(projectPath);
  std::filesystem::create_directory(projectPath + "/assets");
  std::filesystem::create_directory(projectPath + "/assets/textures");
  std::filesystem::create_directory(projectPath + "/assets/models");
  std::filesystem::create_directory(projectPath + "/assets/sounds");
  std::filesystem::create_directory(projectPath + "/config");
  std::filesystem::create_directory(projectPath + "/src");

  // Create main.cpp
  std::ofstream mainFile(projectPath + "/src/main.cpp");
  mainFile << "#include <iostream>\n\n";
  mainFile << "int main() {\n";
  mainFile << "    std::cout << \"Hello, " << name << "!\" << std::endl;\n";
  mainFile << "    return 0;\n";
  mainFile << "}\n";
  mainFile.close();

  // Create CMakeLists.txt
  std::ofstream CMakeFile(projectPath + "/CMakeLists.txt");
  std::filesystem::copy("./templates/CMakeLists.txt", projectPath + "/CMakeLists.txt");
}

}
