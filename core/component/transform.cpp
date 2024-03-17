#include "component/transform.hpp"

namespace SpaceEngine {

Transform::Transform(Entity* owner, std::string name) : Component(owner) {
  this->name = name;
  this->position = Vector3();
  this->scale = Vector3(1.0f, 1.0f, 1.0f);
}

Transform::~Transform() {}

}
