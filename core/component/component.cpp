#include "component/component.hpp"

namespace SpaceEngine {

Component::Component() {}

void Component::setOwner(std::weak_ptr<Entity> owner) {
  this->owner = owner;
}

}
