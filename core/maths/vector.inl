#include <cstddef>

namespace SpaceEngine {

template<typename T, std::size_t N>
constexpr Vector<T, N>::Vector(T val) noexcept {
  data.fill(val);
}

template<typename T, std::size_t N>
template<typename... Args>
constexpr Vector<T, N>::Vector(Args&&... args) noexcept : data{{std::forward<Args>(args)...}} {}

template<typename T, std::size_t N>
constexpr const T& Vector<T, N>::x() const noexcept {
  static_assert(N >= 1, "Vector does not have an X component.");
  return data[0];
}

template<typename T, std::size_t N>
constexpr T& Vector<T, N>::x() noexcept {
  static_assert(N >= 1, "Vector does not have an X component.");
  return data[0];
}

template<typename T, std::size_t N>
constexpr const T& Vector<T, N>::y() const noexcept {
  static_assert(N >= 2, "Vector does not have a Y component.");
  return data[1];
}

template<typename T, std::size_t N>
constexpr T& Vector<T, N>::y() noexcept {
  static_assert(N >= 2, "Vector does not have a Y component.");
  return data[1];
}

template<typename T, std::size_t N>
constexpr const T& Vector<T, N>::z() const noexcept {
  static_assert(N >= 3, "Vector does not have a Z component.");
  return data[2];
}

template<typename T, std::size_t N>
constexpr T& Vector<T, N>::z() noexcept {
  static_assert(N >= 3, "Vector does not have a Z component.");
  return data[2];
}

template<typename T, std::size_t N>
constexpr const T& Vector<T, N>::w() const noexcept {
  static_assert(N >= 4, "Vector does not have a W component.");
  return data[3];
}

template<typename T, std::size_t N>
constexpr T& Vector<T, N>::w() noexcept {
  static_assert(N >= 4, "Vector does not have a W component.");
  return data[3];
}

template<typename T, std::size_t N>
constexpr Vector<T, N> Vector<T, N>::operator-() const noexcept {
  Vector<T, N> result;
  for (std::size_t i = 0; i < N; ++i) {
    result.data[i] = -data[i];
  }
  return result;
}

template<typename T, std::size_t N>
constexpr Vector<T, N> Vector<T, N>::operator+(const Vector<T, N>& vec) const noexcept {
  Vector<T, N> result;
  for (std::size_t i = 0; i < N; ++i) {
    result.data[i] = data[i] + vec.data[i];
  }
  return result;
}

template<typename T, std::size_t N>
constexpr Vector<T, N> Vector<T, N>::operator-(const Vector<T, N>& vec) const noexcept {
  Vector<T, N> result;
  for (std::size_t i = 0; i < N; ++i) {
    result.data[i] = data[i] - vec.data[i];
  }
  return result;
}

template<typename T, std::size_t N>
constexpr Vector<T, N> Vector<T, N>::operator*(T val) const noexcept {
  Vector<T, N> result;
  for (std::size_t i = 0; i < N; ++i) {
    result.data[i] = data[i] * val;
  }
  return result;
}

template<typename T, std::size_t N>
constexpr Vector<T, N> Vector<T, N>::operator*(const Vector<T, N>& vec) const noexcept {
  Vector<T, N> result;
  for (std::size_t i = 0; i < N; ++i) {
    result.data[i] = data[i] * vec.data[i];
  }
  return result;
}

template<typename T, std::size_t N>
constexpr Vector<T, N> Vector<T, N>::operator/(T val) const noexcept {
  Vector<T, N> result;
  for (std::size_t i = 0; i < N; ++i) {
    result.data[i] = data[i] / val;
  }
  return result;
}

template<typename T, std::size_t N>
constexpr Vector<T, N> Vector<T, N>::operator/(const Vector<T, N>& vec) const noexcept {
  Vector<T, N> result;
  for (std::size_t i = 0; i < N; ++i) {
    result.data[i] = data[i] / vec.data[i];
  }
  return result;
}

template<typename T, std::size_t N>
constexpr Vector<T, N>& Vector<T, N>::operator+=(const Vector<T, N>& vec) noexcept {
  for (std::size_t i = 0; i < N; ++i) {
    data[i] += vec.data[i];
  }
  return *this;
}

template<typename T, std::size_t N>
constexpr Vector<T, N>& Vector<T, N>::operator-=(const Vector<T, N>& vec) noexcept {
  for (std::size_t i = 0; i < N; ++i) {
    data[i] -= vec.data[i];
  }
  return *this;
}

template<typename T, std::size_t N>
constexpr Vector<T, N>& Vector<T, N>::operator*=(T val) noexcept {
  for (std::size_t i = 0; i < N; ++i) {
    data[i] *= val;
  }
  return *this;
}

template<typename T, std::size_t N>
constexpr Vector<T, N>& Vector<T, N>::operator*=(const Vector<T, N>& vec) noexcept {
  for (std::size_t i = 0; i < N; ++i) {
    data[i] *= vec.data[i];
  }
  return *this;
}

template<typename T, std::size_t N>
constexpr Vector<T, N>& Vector<T, N>::operator/=(T val) noexcept {
  for (std::size_t i = 0; i < N; ++i) {
    data[i] /= val;
  }
  return *this;
}

template<typename T, std::size_t N>
constexpr Vector<T, N>& Vector<T, N>::operator/=(const Vector<T, N>& vec) noexcept {
  for (std::size_t i = 0; i < N; ++i) {
    data[i] /= vec.data[i];
  }
  return *this;
}

template<typename T, std::size_t N>
constexpr const T& Vector<T, N>::operator[](std::size_t index) const noexcept {
  return data[index];
}

template<typename T, std::size_t N>
constexpr T& Vector<T, N>::operator[](std::size_t index) noexcept {
  return data[index];
}

template<typename T, std::size_t N>
constexpr bool Vector<T, N>::operator==(const Vector<T, N>& vec) const noexcept {
  for (std::size_t i = 0; i < N; ++i) {
    if (data[i] != vec.data[i]) {
      return false;
    }
  }
  return true;
}

template<typename T, std::size_t N>
constexpr bool Vector<T, N>::operator!=(const Vector<T, N>& vec) const noexcept {
  return !(*this == vec);
}

template<typename T, std::size_t N>
std::ostream& operator<<(std::ostream& stream, const Vector<T, N>& vec) {
  stream << "(";
  for (std::size_t i = 0; i < N; ++i) {
    stream << vec.data[i];
    if (i < N - 1) stream << ", ";
  }
  stream << ")";
  return stream;
}


}
