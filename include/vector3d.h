#ifndef VECTOR3D_H
#define VECTOR3D_H
#include <iostream>
#include <cmath>

class vector3d {
public:
  float x, y, z;
  vector3d();

  vector3d(float x, float y, float z);
  ~vector3d(){};
  float dotProduct(const vector3d &vec);
  vector3d crossProduct(const vector3d &vec);
  float length();
  void change(float x, float y, float z);
  void change(vector3d &vec);
  void change(vector3d vec);
  void changeX(float x);
  void changeY(float y);
  void changeZ(float z);
  void normalize();
  vector3d operator+(const vector3d &vec);
  vector3d operator-(const vector3d &vec);
  vector3d operator*(const float &nb);
  vector3d operator/(const float &nb);
  vector3d& operator+=(const vector3d &vec);
  vector3d& operator-=(const vector3d &vec);
  vector3d& operator*=(const float &nb);
  vector3d& operator/=(const float &nb);
  bool operator==(const vector3d &vec);
  bool operator!=(const vector3d &vec);
  friend std::ostream& operator<<(std::ostream &out, const vector3d &vec);
};

#endif 