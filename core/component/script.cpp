#include "component/script.hpp"

namespace SpaceEngine {

Script::Script(std::weak_ptr<Entity> owner) : Component(owner) {}

}
