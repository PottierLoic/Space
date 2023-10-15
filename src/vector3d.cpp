#include "vector3d.h"

vector3d::vector3d() { x = y = z = 0; }
vector3d::vector3d(float p_x, float p_y, float p_z) { x = p_x; y = p_y; z = p_z; }

float vector3d::dotProduct(const vector3d &vec) {
  return x * vec.x + y * vec.y + z * vec.z;
}

vector3d vector3d::crossProduct(const vector3d &vec) {
  return vector3d(y * vec.z - z * vec.y, z * vec.x - x * vec.z, x * vec.y - y * vec.x);
}

float vector3d::length() {
  return sqrt(x * x + y * y + z * z);
}

void vector3d::normalize() {
  float len = length();
  if (len != 0) {
    x /= len;
    y /= len;
    z /= len;
  }
}

void vector3d::change(float p_x, float p_y, float p_z) {
  x = p_x;
  y = p_y;
  z = p_z;
}

void vector3d::change(vector3d &vec) {
  x = vec.x;
  y = vec.y;
  z = vec.z;
}

void vector3d::change(vector3d vec) {
  x = vec.x;
  y = vec.y;
  z = vec.z;
}

void vector3d::changeX(float p_x) { x = p_x; }
void vector3d::changeY(float p_y) { y = p_y; }
void vector3d::changeZ(float p_z) { z = p_z; }

vector3d vector3d::operator+(const vector3d &vec) { return vector3d(x + vec.x, y + vec.y, z + vec.z); }
vector3d vector3d::operator-(const vector3d &vec) { return vector3d(x - vec.x, y - vec.y, z - vec.z); }
vector3d vector3d::operator*(const float &nb) { return vector3d(x * nb, y * nb, z * nb); }
vector3d vector3d::operator/(const float &nb) {
  if (nb != 0) { return vector3d(x / nb, y / nb, z / nb); }
  return vector3d();
}

vector3d& vector3d::operator+= (const vector3d &vec) {
  x += vec.x;
  y += vec.y;
  z += vec.z;
  return *this;
}

vector3d& vector3d::operator-= (const vector3d &vec) {
  x -= vec.x;
  y -= vec.y;
  z -= vec.z;
  return *this;
}

vector3d& vector3d::operator*= (const float &nb) {
  x *= nb;
  y *= nb;
  z *= nb;
  return *this;
}

vector3d& vector3d::operator/= (const float &nb) {
  if (nb != 0) {
    x /= nb;
    y /= nb;
    z /= nb;
  }
  return *this;
}

bool vector3d::operator == (const vector3d &vec) { return (x == vec.x && y == vec.y && z == vec.z); }
bool vector3d::operator!= (const vector3d &vec) { return !(*this == vec); }

std::ostream& operator<<(std::ostream &out, const vector3d &vec) {
  out << vec.x << " " << vec.y << " " << vec.z << std::endl;
  return out;
}
