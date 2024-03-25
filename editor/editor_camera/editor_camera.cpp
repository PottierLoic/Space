#include "editor_camera.hpp"

namespace SpaceEditor {

EditorCamera::EditorCamera(glm::vec3 position, glm::vec3 up, float yaw, float pitch) {
  front = glm::vec3(0.0f, 0.0f, -1.0f);
  movementSpeed = SPEED;
  mouseSensitivity = SENSITIVITY;
  zoom = ZOOM;
  position = position;
  worldUp = up;
  yaw = yaw;
  pitch = pitch;
  updateCameraVectors();
}

glm::mat4 EditorCamera::getViewMatrix() {
  return glm::lookAt(position, position + front, up);
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
  zoom -= yoffset;
  if (zoom < 1.0f ) { zoom = 1.0f; }
  if (zoom > 45.0f ) { zoom = 45.0f; }
}

void EditorCamera::updateCameraVectors() {
  glm::vec3 tmpFront;
  tmpFront.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
  tmpFront.y = sin(glm::radians(pitch));
  tmpFront.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
  front = glm::normalize(tmpFront);
  right = glm::normalize(glm::cross(front, worldUp));
  up = glm::normalize(glm::cross(right, front));
}

}
