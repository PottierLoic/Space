#include "space.hpp"

namespace SpaceEngine {

Space::Space(const std::string& path, const std::string &name) {
  // TODO: Maybe make a create function for this and certainly not in the constructor
  if (std::filesystem::exists(path + "/" + name)) {
    // TODO: Load the projects
  } else {
    this->name = name;
    this->path = path;

    currentScene = std::make_shared<Scene>();
    this->scenes.push_back(currentScene);
  }

  // std::string projectPath = path + "/" + name;
  // std::filesystem::create_directory(projectPath);
  // std::filesystem::create_directory(projectPath + "/assets");
  // std::filesystem::create_directory(projectPath + "/assets/textures");
  // std::filesystem::create_directory(projectPath + "/assets/models");
  // std::filesystem::create_directory(projectPath + "/assets/sounds");
  // std::filesystem::create_directory(projectPath + "/config");
  // std::filesystem::create_directory(projectPath + "/src");
  // std::filesystem::copy("./project_template/main.cpp", projectPath + "/src/main.cpp", std::filesystem::copy_options::overwrite_existing);
  // std::filesystem::copy("./project_template/CMakeLists.txt", projectPath + "/CMakeLists.txt", std::filesystem::copy_options::overwrite_existing);
}

}
