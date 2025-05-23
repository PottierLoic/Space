#include "resource_manager.hpp"

#include <iostream>
#include <ranges>

namespace SpaceEngine {

void ResourceManager::clear() {
  s_resources.clear();
}

template<typename T>
std::shared_ptr<T> ResourceManager::load(const std::string& path, const std::shared_ptr<IResourceUser>& user) {
  static_assert(std::is_base_of_v<Resource, T>, "Error: T must derive from Resource.");

  auto& typedMap = s_resources[typeid(T)];

  if (const auto it = typedMap.find(path); it != typedMap.end()) {
    if (user) s_resourceUsers[path].push_back(user);
    return std::static_pointer_cast<T>(it->second);
  }

  auto resource = T::loadFromFile(path);
  if (resource) {
    typedMap[path] = resource;
    if (user) {
      s_resourceUsers[path].push_back(user);
    }
  }
  return resource;
}

template<typename T>
bool ResourceManager::isLoaded(const std::string& path) {
  const auto& typedMap = s_resources[typeid(T)];
  return typedMap.contains(path);
}

void ResourceManager::reloadOutdated() {
  for (auto &typedMap: s_resources | std::views::values) {
    for (auto& [path, resource] : typedMap) {
      if (const auto reloadable = std::dynamic_pointer_cast<IHotReloadable>(resource); reloadable && reloadable->isOutdated()) {
        const auto updated = reloadable->reload();
        typedMap[path] = updated;

        if (s_resourceUsers.contains(path)) {
          auto& users = s_resourceUsers[path];
          for (auto it = users.begin(); it != users.end();) {
            if (const auto user = it->lock()) {
              user->onResourceReloaded(path);
              ++it;
            } else {
              it = users.erase(it);
            }
          }
        }
      }
    }
  }
}

void ResourceManager::update(const float deltaTime) {
  s_reloadTimer += deltaTime;
  if (s_reloadTimer >= RELOAD_INTERVAL) {
    reloadOutdated();
    s_reloadTimer = 0.0f;
  }
}

template std::shared_ptr<ResAudio> ResourceManager::load<ResAudio>(const std::string&, const std::shared_ptr<IResourceUser>&);
template bool ResourceManager::isLoaded<ResAudio>(const std::string&);

}
