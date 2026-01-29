#pragma once

#include <string>
#include <unordered_map>
#include <functional>
#include <memory>
#include <optional>

#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_stdlib.h"

#include "log/logger.hpp"
#include "scene/scene.hpp"
#include "resource_management/resource_manager.hpp"
#include "ecs/world.hpp"

#include "component/transform.hpp"
#include "component/camera.hpp"
#include "component/physic.hpp"
#include "component/model_renderer.hpp"
#include "component/light.hpp"

using SpaceEngine::Scene;
using SpaceEngine::World;
using SpaceEngine::Entity;
using SpaceEngine::Transform;
using SpaceEngine::Physic;
using SpaceEngine::ModelRenderer;
using SpaceEngine::Camera;
using SpaceEngine::Logger;
using SpaceEngine::ResourceManager;
using SpaceEngine::IHotReloadable;

namespace SpaceEditor {

class EditorGui {
  bool showInspector = true;
  bool showHierarchy = true;
  bool showProject = true;
  bool showScene = true;
  bool showRender = true;
  bool showConsole = true;

  bool showResourceManager = false;

  bool polygonMode = true;
  unsigned int sceneTexture;
  unsigned int renderTexture;

  std::unordered_map<std::type_index, std::function<void(World&, Entity)>> componentViewers;

  void initComponentViewers();
  void displayBar();
  void displayInspector();
  void displayHierarchy();
  void displayProject() const;
  void displayScene();
  void displayRender() const;
  void displayConsole();
  void displayResourceManager();

public:
  std::shared_ptr<Scene> scene = nullptr;

  std::optional<Entity> selectedEntity;

  bool sceneHovered = false;
  bool inspectorFocus = false;

  EditorGui(unsigned int sceneTexture, unsigned int renderTexture);

  void display();

  static void cherryTheme();
};

}