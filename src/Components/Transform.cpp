#include "Components/Transform.hpp"

Transform::Transform(std::string name) {
  this->name = name;
  this->position = Vector3();
}

Transform::~Transform() {}

void Transform::display() {
  if (ImGui::CollapsingHeader("Transform")) {
    ImGui::Text("Name");
    ImGui::SameLine(100);
    ImGui::InputText("##transform.name", &this->name);
    ImGui::PushItemWidth(75);
    ImGui::Text("Position");
    ImGui::SameLine(100);
    if (ImGui::InputDouble("##transform.position.x", &this->position.x)) {}
    ImGui::SameLine(180);
    if (ImGui::InputDouble("##transform.position.y", &this->position.y)) {}
    ImGui::SameLine(260);
    if (ImGui::InputDouble("##transform.position.z", &this->position.z)) {}

    ImGui::Text("Rotation");
    ImGui::SameLine(100);
    if (ImGui::InputDouble("##transform.rotation.x", &this->rotation.x)) {}
    ImGui::SameLine(180);
    if (ImGui::InputDouble("##transform.rotation.y", &this->rotation.y)) {}
    ImGui::SameLine(260);
    if (ImGui::InputDouble("##transform.rotation.z", &this->rotation.z)) {}

    ImGui::Text("Scale");
    ImGui::SameLine(100);
    if (ImGui::InputDouble("##transform.scale.x", &this->scale.x)) {}
    ImGui::SameLine(180);
    if (ImGui::InputDouble("##transform.scale.y", &this->scale.y)) {}
    ImGui::SameLine(260);
    if (ImGui::InputDouble("##transform.scale.z", &this->scale.z)) {}
  }
}
