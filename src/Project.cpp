#include "Project.hpp"

Project::Project(std::string path, std::string name) {
  this->path = path;
  this->name = name;

  std::string projectDirectory = path + "/" + name;

  /* TODO: Should throw errors instead of just printing to std::cerr */
  /* TODO: Should create the project in this directory, create a basic scene etc.*/
  if (!std::filesystem::is_directory(projectDirectory)) {
    try {
      std::filesystem::create_directory(projectDirectory);
    } catch(const std::filesystem::filesystem_error& e) {
      std::cerr << "Filesystem error: " << e.what() << '\n';
    }
  } else {
    std::cerr << "Error: Project directory already exists.\n";
  }
}