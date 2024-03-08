#include "component/component.hpp"

namespace SpaceEngine {

Component::Component(Entity* owner) { this->owner = owner; }
Component::~Component() {}

}
