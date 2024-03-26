#include "test.hpp"
#include "maths/vector.hpp"

using SpaceEngine::Vec4f;

int testVector4() {
  Vec4f vec1(1.0f, 2.0f, 3.0f, 4.0f);
  Vec4f vec2(4.0f, 5.0f, 6.0f, 7.0f);

  // Test addition
  Vec4f add_result = vec1 + vec2;
  custom_assert(add_result.x() == 5.0f && add_result.y() == 7.0f && add_result.z() == 9.0f && add_result.w() == 11.0f, "Vec4f addition failed");

  // Test subtraction
  Vec4f sub_result = vec1 - vec2;
  custom_assert(sub_result.x() == -3.0f && sub_result.y() == -3.0f && sub_result.z() == -3.0f && sub_result.w() == -3.0f, "Vec4f subtraction failed");

  // Test multiplication by a scalar
  Vec4f mul_result_scalar = vec1 * 2.0f;
  custom_assert(mul_result_scalar.x() == 2.0f && mul_result_scalar.y() == 4.0f && mul_result_scalar.z() == 6.0f && mul_result_scalar.w() == 8.0f, "Vec4f scalar multiplication failed");

  // Test division by a scalar
  Vec4f div_result_scalar = vec1 / 2.0f;
  custom_assert(div_result_scalar.x() == 0.5f && div_result_scalar.y() == 1.0f && div_result_scalar.z() == 1.5f && div_result_scalar.w() == 2.0f, "Vec4f scalar division failed");

  // Test addition assignment
  Vec4f vec3 = vec1;
  vec3 += vec2;
  custom_assert(vec3.x() == 5.0f && vec3.y() == 7.0f && vec3.z() == 9.0f && vec3.w() == 11.0f, "Vec4f += failed");

  // Test subtraction assignment
  vec3 = vec1;
  vec3 -= vec2;
  custom_assert(vec3.x() == -3.0f && vec3.y() == -3.0f && vec3.z() == -3.0f && vec3.w() == -3.0f, "Vec4f -= failed");

  // Test multiplication assignment by a scalar
  vec3 = vec1;
  vec3 *= 2.0f;
  custom_assert(vec3.x() == 2.0f && vec3.y() == 4.0f && vec3.z() == 6.0f && vec3.w() == 8.0f, "Vec4f *= failed");

  // Test division assignment by a scalar
  vec3 = vec1;
  vec3 /= 2.0f;
  custom_assert(vec3.x() == 0.5f && vec3.y() == 1.0f && vec3.z() == 1.5f && vec3.w() == 2.0f, "Vec4f /= failed");

  // Test equality
  Vec4f vec4(1.0f, 2.0f, 3.0f, 4.0f);
  custom_assert(vec1 == vec4, "Vec4f equality check failed");

  // Test inequality
  custom_assert(vec1 != vec2, "Vec4f inequality check failed");
  return 0;
}
