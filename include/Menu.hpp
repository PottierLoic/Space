#pragma once

#include <string>

#include "imgui/imgui_impl_glfw.h"

#include "Components/Transform.hpp"

/*
 * The Menu class represents a user interface and control various aspects of a scene, including tools, inspector, hierarchy, and generation options.
 * It includes flags to control the visibility of different menu sections, a reference to the current scene, the selected scene object, and the current menu layout.
 *
 * Properties:
 * - show_inspector (bool): Flag to control the visibility of the inspector section in the menu.
 * - show_hierarchy (bool): Flag to control the visibility of the hierarchy section in the menu.
 * - show_project (bool): Flag to control the visibility of the project section in the menu.
 * - show_scene (bool): Flag to control the visibility of the scene section in the menu.
 * - show_render (bool): Flag to control the visibility of the render section in the menu.
 *
 * Constructor:
 * - Menu(): Initializes a new Menu.
 *
 * Methods:
 * - void display(): Displays the menu, rendering different sections based on the state of the flags.
 */
class Menu {
public:
  bool show_inspector = false;      // Inspector section visiblity flag
  bool show_hierarchy = false;      // Hierarchy section visiblity flag
  bool show_project = false;        // Project section visiblity flag
  bool show_scene = false;          // Scene section visiblity flag
  bool show_render = false;         // Render section visiblity flag

  /* Main constructor */
  Menu();

  /* Display the whole menu */
  void display();
};
