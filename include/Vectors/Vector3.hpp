#pragma once

#include <cmath>

class Vector3 {
public:
  double x, y, z;

  Vector3();
  Vector3(double x, double y, double z);

  Vector3 operator+(const Vector3 &other);
  Vector3 operator-(const Vector3 &other);
  Vector3 operator*(const Vector3 &other);
  Vector3 operator/(const Vector3 &other);

  Vector3 operator+=(const Vector3 &other);
  Vector3 operator-=(const Vector3 &other);
  Vector3 operator*=(const Vector3 &other);
  Vector3 operator/=(const Vector3 &other);

  bool operator==(const Vector3 &other);
  bool operator!=(const Vector3 &other);

  double distance(Vector3 &other);
};