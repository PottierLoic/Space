#include <cstddef>

namespace SpaceEngine {

template<typename T, std::size_t N>
constexpr Vector<T, N>::Vector(T val) {
  data.fill(val);
}

template<typename T, std::size_t N>
template<typename... Args, typename>
constexpr Vector<T, N>::Vector(Args&&... args) : data{ static_cast<T>(args)... } {}

template<typename T, std::size_t N>
constexpr Vector<T, N>::Vector(const Vector<T, N + 1>& vec) {
  for (std::size_t i = 0; i < N; ++i) {
    data[i] = vec.data[i];
  }
}

template<typename T, std::size_t N>
constexpr Vector<T, N>::Vector(const Vector<T, N - 1>& vec, T val) {
  for (std::size_t i = 0; i < N - 1; ++i) {
    data[i] = vec.data[i];
  }
  data[N - 1] = val;
}

template<typename T, std::size_t N>
constexpr const T& Vector<T, N>::x() const {
  static_assert(N >= 1, "Vector does not have an X component.");
  return data[0];
}

template<typename T, std::size_t N>
constexpr T& Vector<T, N>::x() {
  static_assert(N >= 1, "Vector does not have an X component.");
  return data[0];
}

template<typename T, std::size_t N>
constexpr const T& Vector<T, N>::y() const {
  static_assert(N >= 2, "Vector does not have a Y component.");
  return data[1];
}

template<typename T, std::size_t N>
constexpr T& Vector<T, N>::y() {
  static_assert(N >= 2, "Vector does not have a Y component.");
  return data[1];
}

template<typename T, std::size_t N>
constexpr const T& Vector<T, N>::z() const {
  static_assert(N >= 3, "Vector does not have a Z component.");
  return data[2];
}

template<typename T, std::size_t N>
constexpr T& Vector<T, N>::z() {
  static_assert(N >= 3, "Vector does not have a Z component.");
  return data[2];
}

template<typename T, std::size_t N>
constexpr const T& Vector<T, N>::w() const {
  static_assert(N >= 4, "Vector does not have a W component.");
  return data[3];
}

template<typename T, std::size_t N>
constexpr T& Vector<T, N>::w() {
  static_assert(N >= 4, "Vector does not have a W component.");
  return data[3];
}

template<typename T, std::size_t N>
constexpr Vector<T, N> Vector<T, N>::operator-() const {
  Vector<T, N> result;
  for (std::size_t i = 0; i < N; ++i) {
    result.data[i] = -data[i];
  }
  return result;
}

template<typename T, std::size_t N>
constexpr Vector<T, N> Vector<T, N>::operator+(const Vector<T, N>& vec) const {
  Vector<T, N> result;
  for (std::size_t i = 0; i < N; ++i) {
    result.data[i] = data[i] + vec.data[i];
  }
  return result;
}

template<typename T, std::size_t N>
constexpr Vector<T, N> Vector<T, N>::operator+(T val) const {
  Vector<T, N> result;
  for (std::size_t i = 0; i < N; ++i) {
    result.data[i] = data[i] + val;
  }
  return result;
}

template<typename T, std::size_t N>
constexpr Vector<T, N> Vector<T, N>::operator-(const Vector<T, N>& vec) const {
  Vector<T, N> result;
  for (std::size_t i = 0; i < N; ++i) {
    result.data[i] = data[i] - vec.data[i];
  }
  return result;
}

template<typename T, std::size_t N>
constexpr Vector<T, N> Vector<T, N>::operator-(T val) const {
  Vector<T, N> result;
  for (std::size_t i = 0; i < N; ++i) {
    result.data[i] = data[i] - val;
  }
  return result;
}

template<typename T, std::size_t N>
constexpr Vector<T, N> Vector<T, N>::operator*(T val) const {
  Vector<T, N> result;
  for (std::size_t i = 0; i < N; ++i) {
    result.data[i] = data[i] * val;
  }
  return result;
}

template<typename T, std::size_t N>
constexpr Vector<T, N> Vector<T, N>::operator*(const Vector<T, N>& vec) const {
  Vector<T, N> result;
  for (std::size_t i = 0; i < N; ++i) {
    result.data[i] = data[i] * vec.data[i];
  }
  return result;
}

template<typename T, std::size_t N>
constexpr Vector<T, N> Vector<T, N>::operator/(T val) const {
  Vector<T, N> result;
  for (std::size_t i = 0; i < N; ++i) {
    result.data[i] = data[i] / val;
  }
  return result;
}

template<typename T, std::size_t N>
constexpr Vector<T, N> Vector<T, N>::operator/(const Vector<T, N>& vec) const {
  Vector<T, N> result;
  for (std::size_t i = 0; i < N; ++i) {
    result.data[i] = data[i] / vec.data[i];
  }
  return result;
}

template<typename T, std::size_t N>
constexpr Vector<T, N>& Vector<T, N>::operator+=(const Vector<T, N>& vec) {
  for (std::size_t i = 0; i < N; ++i) {
    data[i] += vec.data[i];
  }
  return *this;
}

template<typename T, std::size_t N>
constexpr Vector<T, N>& Vector<T, N>::operator+=(T val) {
  for (std::size_t i = 0; i < N; ++i) {
    data[i] += val;
  }
  return *this;
}

template<typename T, std::size_t N>
constexpr Vector<T, N>& Vector<T, N>::operator-=(const Vector<T, N>& vec) {
  for (std::size_t i = 0; i < N; ++i) {
    data[i] -= vec.data[i];
  }
  return *this;
}

template<typename T, std::size_t N>
constexpr Vector<T, N>& Vector<T, N>::operator-=(T val) {
  for (std::size_t i = 0; i < N; ++i) {
    data[i] -= val;
  }
  return *this;
}

template<typename T, std::size_t N>
constexpr Vector<T, N>& Vector<T, N>::operator*=(T val) {
  for (std::size_t i = 0; i < N; ++i) {
    data[i] *= val;
  }
  return *this;
}

template<typename T, std::size_t N>
constexpr Vector<T, N>& Vector<T, N>::operator*=(const Vector<T, N>& vec) {
  for (std::size_t i = 0; i < N; ++i) {
    data[i] *= vec.data[i];
  }
  return *this;
}

template<typename T, std::size_t N>
constexpr Vector<T, N>& Vector<T, N>::operator/=(T val) {
  for (std::size_t i = 0; i < N; ++i) {
    data[i] /= val;
  }
  return *this;
}

template<typename T, std::size_t N>
constexpr Vector<T, N>& Vector<T, N>::operator/=(const Vector<T, N>& vec) {
  for (std::size_t i = 0; i < N; ++i) {
    data[i] /= vec.data[i];
  }
  return *this;
}

template<typename T, std::size_t N>
constexpr const T& Vector<T, N>::operator[](std::size_t index) const {
  return data[index];
}

template<typename T, std::size_t N>
constexpr T& Vector<T, N>::operator[](std::size_t index) {
  return data[index];
}

template<typename T, std::size_t N>
constexpr bool Vector<T, N>::operator==(const Vector<T, N>& vec) const {
  for (std::size_t i = 0; i < N; ++i) {
    if (data[i] != vec.data[i]) {
      return false;
    }
  }
  return true;
}

template<typename T, std::size_t N>
constexpr bool Vector<T, N>::operator!=(const Vector<T, N>& vec) const {
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
