#include "component/transform.hpp"

namespace SpaceEngine {

Transform::Transform(Entity* owner, std::string name) : Component(owner) {
  this->name = name;
  this->position = Vector3();
}

Transform::~Transform() {}

}
