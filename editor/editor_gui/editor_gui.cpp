#include "editor_gui/editor_gui.hpp"

using namespace SpaceEngine;
namespace SpaceEditor {

EditorGui::EditorGui(std::shared_ptr<Scene> scene) {
  this->scene = scene;
  initComponentViewers();
  cherryTheme();
}

void EditorGui::display() {
  displayBar();
  if (showInspector) { displayInspector(); }
  if (showHierarchy) { displayHierarchy(); }
  if (showProject) { displayProject(); }
  if (showScene) { displayScene(); }
  if (showRender) { displayRender(); }
  if (showConsole) { displayConsole(); }
}

void EditorGui::displayBar() {
  /* Top bar options */
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
      ImGui::Checkbox("Inspector", &showInspector);
      ImGui::Checkbox("Hierarchy", &showHierarchy);
      ImGui::Checkbox("Project", &showProject);
      ImGui::Checkbox("Scene", &showScene);
      ImGui::Checkbox("Render", &showRender);
      ImGui::Separator();
      if (ImGui::MenuItem("Toggle fullscreen", "F11")) {}
      ImGui::Separator();
      // TODO: Add layouts
      ImGui::Separator();
      if (ImGui::MenuItem("Reset layout", "CTRL+SHIFT+R")) {}
      ImGui::Separator();
      if (ImGui::Checkbox("Wireframe Mode", &polygonMode)) {
        if (polygonMode) {
          glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        } else {
          glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        }
      }
      ImGui::EndMenu();
    }

    ImGui::EndMainMenuBar();
  }
}

void EditorGui::displayInspector() {
  if (ImGui::Begin("Inspector")) {
    if (selectedEntity != nullptr) {
      for (const auto& componentPair : selectedEntity->components) {
        std::type_index typeIndex = componentPair.first;
        auto component = componentPair.second;
        auto viewerIt = componentViewers.find(typeIndex);
        if (viewerIt != componentViewers.end()) {
          viewerIt->second(component);
        }
      }
    }
  }
  ImGui::End();
}

void EditorGui::displayHierarchy() {
  if (ImGui::Begin("Hierarchy")) {
    // TODO: Render the hierarchy view.
  }
  ImGui::End();
}

void EditorGui::displayProject() {
  if (ImGui::Begin("Project")) {
    //TODO: Render the scene view.
  }
  ImGui::End();
}

void EditorGui::displayScene() {
  if (ImGui::Begin("Scene")) {
    //TODO: Render the game editor view (draft appearance).
  }
  ImGui::End();
}

void EditorGui::displayRender() {
  if (ImGui::Begin("Render")) {
    //TODO: Render the game rendering view (final appearance).
  }
  ImGui::End();
}

void EditorGui::displayConsole() {
  if (ImGui::Begin("Console")) {
    // TODO: enhance this (it's awfull in the editor)
    // Filter inputs
    // for (size_t i = 0; i < logLevels.size(); ++i) {
    //   if (ImGui::Selectable(logLevels[i], Logger::filter.levels.count(static_cast<LogLevel>(i)))) {
    //     Logger::filter.setLogLevel(static_cast<LogLevel>(i), !Logger::filter.levels.count(static_cast<LogLevel>(i)));
    //   }
    // }
    // ImGui::NewLine();
    // for (size_t i = 0; i < logTypes.size(); ++i) {
    //   if (ImGui::Selectable(logTypes[i], Logger::filter.types.count(static_cast<LogType>(i)))) {
    //     Logger::filter.setLogType(static_cast<LogType>(i), !Logger::filter.types.count(static_cast<LogType>(i)));
    //   }
    // }
    // ImGui::NewLine();
    ImGui::Text("Search: ");
    ImGui::SameLine();
    ImGui::InputText("##log_search", &Logger::filter.keyword);

    // Log list filtered.
    ImGui::SeparatorText("Logs");
    for (const auto& log : Logger::getLogEntries()) {
      std::string texte = log.toString();
      ImGui::Text("%s", texte.c_str());
    }
  }
  ImGui::End();
}

void EditorGui::cherryTheme() {
  // cherry colors, 3 intensities
  #define HI(v)   ImVec4(0.502f, 0.075f, 0.256f, v)
  #define MED(v)  ImVec4(0.455f, 0.198f, 0.301f, v)
  #define LOW(v)  ImVec4(0.232f, 0.201f, 0.271f, v)
  // backgrounds (@todo: complete with BG_MED, BG_LOW)
  #define BG(v)   ImVec4(0.200f, 0.220f, 0.270f, v)
  // text
  #define TEXT(v) ImVec4(0.860f, 0.930f, 0.890f, v)

  auto &style = ImGui::GetStyle();
  style.Colors[ImGuiCol_Text]                  = TEXT(0.78f);
  style.Colors[ImGuiCol_TextDisabled]          = TEXT(0.28f);
  style.Colors[ImGuiCol_WindowBg]              = ImVec4(0.13f, 0.14f, 0.17f, 1.00f);
  style.Colors[ImGuiCol_WindowBg]              = BG( 0.58f);
  style.Colors[ImGuiCol_PopupBg]               = BG( 0.9f);
  style.Colors[ImGuiCol_Border]                = ImVec4(0.31f, 0.31f, 1.00f, 0.00f);
  style.Colors[ImGuiCol_BorderShadow]          = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
  style.Colors[ImGuiCol_FrameBg]               = BG( 1.00f);
  style.Colors[ImGuiCol_FrameBgHovered]        = MED( 0.78f);
  style.Colors[ImGuiCol_FrameBgActive]         = MED( 1.00f);
  style.Colors[ImGuiCol_TitleBg]               = LOW( 1.00f);
  style.Colors[ImGuiCol_TitleBgActive]         = HI( 1.00f);
  style.Colors[ImGuiCol_TitleBgCollapsed]      = BG( 0.75f);
  style.Colors[ImGuiCol_MenuBarBg]             = BG( 0.47f);
  style.Colors[ImGuiCol_ScrollbarBg]           = BG( 1.00f);
  style.Colors[ImGuiCol_ScrollbarGrab]         = ImVec4(0.09f, 0.15f, 0.16f, 1.00f);
  style.Colors[ImGuiCol_ScrollbarGrabHovered]  = MED( 0.78f);
  style.Colors[ImGuiCol_ScrollbarGrabActive]   = MED( 1.00f);
  style.Colors[ImGuiCol_CheckMark]             = ImVec4(0.71f, 0.22f, 0.27f, 1.00f);
  style.Colors[ImGuiCol_SliderGrab]            = ImVec4(0.47f, 0.77f, 0.83f, 0.14f);
  style.Colors[ImGuiCol_SliderGrabActive]      = ImVec4(0.71f, 0.22f, 0.27f, 1.00f);
  style.Colors[ImGuiCol_Button]                = ImVec4(0.47f, 0.77f, 0.83f, 0.14f);
  style.Colors[ImGuiCol_ButtonHovered]         = MED( 0.86f);
  style.Colors[ImGuiCol_ButtonActive]          = MED( 1.00f);
  style.Colors[ImGuiCol_Header]                = MED( 0.76f);
  style.Colors[ImGuiCol_HeaderHovered]         = MED( 0.86f);
  style.Colors[ImGuiCol_HeaderActive]          = HI( 1.00f);
  // style.Colors[ImGuiCol_COUNT]                = ImVec4(0.14f, 0.16f, 0.19f, 1.00f);
  style.Colors[ImGuiCol_ButtonHovered]         = MED( 0.78f);
  style.Colors[ImGuiCol_ButtonActive]          = MED( 1.00f);
  style.Colors[ImGuiCol_ResizeGrip]            = ImVec4(0.47f, 0.77f, 0.83f, 0.04f);
  style.Colors[ImGuiCol_ResizeGripHovered]     = MED( 0.78f);
  style.Colors[ImGuiCol_ResizeGripActive]      = MED( 1.00f);
  style.Colors[ImGuiCol_PlotLines]             = TEXT(0.63f);
  style.Colors[ImGuiCol_PlotLinesHovered]      = MED( 1.00f);
  style.Colors[ImGuiCol_PlotHistogram]         = TEXT(0.63f);
  style.Colors[ImGuiCol_PlotHistogramHovered]  = MED( 1.00f);
  style.Colors[ImGuiCol_TextSelectedBg]        = MED( 0.43f);
  // [...]
  style.Colors[ImGuiCol_ModalWindowDimBg]  = BG( 0.73f);

  style.WindowPadding            = ImVec2(6, 4);
  style.WindowRounding           = 0.0f;
  style.FramePadding             = ImVec2(5, 2);
  style.FrameRounding            = 3.0f;
  style.ItemSpacing              = ImVec2(7, 1);
  style.ItemInnerSpacing         = ImVec2(1, 1);
  style.TouchExtraPadding        = ImVec2(0, 0);
  style.IndentSpacing            = 6.0f;
  style.ScrollbarSize            = 12.0f;
  style.ScrollbarRounding        = 16.0f;
  style.GrabMinSize              = 20.0f;
  style.GrabRounding             = 2.0f;

  style.WindowTitleAlign.x = 0.50f;

  style.Colors[ImGuiCol_Border] = ImVec4(0.539f, 0.479f, 0.255f, 0.162f);
  style.FrameBorderSize = 0.0f;
  style.WindowBorderSize = 1.0f;
}

}