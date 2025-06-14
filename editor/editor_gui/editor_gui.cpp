#include "editor_gui/editor_gui.hpp"

namespace SpaceEditor {

EditorGui::EditorGui(const unsigned int sceneTexture, const unsigned int renderTexture) {
  this->sceneTexture = sceneTexture;
  this->renderTexture = renderTexture;
  initComponentViewers();
  cherryTheme();
}

void EditorGui::display() {
  displayBar();
  if (showInspector) { displayInspector(); }
  if (showHierarchy) { displayHierarchy(); }
  if (showProject) { displayProject(); }
  if (showRender) { displayRender(); }
  if (showConsole) { displayConsole(); }
  if (showScene) { displayScene(); }
  if (showResourceManager) { displayResourceManager(); }
}

void EditorGui::displayBar() {
  /* Top bar options */
  if (ImGui::BeginMainMenuBar()) {
    if (ImGui::BeginMenu("File")) {
      if (ImGui::MenuItem("New", "CTRL+N")) {
        space->currentScene = std::make_shared<Scene>(); // working
        space = std::make_shared<Space>("test", "test");
      }
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
      if (ImGui::MenuItem("Empty", "??")) {
        if (space && space->currentScene) {
          const auto ent = Entity::create("New entity");
          space->currentScene->entities.push_back(ent);
        }
      }
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
      ImGui::Checkbox("Resource Manager", &showResourceManager);
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
    if (selectedEntity) {
      for (const auto&[fst, snd] : selectedEntity->components) {
        std::type_index typeIndex = fst;
        const auto component = snd;
        if (auto viewerIt = componentViewers.find(typeIndex); viewerIt != componentViewers.end()) {
          viewerIt->second(component);
        }
      }
    }
  }
  ImGui::End();
}

void EditorGui::displayHierarchy() {
  if (ImGui::Begin("Hierarchy")) {
    if (space && space->currentScene) {
      int index = 0;
      for (auto& entity : space->currentScene->entities) {
        std::string uniqueLabel = entity->getComponent<Transform>()->name + "##" + std::to_string(index);
        if (ImGui::Selectable(uniqueLabel.c_str(), selectedEntity == entity)) {
          selectedEntity = entity;
        }
        index++;
      }
    }
  }
  ImGui::End();
}

void EditorGui::displayProject() const {
  if (ImGui::Begin("Project")) {
    if (space) {
      // TODO: Render the project folder.
    }
  }
  ImGui::End();
}

void EditorGui::displayRender() const {
  if (ImGui::Begin("Render")) {
    if (space && space->currentScene) {
      const ImVec2 window_size = ImGui::GetContentRegionAvail();
      constexpr float aspect_ratio = 1920.0f / 1080.0f;
      const float window_aspect_ratio = window_size.x / window_size.y;

      ImVec2 image_size;
      if (window_aspect_ratio > aspect_ratio) {
        image_size = ImVec2(window_size.y * aspect_ratio, window_size.y);
      } else {
        image_size = ImVec2(window_size.x, window_size.x / aspect_ratio);
      }

      ImGui::Image(reinterpret_cast<void *>(renderTexture), image_size);
    }
  }
  ImGui::End();
}

void EditorGui::displayConsole() {
  if (ImGui::Begin("Console")) {
    ImGui::Text("Search: ");
    ImGui::SameLine();
    ImGui::InputText("##log_search", &Logger::filter.keyword);
    ImGui::SeparatorText("Logs");
    for (const auto& log : Logger::getLogEntries()) {
      std::string text = log.toString();
      ImGui::Text("%s", text.c_str());
    }
  }
  ImGui::End();
}

void EditorGui::displayScene() {
  if (showScene) {
    ImGui::Begin("Scene");
    if (space && space->currentScene) {
      sceneHovered = ImGui::IsWindowHovered();

      const ImVec2 window_size = ImGui::GetContentRegionAvail();
      constexpr float aspect_ratio = 1920.0f / 1080.0f;
      const float window_aspect_ratio = window_size.x / window_size.y;

      ImVec2 image_size;
      if (window_aspect_ratio > aspect_ratio) {
        image_size = ImVec2(window_size.y * aspect_ratio, window_size.y);
      } else {
        image_size = ImVec2(window_size.x, window_size.x / aspect_ratio);
      }

      ImGui::Image(reinterpret_cast<void *>(sceneTexture), image_size);
    }
    ImGui::End();
  }
}

void EditorGui::displayResourceManager() {
  if (ImGui::Begin("Resource Manager")) {
    if (ImGui::BeginTable("ResourceTable", 5, ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg | ImGuiTableFlags_Resizable)) {
      ImGui::TableSetupColumn("Type", ImGuiTableColumnFlags_WidthFixed);
      ImGui::TableSetupColumn("Path", ImGuiTableColumnFlags_WidthStretch);
      ImGui::TableSetupColumn("Alive", ImGuiTableColumnFlags_WidthFixed);
      ImGui::TableSetupColumn("Users Count", ImGuiTableColumnFlags_WidthFixed);
      ImGui::TableSetupColumn("Users", ImGuiTableColumnFlags_WidthFixed);
      ImGui::TableHeadersRow();
      for (const auto& [typeIndex, resMap] : ResourceManager::getResources()) {
        const std::string typeName = typeIndex.name();
        for (const auto& [path, resPtr] : resMap) {
          ImGui::TableNextRow();
          ImGui::TableSetColumnIndex(0);
          ImGui::TextUnformatted(resPtr->getTypeName());
          ImGui::TableSetColumnIndex(1);
          ImGui::TextUnformatted(path.c_str());
          ImGui::TableSetColumnIndex(2);
          const float alive = resPtr->getTimeSinceLoad().count();
          ImGui::Text("%.2fs", alive);
          ImGui::TableSetColumnIndex(3);
          const auto& userMap = ResourceManager::getResourceUsers();
          const size_t userCount = userMap.contains(path) ? userMap.at(path).size() : 0;
          ImGui::Text("%zu", userCount);
          ImGui::TableSetColumnIndex(4);
          if (userCount == 0) {
            ImGui::TextDisabled("None");
          } else {
            for (const auto& weak : userMap.at(path)) {
              if (auto user = weak.lock()) {
                auto* user_ptr = user.get();
                ImGui::Text("- %s", typeid(*user_ptr).name());
              } else {
                ImGui::TextDisabled("- expired");
              }
            }
          }
        }
      }
      ImGui::EndTable();
    }
    ImGui::End();
  }
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