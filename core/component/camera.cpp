#include "component/camera.hpp"

namespace SpaceEngine {

Camera::Camera() {
  front = glm::vec3(0.0f, 0.0f, -1.0f);
  worldUp = glm::vec3(0.0f, 1.0f, 0.0f);
  yaw = -90.0f;
  pitch = 0.0f;
  skyboxColor = ImVec4(0.1f, 0.1f, 0.1f, 1.0f);
  updateCameraVectors();
}

glm::mat4 Camera::getViewMatrix(const World& world, Entity e) const {
  const auto& tf = world.get_component<Transform>(e);
  const auto positionVec = glm::vec3(tf.position.x(), tf.position.y(), tf.position.z());
  const glm::vec3 lookTarget = positionVec + front;
  return glm::lookAt(positionVec, lookTarget, up);
}

glm::mat4 Camera::getProjectionMatrix() const {
  if (projectionType == ProjectionType::PERSPECTIVE) {
    glm::mat4 projection = glm::perspective(glm::radians(fieldOfView),
                                            aspectRatio,
                                            nearPlane,
                                            farPlane);
    projection[1][1] *= -1;
    return projection;
  } else {
    const float width = orthographicSize * aspectRatio;
    const float height = orthographicSize;
    glm::mat4 projection = glm::ortho(-width, width, -height, height, nearPlane, farPlane);
    projection[1][1] *= -1;
    return projection;
  }
}

void Camera::updateCameraVectors() {
  front = glm::normalize(glm::vec3(cos(glm::radians(yaw)) * cos(glm::radians(pitch)),
                                   sin(glm::radians(pitch)),
                                   sin(glm::radians(yaw)) * cos(glm::radians(pitch))));
  right = glm::normalize(glm::cross(front, worldUp));
  up = glm::normalize(glm::cross(right, front));
}

}  // namespace SpaceEngine
