#pragma once

#include <string>
#include <unordered_map>
#include <functional>
#include <memory>

#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_stdlib.h"

#include "log/logger.hpp"
#include "space/space.hpp"
#include "scene/scene.hpp"
#include "entity/entity.hpp"
#include "resource_management/resource_manager.hpp"

#include "component/component.hpp"
#include "component/transform.hpp"
#include "component/camera.hpp"
#include "component/physic.hpp"
#include "component/model_renderer.hpp"
#include "component/light.hpp"

using SpaceEngine::Space;
using SpaceEngine::Scene;
using SpaceEngine::Entity;
using SpaceEngine::Component;
using SpaceEngine::Transform;
using SpaceEngine::Physic;
using SpaceEngine::ModelRenderer;
using SpaceEngine::Camera;
using SpaceEngine::Logger;
using SpaceEngine::ResourceManager;
using SpaceEngine::IHotReloadable;

namespace SpaceEditor {

/*
 * The EditorGui class represents a user interface and control various aspects of a scene, including tools, inspector, hierarchy, and generation options.
 * It includes flags to control the visibility of different gui sections, a reference to the current scene, the selected scene object, and the current gui layout.
 *
 * Properties:
 * - showInspector (bool): Flag to control the visibility of the inspector section in the gui.
 * - showHierarchy (bool): Flag to control the visibility of the hierarchy section in the gui.
 * - showProject (bool): Flag to control the visibility of the project section in the gui.
 * - showScene (bool): Flag to control the visibility of the scene section in the gui.
 * - showRender (bool): Flag to control the visibility of the render section in the gui.
 * - showConsole (bool): Flag to control the visibility of the console section in the gui
 *
 * - scene (Scene*): Reference to the actual Scene.
 * - selectedEntity (Entity*): Reference to the selected Entity.
 *
 * Constructor:
 * - EditorGui(): Initializes a new EditorGui.
 *
 * Methods:
 * - void initComponentViewers(): Place all the component viewers functions inside the componentViewers map.
 * - void display(): Displays the gui, rendering different sections based on the state of the flags.
 * - void cherryTheme(): Set the actual gui theme to cherry theme.
 */
class EditorGui {
  bool showInspector = true;      // Inspector section visibility flag.
  bool showHierarchy = true;      // Hierarchy section visibility flag.
  bool showProject = true;        // Project section visibility flag.
  bool showScene = true;          // Scene section visibility flag.
  bool showRender = true;         // Render section visibility flag.
  bool showConsole = true;       // Console section visibility flag.

  bool showResourceManager = false; // Resource manager section visibility flag.

  bool polygonMode = true;        // Polygon mode flag. (Draw the full model or just the wireframe)
  unsigned int sceneTexture;      // Scene view texture
  unsigned int renderTexture;     // Render view texture

  std::unordered_map<std::type_index, std::function<void(std::shared_ptr<Component>)>> componentViewers;

  /* Display a transform component section. */
  void initComponentViewers();
  /* Display the menu bar. */
  void displayBar();
  /* Display the inspector section. */
  void displayInspector();
  /* Display the hierarchy section. */
  void displayHierarchy();
  /* Display the project section. */
  void displayProject() const;
  /* Display the scene section. */
  void displayScene();
  /* Display the render section. */
  void displayRender() const;
  /* Display the console section. */
  void displayConsole();
  /* Display the resource manager section. */
  void displayResourceManager();

public:
  /* Reference to the actual Space */
  std::shared_ptr<Space> space = nullptr;

  /* Reference to the selected Entity. */
  std::shared_ptr<Entity> selectedEntity = nullptr;

  bool sceneHovered = false;
  bool inspectorFocus = false;

  /* Main constructor that uses default flags. */
  EditorGui(unsigned int sceneTexture, unsigned int renderTexture);

  /* Display the whole EditorGui. */
  void display();

  /* Gui themes */
  static void cherryTheme();
};

}