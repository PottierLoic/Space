#include "component/physic.hpp"

namespace SpaceEngine {

Physic::Physic(std::weak_ptr<Entity> owner) : Component(owner) {
  this->mass = 1.0;
  this->drag = 0;
  this->angularDrag = 0;
  this->gravity = false;
}

}
