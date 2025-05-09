#pragma once

#include <string>
#include <filesystem>
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <memory>

#include "scene/scene.hpp"

namespace SpaceEngine {

class Space {
public:
  std::string name;
  std::string path;
  std::string version;
  std::string description;
  std::string author;
  std::vector<std::string> supportedPlatforms;

  std::shared_ptr<Scene> currentScene;
  std::vector<std::shared_ptr<Scene>> scenes;

  Space(const std::string& path, const std::string &name);
};

}
