#include "Vectors/Vector3.hpp"

Vector3::Vector3() {
  this->x = 0;
  this->y = 0;
  this->z = 0;
}

Vector3::Vector3(double x, double y, double z) {
  this->x = x;
  this->y = y;
  this->z = z;
}

Vector3 Vector3::operator+(const Vector3 &other) {
  return Vector3(this->x + other.x, this->y + other.y, this->z + other.z);
}

Vector3 Vector3::operator-(const Vector3 &other) {
  return Vector3(this->x - other.x, this->y - other.y, this->z - other.z);
}

Vector3 Vector3::operator*(const Vector3 &other) {
  return Vector3(this->x * other.x, this->y * other.y, this->z * other.z);
}

Vector3 Vector3::operator/(const Vector3 &other) {
  return Vector3(this->x / other.x, this->y / other.y, this->z / other.z);
}

Vector3 Vector3::operator+=(const Vector3 &other) {
  this->x += other.x;
  this->y += other.y;
  this->z += other.z;
  return *this;
}

Vector3 Vector3::operator-=(const Vector3 &other) {
  this->x -= other.x;
  this->y -= other.y;
  this->z -= other.z;
  return *this;
}

Vector3 Vector3::operator*=(const Vector3 &other) {
  this->x *= other.x;
  this->y *= other.y;
  this->z *= other.z;
  return *this;
}

Vector3 Vector3::operator/=(const Vector3 &other) {
  this->x /= other.x;
  this->y /= other.y;
  this->z /= other.z;
  return *this;
}

bool Vector3::operator==(const Vector3 &other) {
  return this->x == other.x && this->y == other.y && this->z == other.z;
}

bool Vector3::operator!=(const Vector3 &other) {
  return this->x != other.x || this->y != other.y || this->z != other.z;
}

double Vector3::distance(const Vector3 &other) {
  return sqrt(pow(this->x - other.x, 2) +
              pow(this->y - other.y, 2) +
              pow(this->z - other.z, 2));
}
