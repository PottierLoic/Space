#include "editor_gui/editor_gui.hpp"

namespace SpaceEditor {

void EditorGui::initComponentViewers() {
  this->componentViewers[std::type_index(typeid(Transform))] = [](const std::shared_ptr<Component>& component) {
    const auto transform = std::static_pointer_cast<Transform>(component);
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

  this->componentViewers[std::type_index(typeid(Physic))] = [](const std::shared_ptr<Component>& component) {
    const auto physic = std::static_pointer_cast<Physic>(component);
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

  this->componentViewers[std::type_index(typeid(ModelRenderer))] = [](const std::shared_ptr<Component>& component) {
    const auto modelRenderer = std::static_pointer_cast<ModelRenderer>(component);
    if (ImGui::CollapsingHeader("Model Renderer")) {
      ImGui::Text("Model path");
      ImGui::SameLine();
      ImGui::InputText("##model_renderer.path", &modelRenderer->path);
      ImGui::SameLine();
      if (ImGui::Button("Load Model")) {
        modelRenderer->setModel();
      }
    }
  };

  this->componentViewers[std::type_index(typeid(Camera))] = [](const std::shared_ptr<Component>& component) {
    const auto camera = std::static_pointer_cast<Camera>(component);
    if (ImGui::CollapsingHeader("Camera")) {
      // Projection Type
      ImGui::Text("Projection Type");
      ImGui::SameLine(100);
      const char* projectionTypes[] = { "Perspective", "Orthographic" };
      int currentType = static_cast<int>(camera->projectionType);
      if (ImGui::Combo("##camera.projectionType", &currentType, projectionTypes, IM_ARRAYSIZE(projectionTypes))) {
        camera->projectionType = static_cast<Camera::ProjectionType>(currentType);
      }

      // Common projection settings
      ImGui::Text("Aspect Ratio");
      ImGui::SameLine(100);
      ImGui::InputFloat("##camera.aspectRatio", &camera->aspectRatio, 0.1f, 1.0f, "%.2f");

      ImGui::Text("Near Plane");
      ImGui::SameLine(100);
      ImGui::InputFloat("##camera.nearPlane", &camera->nearPlane, 0.1f, 1.0f, "%.2f");

      ImGui::Text("Far Plane");
      ImGui::SameLine(100);
      ImGui::InputFloat("##camera.farPlane", &camera->farPlane, 1.0f, 10.0f, "%.2f");

      // Perspective-specific settings
      if (camera->projectionType == Camera::ProjectionType::PERSPECTIVE) {
        ImGui::Text("Field of View");
        ImGui::SameLine(100);
        ImGui::SliderFloat("##camera.fieldOfView", &camera->fieldOfView, 1.0f, 179.0f, "%.1f");
      }
      // Orthographic-specific settings
      else {
        ImGui::Text("Orthographic Size");
        ImGui::SameLine(100);
        ImGui::InputFloat("##camera.orthographicSize", &camera->orthographicSize, 0.1f, 1.0f, "%.2f");
      }

      // Camera orientation
      ImGui::Separator();
      ImGui::Text("Orientation");
      ImGui::Text("Yaw");
      ImGui::SameLine(100);
      if (ImGui::SliderFloat("##camera.yaw", &camera->yaw, -180.0f, 180.0f, "%.1f")) {
        camera->updateCameraVectors();
      }

      ImGui::Text("Pitch");
      ImGui::SameLine(100);
      if (ImGui::SliderFloat("##camera.pitch", &camera->pitch, -89.0f, 89.0f, "%.1f")) {
        camera->updateCameraVectors();
      }

      // Visual settings
      ImGui::Separator();
      ImGui::SetNextItemWidth(200);
      ImGui::Text("Visual Settings");
      ImGui::ColorPicker4("Skybox color", reinterpret_cast<float *>(&camera->skyboxColor));
    }
  };
}

}
