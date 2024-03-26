#pragma once

#include <array>
#include <cmath>
#include <iostream>
#include <cstdint>

namespace SpaceEngine {

template<typename T, std::size_t N>
class Vector {
public:
  std::array<T, N> data;

  // Constructors
  constexpr Vector() = default;
  constexpr explicit Vector(T val);
  template <typename... Args, typename = std::enable_if_t<sizeof...(Args) == N>>
  constexpr explicit Vector(Args&&... args);

  // Dimensionality adjustements
  constexpr explicit Vector(const Vector<T, N + 1>& vec);
  constexpr Vector(const Vector<T, N - 1>& vec, T val);

  // Accessors for x, y, z, w.
  constexpr const T& x() const;
  constexpr T& x();
  constexpr const T& y() const;
  constexpr T& y();
  constexpr const T& z() const;
  constexpr T& z();
  constexpr const T& w() const;
  constexpr T& w();

  // Operations.
  constexpr Vector operator-() const;
  constexpr Vector operator+(const Vector& vec) const;
  constexpr Vector operator+(T val) const;
  constexpr Vector operator-(const Vector& vec) const;
  constexpr Vector operator-(T val) const;
  constexpr Vector operator*(const Vector& vec) const;
  constexpr Vector operator*(T val) const;
  constexpr Vector operator/(const Vector& vec) const;
  constexpr Vector operator/(T val) const;

  // Assignement operations.
  constexpr Vector& operator+=(const Vector& vec);
  constexpr Vector& operator+=(T val);
  constexpr Vector& operator-=(const Vector& vec);
  constexpr Vector& operator-=(T val);
  constexpr Vector& operator*=(const Vector& vec);
  constexpr Vector& operator*=(T val);
  constexpr Vector& operator/=(const Vector& vec);
  constexpr Vector& operator/=(T val);

  // Access operators.
  constexpr const T& operator[](std::size_t index) const;
  constexpr T& operator[](std::size_t index);

  // Equality operators.
  constexpr bool operator==(const Vector& vec) const;
  constexpr bool operator!=(const Vector& vec) const;

  // Utils
  // TODO : Add following functions
  // constexpr float dot(const Vector& vec) const;
  // constexpr Vector cross(const Vector& vec) const;
};

// Aliases

template <typename T> using Vec2 = Vector<T, 2>;
template <typename T> using Vec3 = Vector<T, 3>;
template <typename T> using Vec4 = Vector<T, 4>;

using Vec2b = Vec2<uint8_t>;
using Vec3b = Vec3<uint8_t>;
using Vec4b = Vec4<uint8_t>;

using Vec2i = Vec2<int>;
using Vec3i = Vec3<int>;
using Vec4i = Vec4<int>;

using Vec2u = Vec2<uint32_t>;
using Vec3u = Vec3<uint32_t>;
using Vec4u = Vec4<uint32_t>;

using Vec2f = Vec2<float>;
using Vec3f = Vec3<float>;
using Vec4f = Vec4<float>;

using Vec2d = Vec2<double>;
using Vec3d = Vec3<double>;
using Vec4d = Vec4<double>;

}

#include "vector.inl"
