#include "test.hpp"
#include "vector/vector.hpp"

using SpaceEngine::Vec2f; // Using the float specialization for 2D vectors

int testVector2() {
  Vec2f vec1(1.0f, 2.0f);
  Vec2f vec2(3.0f, 5.0f);

  // Test addition
  auto add_result = vec1 + vec2;
  custom_assert(add_result.x() == 4.0f && add_result.y() == 7.0f, "Vec2f addition failed");

  // Test subtraction
  auto sub_result = vec1 - vec2;
  custom_assert(sub_result.x() == -2.0f && sub_result.y() == -3.0f, "Vec2f subtraction failed");

  // Test multiplication by a scalar
  auto mul_result_scalar = vec1 * 2.0f;
  custom_assert(mul_result_scalar.x() == 2.0f && mul_result_scalar.y() == 4.0f, "Vec2f scalar multiplication failed");

  // Test division by a scalar
  auto div_result_scalar = vec1 / 2.0f;
  custom_assert(div_result_scalar.x() == 0.5f && div_result_scalar.y() == 1.0f, "Vec2f scalar division failed");

  // Test += with a vector
  Vec2f vec3 = vec1;
  vec3 += vec2;
  custom_assert(vec3.x() == 4.0f && vec3.y() == 7.0f, "Vec2f += failed");

  // Test -= with a vector
  vec3 = vec1;
  vec3 -= vec2;
  custom_assert(vec3.x() == -2.0f && vec3.y() == -3.0f, "Vec2f -= failed");

  // Test *= with a scalar
  vec3 = vec1;
  vec3 *= 2.0f;
  custom_assert(vec3.x() == 2.0f && vec3.y() == 4.0f, "Vec2f *= failed");

  // Test /= with a scalar
  vec3 = vec1;
  vec3 /= 2.0f;
  custom_assert(vec3.x() == 0.5f && vec3.y() == 1.0f, "Vec2f /= failed");

  // Test operator[]
  custom_assert(vec1[0] == 1.0f && vec1[1] == 2.0f, "Vec2f operator[] failed");

  // Test equality
  Vec2f vec4(1.0f, 2.0f);
  custom_assert(vec1 == vec4, "Vec2f equality failed");

  // Test inequality
  custom_assert(vec1 != vec2, "Vec2f inequality failed");
  return 0;
}
