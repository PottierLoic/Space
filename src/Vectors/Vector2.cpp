#include "Vectors/Vector2.hpp"

Vector2::Vector2() {
  this->x = 0;
  this->y = 0;
}

Vector2::Vector2(double x, double y) {
  this->x = x;
  this->y = y;
}

Vector2 Vector2::operator+(const Vector2 &other) {
  return Vector2(this->x + other.x, this->y + other.y);
}

Vector2 Vector2::operator-(const Vector2 &other) {
  return Vector2(this->x - other.x, this->y - other.y);
}

Vector2 Vector2::operator*(const Vector2 &other) {
  return Vector2(this->x * other.x, this->y * other.y);
}

Vector2 Vector2::operator/(const Vector2 &other) {
  return Vector2(this->x / other.x, this->y / other.y);
}

Vector2 Vector2::operator+=(const Vector2 &other) {
  this->x += other.x;
  this->y += other.y;
  return *this;
}

Vector2 Vector2::operator-=(const Vector2 &other) {
  this->x -= other.x;
  this->y -= other.y;
  return *this;
}

Vector2 Vector2::operator*=(const Vector2 &other) {
  this->x *= other.x;
  this->y *= other.y;
  return *this;
}

Vector2 Vector2::operator/=(const Vector2 &other) {
  this->x /= other.x;
  this->y /= other.y;
  return *this;
}

bool Vector2::operator==(const Vector2 &other) {
  return this->x == other.x && this->y == other.y;
}

bool Vector2::operator!=(const Vector2 &other) {
  return this->x != other.x || this->y != other.y;
}

double Vector2::distance(Vector2 &other) {
  return std::sqrt(std::pow(this->x - other.x, 2) + pow(this->y - other.y, 2));
}
