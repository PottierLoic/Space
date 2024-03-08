#include "component/camera.hpp"
#include "entity/entity.hpp" // Can only be done here to avoid circular includes.

namespace SpaceEngine {

Camera::Camera(Entity* owner) : Component(owner) {
  front = glm::vec3(0.0f, 0.0f, -1.0f);
  zoom = 45.0f;
  worldUp = glm::vec3(0.0f, 1.0f, 0.0f);
  yaw = -90.0f;
  pitch = 0.0f;
  updateCameraVectors();
}

Camera::~Camera() {}

glm::mat4 Camera::getViewMatrix() {
  Transform* tf = this->owner->getComponent<Transform>();
  return glm::lookAt(glm::vec3(tf->position.x, tf->position.y, tf->position.z), position + front, up);
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

}
