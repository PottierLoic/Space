#include "Menu.hpp"

Menu::Menu() { }

void Menu::display() {
  /* Main menu options (On top of the window) */
  if (ImGui::BeginMainMenuBar()) {
    if (ImGui::BeginMenu("File")) {
      if (ImGui::MenuItem("New", "CTRL+N")) {}
      if (ImGui::MenuItem("Open", "CTRL+O")) {}
      if (ImGui::MenuItem("Save", "CTRL+S")) {}
      if (ImGui::MenuItem("Save as", "CTRL+SHIFT+S")) {}
      ImGui::Separator();
      if (ImGui::MenuItem("Import", "CTRL+I???")) {}
      if (ImGui::MenuItem("Export", "CTRL+E???")) {}
      ImGui::Separator();
      if (ImGui::MenuItem("Quit", "CTRL+W???")) {}
      ImGui::EndMenu();
    }

    if (ImGui::BeginMenu("Edit"))  {
      if (ImGui::MenuItem("Undo", "CTRL+Z")) {}
      if (ImGui::MenuItem("Redo", "CTRL+Y", false, false)) {}
      ImGui::Separator();
      if (ImGui::MenuItem("Cut", "CTRL+X")) {}
      if (ImGui::MenuItem("Copy", "CTRL+C")) {}
      if (ImGui::MenuItem("Paste", "CTRL+V")) {}
      ImGui::EndMenu();
    }

    if (ImGui::BeginMenu("Add")) {
      if (ImGui::MenuItem("Empty", "??")) {}
      ImGui::Separator();
      // 2D Forms
      if (ImGui::MenuItem("Circle", "??")) {}
      if (ImGui::MenuItem("Quad", "??")) {}
      ImGui::Separator();
      // 3D Forms
      if (ImGui::MenuItem("Sphere", "??")) {}
      if (ImGui::MenuItem("Cube", "??")) {}
      if (ImGui::MenuItem("Cylinder", "??")) {}
      ImGui::EndMenu();
    }

    if (ImGui::BeginMenu("Window")) {
      if (ImGui::MenuItem("Zoom in", "CTRL+PGUP")) {}
      if (ImGui::MenuItem("Zoom out", "CTRL+PGDN")) {}
      ImGui::Separator();
      ImGui::Checkbox("Inspector", &show_inspector);
      ImGui::Checkbox("Hierarchy", &show_hierarchy);
      ImGui::Checkbox("Project", &show_project);
      ImGui::Checkbox("Scene", &show_scene);
      ImGui::Checkbox("Render", &show_render);
      ImGui::Separator();
      if (ImGui::MenuItem("Toggle fullscreen", "F11")) {}
      ImGui::Separator();
      // TODO: Add layouts
      ImGui::Separator();
      if (ImGui::MenuItem("Reset layout", "CTRL+SHIFT+R")) {}
      ImGui::EndMenu();
    }

    ImGui::EndMainMenuBar();
  }

  if (show_inspector) {
    if (ImGui::Begin("Inspector")) {
      // TODO: call render() on all selected object components
      ImGui::End();
    }
  }

  if (show_hierarchy) {
    if (ImGui::Begin("Hierarchy")) {
      ImGui::End();
    }
  }

  if (show_scene) {
    if (ImGui::Begin("Scene")) {
      //TODO: Render the scene view.
      ImGui::End();
    }
  }

  if (show_render) {
    if (ImGui::Begin("Render")) {
      //TODO: Render the game rendering view (final appearance).
      ImGui::End();
    }
  }
}