#include "Components/Physic.hpp"

Physic::Physic() {
  this->mass = 1.0;
  this->drag = 0;
  this->angularDrag = 0;
  this->gravity = false;
}

Physic::~Physic() {}

void Physic::display() {
  if (ImGui::CollapsingHeader("Physic")) {
    ImGui::Text("Mass");
    ImGui::SameLine(100);
    ImGui::InputDouble("##physic_mass", &this->mass);
    ImGui::Text("Drag");
    ImGui::SameLine(100);
    ImGui::InputDouble("##physic_drag", &this->drag);
    ImGui::Text("Angular drag");
    ImGui::SameLine(100);
    ImGui::InputDouble("##physic_angular_drag", &this->angularDrag);
    ImGui::Text("Gravity");
    ImGui::SameLine(100);
    ImGui::Checkbox("##physic_gravity", &this->gravity);

  }
}
