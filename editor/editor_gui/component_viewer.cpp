#include "editor_gui/editor_gui.hpp"

namespace SpaceEditor {

void EditorGui::initComponentViewers() {
  this->componentViewers[std::type_index(typeid(Transform))] = [](std::shared_ptr<Component> component) {
    auto transform = std::static_pointer_cast<Transform>(component);
    if (ImGui::CollapsingHeader("Transform")) {
      ImGui::Text("Name");
      ImGui::SameLine(100);
      ImGui::InputText("##transform.name", &transform->name);
      ImGui::PushItemWidth(75);
      ImGui::Text("Position");
      ImGui::SameLine(100);
      if (ImGui::InputFloat("##transform.position.x", &transform->position.x())) {}
      ImGui::SameLine(180);
      if (ImGui::InputFloat("##transform.position.y", &transform->position.y())) {}
      ImGui::SameLine(260);
      if (ImGui::InputFloat("##transform.position.z", &transform->position.z())) {}

      ImGui::Text("Rotation");
      ImGui::SameLine(100);
      if (ImGui::InputFloat("##transform.rotation.x", &transform->rotation.x())) {}
      ImGui::SameLine(180);
      if (ImGui::InputFloat("##transform.rotation.y", &transform->rotation.y())) {}
      ImGui::SameLine(260);
      if (ImGui::InputFloat("##transform.rotation.z", &transform->rotation.z())) {}

      ImGui::Text("Scale");
      ImGui::SameLine(100);
      if (ImGui::InputFloat("##transform.scale.x", &transform->scale.x())) {}
      ImGui::SameLine(180);
      if (ImGui::InputFloat("##transform.scale.y", &transform->scale.y())) {}
      ImGui::SameLine(260);
      if (ImGui::InputFloat("##transform.scale.z", &transform->scale.z())) {}
    }
  };

  this->componentViewers[std::type_index(typeid(Physic))] = [](std::shared_ptr<Component> component) {
    auto physic = std::static_pointer_cast<Physic>(component);
    if (ImGui::CollapsingHeader("Physic")) {
      ImGui::Text("Mass");
      ImGui::SameLine(100);
      ImGui::InputFloat("##physic_mass", &physic->mass);
      ImGui::Text("Drag");
      ImGui::SameLine(100);
      ImGui::InputFloat("##physic_drag", &physic->drag);
      ImGui::Text("Angular drag");
      ImGui::SameLine(100);
      ImGui::InputFloat("##physic_angular_drag", &physic->angularDrag);
      ImGui::Text("Gravity");
      ImGui::SameLine(100);
      ImGui::Checkbox("##physic_gravity", &physic->gravity);
    }
  };

  this->componentViewers[std::type_index(typeid(ModelRenderer))] = [](std::shared_ptr<Component> component) {
    auto modelRenderer = std::static_pointer_cast<ModelRenderer>(component);
    if (ImGui::CollapsingHeader("Component")) {
      ImGui::Text("Model");
      ImGui::SameLine(100);

      if (modelRenderer->model != nullptr) {
        ImGui::Text("%s", modelRenderer->model->directory.c_str());
      }
    }
  };

  this->componentViewers[std::type_index(typeid(Camera))] = [](std::shared_ptr<Component> component) {
    auto camera = std::static_pointer_cast<Camera>(component);
    if (ImGui::CollapsingHeader("Camera")) {
      ImGui::SetNextItemWidth(200);
      ImGui::ColorPicker4("Skybox color", (float*)&camera->skyboxColor);
    }
  };
}

}
