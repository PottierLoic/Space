#pragma once

#include "../imgui/imgui_impl_opengl3.h"
#include "component/transform.hpp"
#include "ecs/entity.hpp"
#include "ecs/world.hpp"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

namespace SpaceEngine {

struct Camera {
  enum class ProjectionType { PERSPECTIVE, ORTHOGRAPHIC };

  glm::vec3 front{};
  glm::vec3 up{};
  glm::vec3 right{};
  glm::vec3 worldUp{};
  float yaw;
  float pitch;

  ProjectionType projectionType = ProjectionType::PERSPECTIVE;
  float fieldOfView = 45.0f;
  float aspectRatio = 16.0f / 9.0f;
  float nearPlane = 0.1f;
  float farPlane = 100.0f;

  float orthographicSize = 5.0f;

  ImVec4 skyboxColor;

  Camera();
  [[nodiscard]] glm::mat4 getViewMatrix(const World& world, Entity e) const;
  [[nodiscard]] glm::mat4 getProjectionMatrix() const;
  void updateCameraVectors();
};

}  // namespace SpaceEngine
