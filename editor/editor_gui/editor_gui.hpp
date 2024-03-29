#pragma once

#include <string>
#include <unordered_map>
#include <functional>
#include <memory>

#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_stdlib.h"

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

namespace SpaceEditor {

/*
 * The EditorGui class represents a user interface and control various aspects of a scene, including tools, inspector, hierarchy, and generation options.
 * It includes flags to control the visibility of different menu sections, a reference to the current scene, the selected scene object, and the current menu layout.
 *
 * Properties:
 * - showInspector (bool): Flag to control the visibility of the inspector section in the menu.
 * - showHierarchy (bool): Flag to control the visibility of the hierarchy section in the menu.
 * - showProject (bool): Flag to control the visibility of the project section in the menu.
 * - showScene (bool): Flag to control the visibility of the scene section in the menu.
 * - showRender (bool): Flag to control the visibility of the render section in the menu.
 *
 * - scene (Scene*): Reference to the actual Scene.
 * - selectedEntity (Entity*): Reference to the selected Entity.
 *
 * Constructor:
 * - EditorGui(): Initializes a new EditorGui.
 *
 * Methods:
 * - void initComponentViewers(): Place all the component viewers functions inside of the componentViewers map.
 * - void display(): Displays the menu, rendering different sections based on the state of the flags.
 * - void cherryTheme(): Set the actual menu theme to cherry theme.
 */
class EditorGui {
private:
  bool showInspector = true;      // Inspector section visiblity flag.
  bool showHierarchy = true;      // Hierarchy section visiblity flag.
  bool showProject = true;        // Project section visiblity flag.
  bool showScene = false;          // Scene section visiblity flag.
  bool showRender = false;         // Render section visiblity flag.

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

public:
  /* Reference to the actual Scene. */
  std::shared_ptr<Scene> scene;

  /* Reference to the selected Entity. */
  std::shared_ptr<Entity> selectedEntity = nullptr;

  /*
   * Main constructor that use default flags.
   * @param scene: Reference to a scene.
   */
  EditorGui(std::shared_ptr<Scene> scene);

  /* Display the whole EditorGui. */
  void display();

  /* Gui themes */
  void cherryTheme();
};

}