#include "component/component.hpp"

namespace SpaceEngine {

Component::Component(std::weak_ptr<Entity> owner) { this->owner = owner; }
Component::~Component() {}

}
