#pragma once

#include <string>
#include <filesystem>
#include <iostream>
#include <vector>
#include <fstream>
#include <string>

namespace SpaceEditor {

class Project {
public:
  std::string name;
  std::string path;
  std::string lastScene;

  /* TODO: Project context (once the class will be done) contains the user config */
  // ProjectCtx config;

  std::string version;
  std::string description;
  std::string author;
  std::vector<std::string> supportedPlatforms;

  Project(std::string path, std::string name);
};

}
