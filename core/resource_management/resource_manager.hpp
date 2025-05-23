#pragma once

#include<memory>
#include <typeindex>
#include <unordered_map>
#include <ranges>

#include "resource.hpp"
#include "resources/res_audio.hpp"
#include "resource_user.hpp"
#include "hot_reloadable.hpp"
#include "log/logger.hpp"

namespace SpaceEngine {

class ResourceManager {
public:
  template<typename T>
  static std::shared_ptr<T> load(const std::string& path, const std::shared_ptr<IResourceUser>& user = nullptr);

  static void unregisterUser(const std::string& path, const std::shared_ptr<IResourceUser>& user);

  template<typename T>
  static bool isLoaded(const std::string& path);

  static void clear();
  static void update(float deltaTime);

  static const std::unordered_map<std::type_index, std::unordered_map<std::string, std::shared_ptr<Resource>>>& getResources() { return s_resources; }
  static const std::unordered_map<std::string, std::vector<std::weak_ptr<IResourceUser>>>& getResourceUsers() { return s_resourceUsers; }

private:
  inline static std::unordered_map<std::type_index, std::unordered_map<std::string, std::shared_ptr<Resource>>> s_resources;
  inline static std::unordered_map<std::string, std::vector<std::weak_ptr<IResourceUser>>> s_resourceUsers;

  static void unloadUnusedResources();
  static void reloadOutdated();
  static inline float s_reloadTimer = 0.0f;
  static constexpr float RELOAD_INTERVAL = 1.0f;
};

}