#pragma once

namespace SpaceEngine {

class IStorage {
public:
    virtual ~IStorage() = default;
    virtual void remove(uint32_t id) = 0;
    virtual void clear() = 0;
};

template<typename T>
class Storage final : public IStorage{
private:
    std::unordered_map<uint32_t, T> data;
public:
    bool has(uint32_t id) const {
        return data.find(id) != data.end();
    }

    T& get(uint32_t id) {
        auto it = data.find(id);
        if (it == data.end()) throw std::runtime_error("Storage::get: missing component");
        return it->second;
    }

    const T& get(uint32_t id) const {
        auto it = data.find(id);
        if (it == data.end()) throw std::runtime_error("Storage::get: missing component");
        return it->second;
    }

    T& add(uint32_t id, T value) {
        auto [it, inserted] = data.emplace(id, std::move(value));
        if (!inserted) {
            it->second = std::move(value);
        }
        return it->second;
    }

    void remove(uint32_t id) override {
        data.erase(id);
    }

    void clear() override {
        data.clear();
    }

    auto& raw() { return data; }
    const auto& raw() const { return data; }

};

}