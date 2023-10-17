#ifndef VECTOR2_H
#define VECTOR2_H

class Vector2 {
public:
  float x, y;

  Vector2();
  Vector2(float x, float y);

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
};

#endif