#include "Project.hpp"

Project::Project(std::string path, std::string name) {
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

  // Bring basic main.cpp from template folder
  std::filesystem::copy("../templates/main.cpp", projectPath + "/src/main.cpp");

  // Bring basic CMakeLists.txt from template folder
  std::filesystem::copy("../templates/CMakeLists.txt", projectPath + "/CMakeLists.txt");

  // Bring build-mingw.bat and build-unix.sh from template folder
  std::filesystem::copy("../templates/build-mingw.bat", projectPath + "/build.bat");
  std::filesystem::copy("../templates/build-unix.sh", projectPath + "/build.sh");


}