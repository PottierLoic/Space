#include "vector/vector2.hpp"

int main() {
    SpaceEngine::Vector2 position(10.0, 20.0);
    SpaceEngine::Vector2 velocity(5.0, 3.0);

    SpaceEngine::Vector2 newPosition = position + velocity;
    // ... use newPosition as needed

    return 0;
}