#include "test.hpp"
#include "maths/vector.hpp"

using namespace SpaceEngine;

int testVector4() {
  Vec4f vec1(1.0f, 2.0f, 3.0f, 4.0f);
  Vec4f vec2(5.0f, 6.0f, 7.0f, 8.0f);

  // Vector/Vector addition
  custom_assert(vec1 + vec2 == Vec4f(6.0f, 8.0f, 10.0f, 12.0f), "Vec4f vector addition failed");

  // Vector/Scalar addition
  custom_assert(vec1 + 3.0f == Vec4f(4.0f, 5.0f, 6.0f, 7.0f), "Vec4f scalar addition failed");

  // Vector/Vector subtraction
  custom_assert(vec1 - vec2 == Vec4f(-4.0f, -4.0f, -4.0f, -4.0f), "Vec4f subtraction failed");

  // Vector/Scalar subtraction
  custom_assert(vec2 - 3.0f == Vec4f(2.0f, 3.0f, 4.0f, 5.0f), "Vec4f scalar subtraction failed");

  // Multiplication by a scalar
  custom_assert(vec1 * 2.0f == Vec4f(2.0f, 4.0f, 6.0f, 8.0f), "Vec4f scalar multiplication failed");

  // Division by a scalar
  custom_assert(vec1 / 2.0f == Vec4f(0.5f, 1.0f, 1.5f, 2.0f), "Vec4f scalar division failed");

  // += with a vector
  Vec4f vec3 = vec1;
  vec3 += vec2;
  custom_assert(vec3 == Vec4f(6.0f, 8.0f, 10.0f, 12.0f), "Vec4f += failed");

  // += with a scalar
  vec3 = vec1;
  vec3 += 2.0f;
  custom_assert(vec3 == Vec4f(3.0f, 4.0f, 5.0f, 6.0f), "Vec4f += scalar failed");

  // -= with a vector
  vec3 = vec1;
  vec3 -= vec2;
  custom_assert(vec3 == Vec4f(-4.0f, -4.0f, -4.0f, -4.0f), "Vec4f -= failed");

  // -= with a scalar
  vec3 = vec1;
  vec3 -= 2.0f;
  custom_assert(vec3 == Vec4f(-1.0f, 0.0f, 1.0f, 2.0f), "Vec4f -= scalar failed");

  // *= with a scalar
  vec3 = vec1;
  vec3 *= 2.0f;
  custom_assert(vec3 == Vec4f(2.0f, 4.0f, 6.0f, 8.0f), "Vec4f *= failed");

  // /= with a scalar
  vec3 = vec1;
  vec3 /= 2.0f;
  custom_assert(vec3 == Vec4f(0.5f, 1.0f, 1.5f, 2.0f), "Vec4f /= failed");

  // operator[]
  custom_assert(vec1[0] == 1.0f && vec1[1] == 2.0f && vec1[2] == 3.0f && vec1[3] == 4.0f, "Vec4f operator[] failed");

  // equality
  custom_assert(vec1 == Vec4f(1.0f, 2.0f, 3.0f, 4.0f), "Vec4f equality failed");

  // inequality
  custom_assert(vec1 != vec2, "Vec4f inequality failed");

  // truncation to Vec3f
  custom_assert(Vec3f(vec1) == Vec3f(1.0f, 2.0f,3.0f), "Vec4f to Vec3f truncation failed");

  // dot product
  custom_assert(vec1.dot(vec2) == 70.0f, "Vec4f dot product failed");
  return 0;
}