#pragma once

#include <string>

#include "imgui/imgui_impl_glfw.h"

#include "scene/scene.hpp"
#include "entity/entity.hpp"
#include "component/transform.hpp"

namespace SpaceEditor {

/*
 * The Menu class represents a user interface and control various aspects of a scene, including tools, inspector, hierarchy, and generation options.
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
 * - Menu(): Initializes a new Menu.
 *
 * Methods:
 * - void display(): Displays the menu, rendering different sections based on the state of the flags.
 */
class Menu {
public:
  bool showInspector = false;      // Inspector section visiblity flag.
  bool showHierarchy = false;      // Hierarchy section visiblity flag.
  bool showProject = false;        // Project section visiblity flag.
  bool showScene = true;          // Scene section visiblity flag.
  bool showRender = false;         // Render section visiblity flag.

  /* Reference to the actual Scene. */
  Scene* scene;

  /* Reference to the selected Entity. */
  Entity* selectedEntity = nullptr;

  /*
   * Main constructor that use default flags.
   * @param scene: Reference to a scene.
   */
  Menu(Scene* scene);

  /* Display the whole menu. */
  void display();

  /* Display the menu bar. */
  void displayMenuBar();

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

  /* Menu themes */
  void cherryTheme();
};

}