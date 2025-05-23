#include "component/component.hpp"

namespace SpaceEngine {

Component::Component() = default;

void Component::setOwner(const std::weak_ptr<Entity> &owner) {
  this->owner = owner;
}

void Component::onEntityDestroyed() {}

}
