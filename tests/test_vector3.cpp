#include "test.hpp"
#include "maths/vector.hpp"

using SpaceEngine::Vec3f;

int testVector3() {
  Vec3f vec1(1.0f, 2.0f, 3.0f);
  Vec3f vec2(4.0f, 5.0f, 6.0f);

  // Test addition
  auto add_result = vec1 + vec2;
  custom_assert(add_result.x() == 5.0f && add_result.y() == 7.0f && add_result.z() == 9.0f, "Vec3f addition failed");

  // Test subtraction
  auto sub_result = vec1 - vec2;
  custom_assert(sub_result.x() == -3.0f && sub_result.y() == -3.0f && sub_result.z() == -3.0f, "Vec3f subtraction failed");

  // Test multiplication by a scalar
  auto mul_result_scalar = vec1 * 2.0f;
  custom_assert(mul_result_scalar.x() == 2.0f && mul_result_scalar.y() == 4.0f && mul_result_scalar.z() == 6.0f, "Vec3f scalar multiplication failed");

  // Test division by a scalar
  auto div_result_scalar = vec1 / 2.0f;
  custom_assert(div_result_scalar.x() == 0.5f && div_result_scalar.y() == 1.0f && div_result_scalar.z() == 1.5f, "Vec3f scalar division failed");

  // Test += with a vector
  Vec3f vec3 = vec1;
  vec3 += vec2;
  custom_assert(vec3.x() == 5.0f && vec3.y() == 7.0f && vec3.z() == 9.0f, "Vec3f += failed");

  // Test -= with a vector
  vec3 = vec1;
  vec3 -= vec2;
  custom_assert(vec3.x() == -3.0f && vec3.y() == -3.0f && vec3.z() == -3.0f, "Vec3f -= failed");

  // Test *= with a scalar
  vec3 = vec1;
  vec3 *= 2.0f;
  custom_assert(vec3.x() == 2.0f && vec3.y() == 4.0f && vec3.z() == 6.0f, "Vec3f *= failed");

  // Test /= with a scalar
  vec3 = vec1;
  vec3 /= 2.0f;
  custom_assert(vec3.x() == 0.5f && vec3.y() == 1.0f && vec3.z() == 1.5f, "Vec3f /= failed");

  // Test operator[]
  custom_assert(vec1[0] == 1.0f && vec1[1] == 2.0f && vec1[2] == 3.0f, "Vec3f operator[] failed");

  // Test equality
  Vec3f vec4(1.0f, 2.0f, 3.0f);
  custom_assert(vec1 == vec4, "Vec3f equality failed");

  // Test inequality
  custom_assert(vec1 != vec2, "Vec3f inequality failed");
  return 0;
}
