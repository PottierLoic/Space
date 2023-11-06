#include "camera.hpp"
#include "vector3.hpp"

Camera::Camera() {
  this->position = Vector3(0, 0, 0);
  this->width = 0;
  this->height = 0;
}

Camera::Camera(Vector3 position, double width, double height) {
  this->position = position;
  this->width = width;
  this->height = height;
}

void Camera::movePosition(Vector3 position) {
  this->position += position;
}

void Camera::setPosition(Vector3 position) {
  this->position = position;
}

void Camera::setSize(double width, double height) {
  this->width = width;
  this->height = height;
}
