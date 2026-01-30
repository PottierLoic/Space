#pragma once

#include "types/types.hpp"

namespace SpaceEngine {

class IStorage {
 public:
  virtual ~IStorage() = default;
  virtual void remove(u32 id) = 0;
  virtual void clear() = 0;
};

template <typename T>
class Storage final : public IStorage {
 private:
  std::unordered_map<u32, T> data;

 public:
  bool has(u32 id) const {
    return data.find(id) != data.end();
  }

  T& get(u32 id) {
    auto it = data.find(id);
    if (it == data.end()) {
      throw std::runtime_error("Storage::get: missing component");
    }
    return it->second;
  }

  const T& get(u32 id) const {
    auto it = data.find(id);
    if (it == data.end()) {
      throw std::runtime_error("Storage::get: missing component");
    }
    return it->second;
  }

  T& add(u32 id, T value) {
    auto [it, inserted] = data.emplace(id, std::move(value));
    if (!inserted) {
      it->second = std::move(value);
    }
    return it->second;
  }

  void remove(u32 id) override {
    data.erase(id);
  }

  void clear() override {
    data.clear();
  }

  auto& raw() {
    return data;
  }
  const auto& raw() const {
    return data;
  }
};

}  // namespace SpaceEngine