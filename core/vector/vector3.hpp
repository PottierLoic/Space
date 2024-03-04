#pragma once

#include <cmath>

namespace SpaceEngine {

/*
 * The Vector3 class represents a three-dimensional vector with x, y, and z components.
 *
 * Properties:
 * - x (double): The x-component of the vector.
 * - y (double): The y-component of the vector.
 * - z (double): The z-component of the vector.
 *
 * Constructors:
 * - Vector3(): Initializes a new Vector3 with default x, y, and z values (0.0).
 * - Vector3(double x, double y, double z): Initializes a new Vector3 with the specified x, y, and z values.
 *
 * Methods:
 * - Vector3 operator+(const Vector3 &other): Adds two Vector3 instances and returns the result.
 * - Vector3 operator-(const Vector3 &other): Subtracts the other vector from the current vector and returns the result.
 * - Vector3 operator*(const Vector3 &other): Multiplies corresponding components of two vectors and returns the result.
 * - Vector3 operator/(const Vector3 &other): Divides corresponding components of two vectors and returns the result.
 *
 * - Vector3 operator+=(const Vector3 &other): Adds another vector to the current vector and updates the current vector.
 * - Vector3 operator-=(const Vector3 &other): Subtracts another vector from the current vector and updates the current vector.
 * - Vector3 operator*=(const Vector3 &other): Multiplies corresponding components of two vectors and updates the current vector.
 * - Vector3 operator/=(const Vector3 &other): Divides corresponding components of two vectors and updates the current vector.
 *
 * - bool operator==(const Vector3 &other): Checks if two vectors are equal.
 * - bool operator!=(const Vector3 &other): Checks if two vectors are not equal.
 *
 * - double distance(const Vector3 &other): Calculates the Euclidean distance between two vectors.
 */
class Vector3 {
public:
  double x, y, z;

  /**
   * @brief Initializes a new Vector3 with default x, y, and z values (0.0).
   */
  Vector3();

  /**
   * @brief Initializes a new Vector3 with the specified x, y, and z values.
   * @param x: The x-component of the vector.
   * @param y: The y-component of the vector.
   * @param z: The z-component of the vector.
   */
  Vector3(double x, double y, double z);

  /* Arithmetic operators */
  Vector3 operator+(const Vector3 &other);
  Vector3 operator-(const Vector3 &other);
  Vector3 operator*(const Vector3 &other);
  Vector3 operator/(const Vector3 &other);

  /* Compound assignment operators */
  Vector3 operator+=(const Vector3 &other);
  Vector3 operator-=(const Vector3 &other);
  Vector3 operator*=(const Vector3 &other);
  Vector3 operator/=(const Vector3 &other);

  /* Comparison operators */
  bool operator==(const Vector3 &other);
  bool operator!=(const Vector3 &other);

  /**
   * @brief Calculates the Euclidean distance between two vectors.
   * @param other: The Vector3 to calculate the distance to.
   * @return The Euclidean distance between the two vectors.
   */
  double distance(const Vector3 &other);
};

}
