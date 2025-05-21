#pragma once

#include<memory>
#include <typeindex>
#include <unordered_map>

#include "resource.hpp"
#include "resource_management/resources/res_audio.hpp"

namespace SpaceEngine {

class ResourceManager {
public:
  template<typename T>
  static std::shared_ptr<T> load(const std::string& path);

  template<typename T>
  static bool isLoaded(const std::string& path);

  static void clear();

private:
  inline static std::unordered_map<std::type_index, std::unordered_map<std::string, std::shared_ptr<Resource>>> s_resources;
};

}