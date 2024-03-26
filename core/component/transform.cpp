#include "component/transform.hpp"

namespace SpaceEngine {

Transform::Transform(std::weak_ptr<Entity> owner, std::string name) : Component(owner) {
  this->name = name;
  this->position = Vec3f();
  this->scale = Vec3f(1.0f, 1.0f, 1.0f);
}

}
