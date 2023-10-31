#include "camera.hpp"
#include "vector2.hpp"

Camera::Camera() {
  this->position = Vector2(0, 0);
  this->size = Vector2(500, 500);
}

Camera::Camera(Vector2 position, Vector2 size) {
  this->position = position;
  this->size = size;
}

void Camera::movePosition(Vector2 position) {
  this->position += position;
}

void Camera::setPosition(Vector2 position) {
  this->position = position;
}

void Camera::setSize(Vector2 size) {
  this->size = size;
}
