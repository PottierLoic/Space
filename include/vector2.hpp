#ifndef VECTOR2_H
#define VECTOR2_H

#include <cmath>

class Vector2 {
public:
  double x, y;

  Vector2();
  Vector2(double x, double y);

  Vector2 operator+(const Vector2 &other);
  Vector2 operator-(const Vector2 &other);
  Vector2 operator*(const Vector2 &other);
  Vector2 operator/(const Vector2 &other);
  Vector2 operator+=(const Vector2 &other);
  Vector2 operator-=(const Vector2 &other);
  Vector2 operator*=(const Vector2 &other);
  Vector2 operator/=(const Vector2 &other);
  bool operator==(const Vector2 &other);
  bool operator!=(const Vector2 &other);

  double distance(Vector2 &other);
};

#endif