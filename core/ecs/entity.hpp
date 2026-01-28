#pragma once

namespace SpaceEngine {

struct Entity {
    std::uint32_t id{};

    bool operator==(const Entity& other) const {
        return id == other.id;
    }

    bool operator!=(const Entity& other) const {
        return id != other.id;
    }
};

}
