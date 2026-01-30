#include "editor_camera.hpp"

namespace SpaceEditor {

EditorCamera::EditorCamera() = default;

void EditorCamera::processKeyboard(const CameraMovement direction, const float deltaTime) {
  const float velocity = movementSpeed * deltaTime;
  switch (direction) {
    case FORWARD:
      position += front * velocity;
      break;
    case BACKWARD:
      position -= front * velocity;
      break;
    case LEFT:
      position -= right * velocity;
      break;
    case RIGHT:
      position += right * velocity;
      break;
  }
}

void EditorCamera::processMouseMovement(float xOffset, float yOffset, const bool constrainPitch) {
  xOffset *= mouseSensitivity;
  yOffset *= mouseSensitivity;

  yaw += xOffset;
  pitch += yOffset;

  if (constrainPitch) {
    if (pitch > 89.0f) {
      pitch = 89.0f;
    }
    if (pitch < -89.0f) {
      pitch = -89.0f;
    }
  }

  updateCameraVectors();
}

void EditorCamera::processMouseScroll(const float yOffset) {
  fieldOfView -= yOffset;
  if (fieldOfView < 1.0f) {
    fieldOfView = 1.0f;
  }
  if (fieldOfView > 179.0f) {
    fieldOfView = 179.0f;
  }
}

glm::mat4 EditorCamera::getEditorViewMatrix() const {
  const glm::vec3 lookTarget = position + front;
  return glm::lookAt(position, lookTarget, up);
}

glm::mat4 EditorCamera::getEditorProjectionMatrix() const {
  if (projectionType == ProjectionType::PERSPECTIVE) {
    glm::mat4 projection = glm::perspective(glm::radians(fieldOfView),
                                            aspectRatio,
                                            nearPlane,
                                            farPlane);
    projection[1][1] *= -1;
    return projection;
  }
  const float width = orthographicSize * aspectRatio;
  const float height = orthographicSize;
  glm::mat4 projection = glm::ortho(-width, width, -height, height, nearPlane, farPlane);
  projection[1][1] *= -1;
  return projection;
}

}  // namespace SpaceEditor