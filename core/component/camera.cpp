#include "component/camera.hpp"
#include "entity/entity.hpp" // Can only be done here to avoid circular includes.

namespace SpaceEngine {

Camera::Camera() {
  front = glm::vec3(0.0f, 0.0f, -1.0f);
  worldUp = glm::vec3(0.0f, 1.0f, 0.0f);
  yaw = -90.0f;
  pitch = 0.0f;
  skyboxColor = ImVec4(0.1f, 0.1f, 0.1f, 1.0f);
  updateCameraVectors();
}

glm::mat4 Camera::getViewMatrix() {
  auto lockedOwner = owner.lock();
  if (!lockedOwner) {
    return glm::mat4(1.0f);
  } else {
    auto tf = lockedOwner->getComponent<Transform>();
    glm::vec3 positionVec = glm::vec3(tf->position.x(), tf->position.y(), tf->position.z());
    glm::vec3 lookTarget = positionVec + front;
    return glm::lookAt(positionVec, lookTarget, up);
  }
}

glm::mat4 Camera::getProjectionMatrix() {
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

void Camera::updateCameraVectors() {
  front = glm::normalize(glm::vec3(
    cos(glm::radians(yaw)) * cos(glm::radians(pitch)),
    sin(glm::radians(pitch)),
    sin(glm::radians(yaw)) * cos(glm::radians(pitch))
  ));
  right = glm::normalize(glm::cross(front, worldUp));
  up = glm::normalize(glm::cross(right, front));
}

}
