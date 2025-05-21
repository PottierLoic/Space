#include "resource_manager.hpp"

#include <iostream>

namespace SpaceEngine {

void ResourceManager::clear() {
  s_resources.clear();
}

template<typename T>
std::shared_ptr<T> ResourceManager::load(const std::string& path) {
  static_assert(std::is_base_of_v<Resource, T>, "Error: T must derive from Resource.");

  auto& typedMap = s_resources[typeid(T)];

  if (const auto it = typedMap.find(path); it != typedMap.end()) {
    std::cout<<"already loaded, loading from cache"<<std::endl;
    return std::static_pointer_cast<T>(it->second);
  }

  auto resource = T::loadFromFile(path);
  typedMap[path] = resource;
  return resource;
}

template<typename T>
bool ResourceManager::isLoaded(const std::string& path) {
  const auto& typedMap = s_resources[typeid(T)];
  return typedMap.contains(path);
}

template std::shared_ptr<ResAudio> ResourceManager::load<ResAudio>(const std::string&);
template bool ResourceManager::isLoaded<ResAudio>(const std::string&);

}
