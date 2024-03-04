#include "test.hpp"
#include "vector/vector2.hpp"

int testVector2() {
  SpaceEngine::Vector2 vec1 = SpaceEngine::Vector2(1.0, 2.0);
  SpaceEngine::Vector2 vec2 = SpaceEngine::Vector2(3.0, 5.0);

  /* Addition check */
  SpaceEngine::Vector2 add_result = vec1 + vec2;
  custom_assert(add_result == SpaceEngine::Vector2(4.0, 7.0));

  /* Subtraction check */
  SpaceEngine::Vector2 sub_resutl = vec1 - vec2;
  custom_assert(sub_resutl == SpaceEngine::Vector2(-2.0, -3.0));

  /* Addition assignment check */
  SpaceEngine::Vector2 vec3(2.0, 3.0);
  vec3 += vec1;
  custom_assert(vec3 == SpaceEngine::Vector2(3.0, 5.0));

  /* Subtraction assignment check */
  SpaceEngine::Vector2 vec4(5.0, 7.0);
  vec4 -= vec1;
  custom_assert(vec4 == SpaceEngine::Vector2(4.0, 5.0));

  /* Multiplication assignment check */
  SpaceEngine::Vector2 vec5(2.0, 4.0);
  vec5 *= vec1;
  custom_assert(vec5 == SpaceEngine::Vector2(2.0, 8.0));

  /* Division assignment check */
  SpaceEngine::Vector2 vec6(6.0, 8.0);
  vec6 /= vec2;
  custom_assert(vec6 == SpaceEngine::Vector2(2.0, 1.6));

  /* Equality check */
  SpaceEngine::Vector2 vec7(3.0, 5.0);
  custom_assert(vec2 == vec7);

  /* Inequality check */
  SpaceEngine::Vector2 vec8(1.0, 7.0);
  custom_assert(vec1 != vec8);

  /* Distance check */
  double distance_result = vec1.distance(vec2);
  custom_assert(distance_result == sqrt(13.0));
  return 0;
}
