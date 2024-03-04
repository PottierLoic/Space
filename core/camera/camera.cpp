#include "Camera.hpp"

Camera::Camera(glm::vec3 position, glm::vec3 up, float yaw, float pitch) {
  front = glm::vec3(0.0f, 0.0f, -1.0f);
  movementSpeed = SPEED;
  mouseSensitivity = SENSITIVITY;
  zoom = ZOOM;
  this->position = position;
  worldUp = up;
  this->yaw = yaw;
  this->pitch = pitch;
  updateCameraVectors();
}

Camera::Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch) {
  front = glm::vec3(0.0f, 0.0f, -1.0f);
  movementSpeed = SPEED;
  mouseSensitivity = SENSITIVITY;
  zoom = ZOOM;
  position = glm::vec3(posX, posY, posZ);
  worldUp = glm::vec3(upX, upY, upZ);
  this->yaw = yaw;
  this->pitch = pitch;
  updateCameraVectors();
}

glm::mat4 Camera::getViewMatrix() {
  return glm::lookAt(position, position + front, up);
}

void Camera::processKeyboard(CameraMovement direction, float deltaTime) {
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

void Camera::processMouseMovement(float xoffset, float yoffset, bool constrainPitch) {
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

void Camera::processMouseScroll(float yoffset) {
  zoom -= yoffset;
  if (zoom < 1.0f ) { zoom = 1.0f; }
  if (zoom > 45.0f ) { zoom = 45.0f; }
}

void Camera::updateCameraVectors() {
  glm::vec3 tmpFront;
  tmpFront.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
  tmpFront.y = sin(glm::radians(pitch));
  tmpFront.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
  front = glm::normalize(tmpFront);
  right = glm::normalize(glm::cross(front, worldUp));
  up = glm::normalize(glm::cross(right, front));
}
