#pragma once

#include <cmath>

/*
 * The Vector2 class represents a two-dimensional vector with x and y components.
 *
 * Properties:
 * - x (double): The x-component of the vector.
 * - y (double): The y-component of the vector.
 *
 * Constructors:
 * - Vector2(): Initializes a new Vector2 with default x and y values (0.0).
 * - Vector2(double x, double y): Initializes a new Vector2 with the specified x and y values.
 *
 * Methods:
 * - Vector2 operator+(const Vector2 &other): Adds two Vector2 instances and returns the result.
 * - Vector2 operator-(const Vector2 &other): Subtracts the other vector from the current vector and returns the result.
 * - Vector2 operator*(const Vector2 &other): Multiplies corresponding components of two vectors and returns the result.
 * - Vector2 operator/(const Vector2 &other): Divides corresponding components of two vectors and returns the result.
 *
 * - Vector2 operator+=(const Vector2 &other): Adds another vector to the current vector and updates the current vector.
 * - Vector2 operator-=(const Vector2 &other): Subtracts another vector from the current vector and updates the current vector.
 * - Vector2 operator*=(const Vector2 &other): Multiplies corresponding components of two vectors and updates the current vector.
 * - Vector2 operator/=(const Vector2 &other): Divides corresponding components of two vectors and updates the current vector.
 *
 * - bool operator==(const Vector2 &other): Checks if two vectors are equal.
 * - bool operator!=(const Vector2 &other): Checks if two vectors are not equal.
 *
 * - double distance(const Vector2 &other): Calculates the Euclidean distance between two vectors.
 */
class Vector2 {
public:
  double x, y;

  /**
   * @brief Initializes a new Vector2 with default x and y values (0.0).
   */
  Vector2();

  /**
   * @brief Initializes a new Vector2 with the specified x and y values.
   * @param x: The x-component of the vector.
   * @param y: The y-component of the vector.
   */
  Vector2(double x, double y);

  /* Arithmetic operators */
  Vector2 operator+(const Vector2 &other);
  Vector2 operator-(const Vector2 &other);
  Vector2 operator*(const Vector2 &other);
  Vector2 operator/(const Vector2 &other);

  /* Compound assignment operators */
  Vector2 operator+=(const Vector2 &other);
  Vector2 operator-=(const Vector2 &other);
  Vector2 operator*=(const Vector2 &other);
  Vector2 operator/=(const Vector2 &other);

  /* Comparison operators */
  bool operator==(const Vector2 &other);
  bool operator!=(const Vector2 &other);

  /**
   * @brief Calculates the Euclidean distance between two vectors.
   * @param other: The Vector2 to calculate the distance to.
   * @return The Euclidean distance between the two vectors.
   */
  double distance(const Vector2 &other);
};