#pragma once

#include<memory>
#include <typeindex>
#include <unordered_map>

#include "resource.hpp"
#include "resources/res_audio.hpp"
#include "resource_user.hpp"
#include "hot_reloadable.hpp"

namespace SpaceEngine {

class ResourceManager {
public:
  template<typename T>
  std::shared_ptr<T> load(const std::string& path, const std::shared_ptr<IResourceUser>& user = nullptr);

  template<typename T>
  static bool isLoaded(const std::string& path);

  static void clear();

private:
  inline static std::unordered_map<std::type_index, std::unordered_map<std::string, std::shared_ptr<Resource>>> s_resources;
  inline static std::unordered_map<std::string, std::vector<std::weak_ptr<IResourceUser>>> s_resourceUsers;

  static void reloadOutdated();
  static void registerUser(const std::string& path, const std::shared_ptr<IResourceUser>& user);

};

}