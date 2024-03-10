#include "menu.hpp"

namespace SpaceEditor {

void Menu::initComponentViewers() {
  this->componentViewers[std::type_index(typeid(Transform))] = [](Component* component) {
    auto* transform = static_cast<Transform*>(component);
    if (ImGui::CollapsingHeader("Transform")) {
      ImGui::Text("Name");
      ImGui::SameLine(100);
      ImGui::InputText("##transform.name", &transform->name);
      ImGui::PushItemWidth(75);
      ImGui::Text("Position");
      ImGui::SameLine(100);
      if (ImGui::InputDouble("##transform.position.x", &transform->position.x)) {}
      ImGui::SameLine(180);
      if (ImGui::InputDouble("##transform.position.y", &transform->position.y)) {}
      ImGui::SameLine(260);
      if (ImGui::InputDouble("##transform.position.z", &transform->position.z)) {}

      ImGui::Text("Rotation");
      ImGui::SameLine(100);
      if (ImGui::InputDouble("##transform.rotation.x", &transform->rotation.x)) {}
      ImGui::SameLine(180);
      if (ImGui::InputDouble("##transform.rotation.y", &transform->rotation.y)) {}
      ImGui::SameLine(260);
      if (ImGui::InputDouble("##transform.rotation.z", &transform->rotation.z)) {}

      ImGui::Text("Scale");
      ImGui::SameLine(100);
      if (ImGui::InputDouble("##transform.scale.x", &transform->scale.x)) {}
      ImGui::SameLine(180);
      if (ImGui::InputDouble("##transform.scale.y", &transform->scale.y)) {}
      ImGui::SameLine(260);
      if (ImGui::InputDouble("##transform.scale.z", &transform->scale.z)) {}
    }
  };

  this->componentViewers[std::type_index(typeid(Physic))] = [](Component* component) {
    auto* physic = static_cast<Physic*>(component);
    if (ImGui::CollapsingHeader("Physic")) {
      ImGui::Text("Mass");
      ImGui::SameLine(100);
      ImGui::InputDouble("##physic_mass", &physic->mass);
      ImGui::Text("Drag");
      ImGui::SameLine(100);
      ImGui::InputDouble("##physic_drag", &physic->drag);
      ImGui::Text("Angular drag");
      ImGui::SameLine(100);
      ImGui::InputDouble("##physic_angular_drag", &physic->angularDrag);
      ImGui::Text("Gravity");
      ImGui::SameLine(100);
      ImGui::Checkbox("##physic_gravity", &physic->gravity);
    }
  };

  this->componentViewers[std::type_index(typeid(ModelRenderer))] = [](Component* component) {
    auto* modelRenderer = static_cast<ModelRenderer*>(component);
    if (ImGui::CollapsingHeader("Component")) {
      ImGui::Text("Model");
      ImGui::SameLine(100);

      if (modelRenderer->model != nullptr) {
        ImGui::Text("%s", modelRenderer->model->directory.c_str());
      }
    }
  };
}

}
