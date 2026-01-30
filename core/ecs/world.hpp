#pragma once

#include <memory>
#include <typeindex>
#include <unordered_map>

#include "entity.hpp"
#include "storage.hpp"
#include "types/types.hpp"

namespace SpaceEngine {

class World {
 private:
  std::unordered_map<std::type_index, std::unique_ptr<IStorage>> storages;
  u32 next_id = 0;

  template <typename T>
  Storage<T>& storage() {
    auto key = std::type_index(typeid(T));
    auto it = storages.find(key);
    if (it == storages.end()) {
      auto ptr = std::make_unique<Storage<T>>();
      auto* raw = ptr.get();
      storages.emplace(key, std::move(ptr));
      return *raw;
    }
    return *static_cast<Storage<T>*>(it->second.get());
  }

  template <typename T>
  const Storage<T>& storage() const {
    return const_cast<World*>(this)->storage<T>();
  }

 public:
  World() = default;
  ~World() = default;

  Entity create() {
    u32 id = next_id++;
    return Entity{id};
  }

  void destroy(Entity e) {
    for (auto& [_, storage] : storages) {
      storage->remove(e.id);
    }
  }

  template <typename T>
  bool has_component(Entity e) const {
    return storage<T>().has(e.id);
  }

  template <typename T>
  T& add_component(Entity e, T value) {
    return storage<T>().add(e.id, std::move(value));
  }

  template <typename T>
  void remove_component(Entity e) {
    storage<T>().remove(e.id);
  }

  template <typename T>
  T& get_component(Entity e) {
    return storage<T>().get(e.id);
  }

  template <typename T>
  const T& get_component(Entity e) const {
    return storage<T>().get(e.id);
  }

  template <typename T>
  class View1 {
   public:
    explicit View1(const World& w) : world(w), st(&w.storage<T>()) {}

    class Iterator {
     public:
      using MapIt = typename std::unordered_map<u32, T>::const_iterator;
      Iterator(const World& w, const std::unordered_map<u32, T>* map, MapIt it, MapIt end)
          : world(w), map(map), it(it), end(end) {}
      Entity operator*() const {
        return Entity{it->first};
      }
      Iterator& operator++() {
        ++it;
        return *this;
      }
      bool operator!=(const Iterator& other) const {
        return it != other.it;
      }

     private:
      const World& world;
      const std::unordered_map<u32, T>* map;
      MapIt it;
      MapIt end;
    };

    Iterator begin() const {
      const auto& m = st->raw();
      return Iterator{world, &m, m.begin(), m.end()};
    }

    Iterator end() const {
      const auto& m = st->raw();
      return Iterator{world, &m, m.end(), m.end()};
    }

   private:
    const World& world;
    const Storage<T>* st;
  };

  template <typename A, typename B>
  class View2 {
   public:
    explicit View2(const World& w) : world(w), a(&w.storage<A>()) {}

    class Iterator {
     public:
      using MapIt = typename std::unordered_map<u32, A>::const_iterator;

      Iterator(const World& w, const std::unordered_map<u32, A>* amap, MapIt it, MapIt end)
          : world(w), amap(amap), it(it), end(end) {
        skip_invalid();
      }

      Entity operator*() const {
        return Entity{it->first};
      }

      Iterator& operator++() {
        ++it;
        skip_invalid();
        return *this;
      }

      bool operator!=(const Iterator& other) const {
        return it != other.it;
      }

     private:
      void skip_invalid() {
        while (it != end) {
          Entity e{it->first};
          if (world.has_component<B>(e)) {
            return;
          }
          ++it;
        }
      }

      const World& world;
      const std::unordered_map<u32, A>* amap;
      MapIt it;
      MapIt end;
    };

    Iterator begin() const {
      const auto& m = a->raw();
      return Iterator(world, &m, m.begin(), m.end());
    }

    Iterator end() const {
      const auto& m = a->raw();
      return Iterator(world, &m, m.end(), m.end());
    }

   private:
    const World& world;
    const Storage<A>* a;
  };

  template <typename T>
  View1<T> view() const {
    return View1<T>(*this);
  }

  template <typename A, typename B>
  View2<A, B> view() const {
    return View2<A, B>(*this);
  }
};

}  // namespace SpaceEngine