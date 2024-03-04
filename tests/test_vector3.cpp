#include "test.hpp"
#include "vector/vector3.hpp"

int testVector3() {
  Vector3 vec1 = Vector3(1.0, 2.0, 3.0);
  Vector3 vec2 = Vector3(3.0, 5.0, 7.0);

  /* Addition check */
  Vector3 add_result = vec1 + vec2;
  custom_assert(add_result == Vector3(4.0, 7.0, 10.0));

  /* Subtraction check */
  Vector3 sub_result = vec1 - vec2;
  custom_assert(sub_result == Vector3(-2.0, -3.0, -4.0));

  /* Addition assignment check */
  Vector3 vec3(2.0, 3.0, 4.0);
  vec3 += vec1;
  custom_assert(vec3 == Vector3(3.0, 5.0, 7.0));

  /* Subtraction assignment check */
  Vector3 vec4(5.0, 7.0, 9.0);
  vec4 -= vec1;
  custom_assert(vec4 == Vector3(4.0, 5.0, 6.0));

  /* Multiplication assignment check */
  Vector3 vec5(2.0, 4.0, 6.0);
  vec5 *= vec1;
  custom_assert(vec5 == Vector3(2.0, 8.0, 18.0));

  /* Division assignment check */
  Vector3 vec6(6.0, 8.0, 12.0);
  vec6 /= vec2;
  custom_assert(vec6 == Vector3(2.0, 1.6, 1.7142857142857142));

  /* Equality check */
  Vector3 vec7(3.0, 5.0, 7.0);
  custom_assert(vec2 == vec7);

  /* Inequality check */
  Vector3 vec8(1.0, 7.0, 9.0);
  custom_assert(vec1 != vec8);

  /* Distance check */
  double distance_result = vec1.distance(vec2);
  custom_assert(distance_result == sqrt(29.));

  return 0;
}
