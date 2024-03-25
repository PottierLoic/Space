#pragma once

#include <array>
#include <cmath>
#include <iostream>

namespace SpaceEngine {

template<typename T, std::size_t N>
class Vector {
public:
  std::array<T, N> data;

  // Constructors
  constexpr Vector() noexcept = default;
  constexpr explicit Vector(T val) noexcept;
  template <typename... Args>
  constexpr explicit Vector(Args&&... args) noexcept;

  // Accessors for x, y, z, w.
  constexpr const T& x() const noexcept;
  constexpr T& x() noexcept;
  constexpr const T& y() const noexcept;
  constexpr T& y() noexcept;
  constexpr const T& z() const noexcept;
  constexpr T& z() noexcept;
  constexpr const T& w() const noexcept;
  constexpr T& w() noexcept;

  // Operations.
  constexpr Vector operator-() const noexcept;
  constexpr Vector operator+(const Vector& vec) const noexcept;
  constexpr Vector operator-(const Vector& vec) const noexcept;
  constexpr Vector operator*(const Vector& vec) const noexcept;
  constexpr Vector operator*(T val) const noexcept;
  constexpr Vector operator/(const Vector& vec) const noexcept;
  constexpr Vector operator/(T val) const noexcept;

  // Assignement operations.
  constexpr Vector& operator+=(const Vector& vec) noexcept;
  constexpr Vector& operator-=(const Vector& vec) noexcept;
  constexpr Vector& operator*=(const Vector& vec) noexcept;
  constexpr Vector& operator*=(T val) noexcept;
  constexpr Vector& operator/=(const Vector& vec) noexcept;
  constexpr Vector& operator/=(T val) noexcept;

  // Access operators.
  constexpr const T& operator[](std::size_t index) const noexcept;
  constexpr T& operator[](std::size_t index) noexcept;

  // Equality operators.
  constexpr bool operator==(const Vector& vec) const noexcept;
  constexpr bool operator!=(const Vector& vec) const noexcept;

  // stdout
  std::ostream& operator<< <>(std::ostream& stream, const Vector& vec);
};

// Aliases

template <typename T> using Vec2 = Vector<T, 2>;
template <typename T> using Vec3 = Vector<T, 3>;
template <typename T> using Vec4 = Vector<T, 4>;

using Vec2i = Vec2<int>;
using Vec3i = Vec3<int>;
using Vec4i = Vec4<int>;

using Vec2f = Vec2<float>;
using Vec3f = Vec3<float>;
using Vec4f = Vec4<float>;

using Vec2d = Vec2<double>;
using Vec3d = Vec3<double>;
using Vec4d = Vec4<double>;

}

#include "vector.inl"
