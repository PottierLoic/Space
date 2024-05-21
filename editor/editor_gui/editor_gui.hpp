#pragma once

#include <string>
#include <unordered_map>
#include <functional>
#include <memory>

#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_stdlib.h"

#include "log/logger.hpp"

#include "scene/scene.hpp"
#include "entity/entity.hpp"

#include "component/component.hpp"
#include "component/transform.hpp"
#include "component/camera.hpp"
#include "component/physic.hpp"
#include "component/model_renderer.hpp"
#include "component/light.hpp"

using SpaceEngine::Scene;
using SpaceEngine::Entity;
using SpaceEngine::Component;
using SpaceEngine::Transform;
using SpaceEngine::Physic;
using SpaceEngine::ModelRenderer;
using SpaceEngine::Camera;

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
 * - void initComponentViewers(): Place all the component viewers functions inside of the componentViewers map.
 * - void display(): Displays the gui, rendering different sections based on the state of the flags.
 * - void cherryTheme(): Set the actual gui theme to cherry theme.
 */
class EditorGui {
private:
  bool showInspector = true;      // Inspector section visiblity flag.
  bool showHierarchy = true;      // Hierarchy section visiblity flag.
  bool showProject = true;        // Project section visiblity flag.
  bool showScene = true;          // Scene section visiblity flag.
  bool showRender = true;         // Render section visiblity flag.
  bool showConsole = true;       // Console section visibility flag.

  bool polygonMode = true;        // Polygon mode flag. (Draw the full model or just the wireframe)
  unsigned int textureColorbuffer;

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
  void displayProject();
  /* Display the scene section. */
  void displayScene();
  /* Display the render section. */
  void displayRender();
  /* Display the console section. */
  void displayConsole();

public:
  /* Reference to the actual Scene. */
  std::shared_ptr<Scene> scene;

  /* Reference to the selected Entity. */
  std::shared_ptr<Entity> selectedEntity = nullptr;

  bool sceneHovered = false;

  /*
   * Main constructor that use default flags.
   * @param scene: Reference to a scene.
   */
  EditorGui(std::shared_ptr<Scene> scene, unsigned int textureColorbuffer);

  /* Display the whole EditorGui. */
  void display();

  /* Gui themes */
  void cherryTheme();
};

}