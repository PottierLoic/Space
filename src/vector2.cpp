#include "vector2.hpp"

Vector2::Vector2() {
  this->x = 0;
  this->y = 0;
}

Vector2::Vector2(float x, float y) {
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