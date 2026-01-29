#pragma once

#include "types/types.hpp"

namespace SpaceEngine {

struct Entity {
    u32 id{};

    bool operator==(const Entity& other) const {
        return id == other.id;
    }

    bool operator!=(const Entity& other) const {
        return id != other.id;
    }
};

}
