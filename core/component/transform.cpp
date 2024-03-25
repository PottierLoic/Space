#include "component/transform.hpp"

namespace SpaceEngine {

Transform::Transform(std::weak_ptr<Entity> owner, std::string name) : Component(owner) {
  this->name = name;
  this->position = Vec3d();
  this->scale = Vec3d(1.0f, 1.0f, 1.0f);
}

}
