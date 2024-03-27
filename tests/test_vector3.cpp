#include "test.hpp"
#include "maths/vector.hpp"

using namespace SpaceEngine;

int testVector3() {
  Vec3f vec1(1.0f, 2.0f, 3.0f);
  Vec3f vec2(4.0f, 5.0f, 6.0f);

  // Vector/Vector addition
  custom_assert(vec1 + vec2 == Vec3f(5.0f, 7.0f, 9.0f), "Vec3f vector addition failed");

  // Vector/Scalar addition
  custom_assert(vec1 + 3.0f == Vec3f(4.0f, 5.0f, 6.0f), "Vec3f scalar addition failed");

  // Vector/Vector subtraction
  custom_assert(vec1 - vec2 == Vec3f(-3.0f, -3.0f, -3.0f), "Vec3f subtraction failed");

  // Vector/Scalar subtraction
  custom_assert(vec2 - 3.0f == Vec3f(1.0f, 2.0f, 3.0f), "Vec3f scalar subtraction failed");

  // Multiplication by a scalar
  custom_assert(vec1 * 2.0f == Vec3f(2.0f, 4.0f, 6.0f), "Vec3f scalar multiplication failed");

  // Division by a scalar
  custom_assert(vec1 / 2.0f == Vec3f(0.5f, 1.0f, 1.5f), "Vec3f scalar division failed");

  // += with a vector
  Vec3f vec3 = vec1;
  vec3 += vec2;
  custom_assert(vec3 == Vec3f(5.0f, 7.0f, 9.0f), "Vec3f += failed");

  // += with a scalar
  vec3 = vec1;
  vec3 += 2.0f;
  custom_assert(vec3 == Vec3f(3.0f, 4.0f, 5.0f), "Vec3f += scalar failed");

  // -= with a vector
  vec3 = vec1;
  vec3 -= vec2;
  custom_assert(vec3 == Vec3f(-3.0f, -3.0f, -3.0f), "Vec3f -= failed");

  // -= with a scalar
  vec3 = vec1;
  vec3 -= 2.0f;
  custom_assert(vec3 == Vec3f(-1.0f, 0.0f, 1.0f), "Vec3f -= scalar failed");

  // *= with a scalar
  vec3 = vec1;
  vec3 *= 2.0f;
  custom_assert(vec3 == Vec3f(2.0f, 4.0f, 6.0f), "Vec3f *= failed");

  // /= with a scalar
  vec3 = vec1;
  vec3 /= 2.0f;
  custom_assert(vec3 == Vec3f(0.5f, 1.0f, 1.5f), "Vec3f /= failed");

  // operator[]
  custom_assert(vec1[0] == 1.0f && vec1[1] == 2.0f && vec1[2] == 3.0f, "Vec3f operator[] failed");

  // equality
  custom_assert(vec1 == Vec3f(1.0f, 2.0f, 3.0f), "Vec3f equality failed");

  // inequality
  custom_assert(vec1 != vec2, "Vec3f inequality failed");

   // extension
  Vec4f extendedVec = Vec4f(vec1, 4.0f);
  custom_assert(extendedVec == Vec4f(1.0f, 2.0f, 3.0f, 4.0f), "Vec3f to Vec4f extension failed");

  // truncation
  custom_assert(Vec3f(extendedVec) == Vec3f(1.0f, 2.0f, 3.0f), "Vec4f to Vec3f truncation failed");
  custom_assert(Vec2f(vec1) == Vec2f(1.0f, 2.0f), "Vec3f to Vec2f truncation failed");

  // dot product
  custom_assert(vec1.dot(vec2) == 32.0f, "Vec3f dot product failed");

  // Cross product (specific to Vec3f)
  Vec3f crossProduct = vec1.cross(vec2);
  custom_assert(crossProduct == Vec3f(-3.0f, 6.0f, -3.0f), "Vec3f cross product failed");
  return 0;
}
