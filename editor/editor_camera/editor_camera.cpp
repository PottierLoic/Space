#include "editor_camera.hpp"

namespace SpaceEditor {

EditorCamera::EditorCamera(glm::vec3 position, glm::vec3 up, float yaw, float pitch) {
  this->front = glm::vec3(0.0f, 0.0f, -1.0f);
  this->position = position;
  this->worldUp = up;
  this->yaw = yaw;
  this->pitch = pitch;
  updateCameraVectors();
}

void EditorCamera::processKeyboard(CameraMovement direction, float deltaTime) {
  float velocity = movementSpeed * deltaTime;
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

void EditorCamera::processMouseMovement(float xoffset, float yoffset, bool constrainPitch) {
  xoffset *= mouseSensitivity;
  yoffset *= mouseSensitivity;

  yaw += xoffset;
  pitch += yoffset;

  if (constrainPitch) {
    if (pitch > 89.0f) { pitch = 89.0f; }
    if (pitch < -89.0f) { pitch = -89.0f; }
  }

  updateCameraVectors();
}

void EditorCamera::processMouseScroll(float yoffset) {
  fieldOfView -= yoffset;
  if (fieldOfView < 1.0f ) { fieldOfView = 1.0f; }
  if (fieldOfView > 179.0f ) { fieldOfView = 179.0f; }
}

glm::mat4 EditorCamera::getEditorViewMatrix() {
  glm::vec3 lookTarget = position + front;
  return glm::lookAt(position, lookTarget, up);
}

glm::mat4 EditorCamera::getEditorProjectionMatrix() {
  if (projectionType == ProjectionType::PERSPECTIVE) {
    glm::mat4 projection = glm::perspective(glm::radians(fieldOfView), aspectRatio, nearPlane, farPlane);
    projection[1][1] *= -1; // Flip Y for Vulkan-style coordinate system
    return projection;
  } else {
    float width = orthographicSize * aspectRatio;
    float height = orthographicSize;
    glm::mat4 projection = glm::ortho(-width, width, -height, height, nearPlane, farPlane);
    projection[1][1] *= -1; // Flip Y for Vulkan-style coordinate system
    return projection;
  }
}

}