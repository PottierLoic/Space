#include "test.hpp"
#include "vector/vector.hpp"

using SpaceEngine::Vec2f; // Using the float specialization for 2D vectors

int testVector2() {
  Vec2f vec1(1.0f, 2.0f);
  Vec2f vec2(3.0f, 5.0f);

  /* Addition check */
  Vec2f add_result = vec1 + vec2;
  custom_assert((add_result.x() == 4.0f && add_result.y() == 7.0f), "Addition check failed");

  /* Subtraction check */
  Vec2f sub_result = vec1 - vec2;
  custom_assert((sub_result.x() == -2.0f && sub_result.y() == -3.0f), "Subtraction check failed");

  /* Addition assignment check */
  Vec2f vec3(2.0f, 3.0f);
  vec3 += vec1;
  custom_assert((vec3.x() == 3.0f && vec3.y() == 5.0f), "Addition assignment check failed");

  /* Subtraction assignment check */
  Vec2f vec4(5.0f, 7.0f);
  vec4 -= vec1;
  custom_assert((vec4.x() == 4.0f && vec4.y() == 5.0f), "Subtraction assignment check failed");

  /* Multiplication assignment check */
  Vec2f vec5(2.0f, 4.0f);
  vec5 *= 2.0f; // Assuming scalar multiplication
  custom_assert((vec5.x() == 4.0f && vec5.y() == 8.0f), "Multiplication assignment check failed");

  // Since the Vector class does not directly support division by another Vector,
  // this section will be omitted or you need to implement it in the Vector class.

  /* Equality check */
  Vec2f vec7(3.0f, 5.0f);
  custom_assert((vec2.x() == vec7.x() && vec2.y() == vec7.y()), "Equality check failed");

  /* Inequality check */
  Vec2f vec8(1.0f, 7.0f);
  custom_assert((vec1.x() != vec8.x() || vec1.y() != vec8.y()), "Inequality check failed");

  // The distance and glm cast checks are omitted since they would require additional implementation details.

  return 0;
}
