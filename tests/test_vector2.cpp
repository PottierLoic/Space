#include "test.hpp"
#include "maths/vector.hpp"

using namespace SpaceEngine;

int testVector2() {
  Vec2f vec1(1.0f, 2.0f);
  constexpr Vec2f vec2(3.0f, 5.0f);

  // Vector/Vector addition
  custom_assert(vec1 + vec2 == Vec2f(4.0f, 7.0f), "Vec2f vector addition failed");

  // Vector/Scalar addition
  custom_assert(vec1 + 3 == Vec2f(4.0f, 5.0f), "Vec2f scalar addition failed")

  // Vector/Vector subtraction
  custom_assert(vec1 - vec2 == Vec2f(-2.0f, -3.0f), "Vec2f subtraction failed");

  // Vector/Scalar subtraction
  custom_assert(vec2 - 3 == Vec2f(0.0f, 2.0f), "Vec2f scalar subtraction failed")

  // Multiplication by a scalar
  custom_assert(vec1 * 2.0 == Vec2f(2.0f, 4.0f), "Vec2f scalar multiplication failed");

  // Division by a scalar
  custom_assert(vec1 / 2.0 == Vec2f(0.5f, 1.0f), "Vec2f scalar division failed");

  // += with a vector
  Vec2f vec3 = vec1;
  vec3 += vec2;
  custom_assert(vec3.x() == 4.0f && vec3.y() == 7.0f, "Vec2f += failed");

  // += with a scalar
  vec3 = vec1;
  vec3 += 2.0f;
  custom_assert(vec3.x() == 3.0f && vec3.y() == 4.0f, "Vec2f += scalar failed");

  // -= with a vector
  vec3 = vec1;
  vec3 -= vec2;
  custom_assert(vec3.x() == -2.0f && vec3.y() == -3.0f, "Vec2f -= failed");

  // -= with a scalar
  vec3 = vec1;
  vec3 -= 2.0f;
  custom_assert(vec3.x() == -1.0f && vec3.y() == 0.0f, "Vec2f -= scalar failed");

  // *= with a scalar
  vec3 = vec1;
  vec3 *= 2.0f;
  custom_assert(vec3.x() == 2.0f && vec3.y() == 4.0f, "Vec2f *= failed");

  // /= with a scalar
  vec3 = vec1;
  vec3 /= 2.0f;
  custom_assert(vec3.x() == 0.5f && vec3.y() == 1.0f, "Vec2f /= failed");

  // operator[]
  custom_assert(vec1[0] == 1.0f && vec1[1] == 2.0f, "Vec2f operator[] failed");

  // equality
  custom_assert(vec1 == Vec2f(1.0f, 2.0f), "Vec2f equality failed");

  // inequality
  custom_assert(vec1 != vec2, "Vec2f inequality failed");

  // extension
  const auto extendedVec = Vec3f(vec1, 3.0f);
  custom_assert(extendedVec == Vec3f(1.0f, 2.0f, 3.0f), "Vec2f to Vec3f extension failed");

  // truncation
  custom_assert(Vec2f(extendedVec) == Vec2f(1.0f, 2.0f), "Vec3f to Vec2f truncation failed");

  // dot product
  custom_assert(vec1.dot(vec2) == 13.0f, "Vec2f dot product failed");
  return 0;
}
