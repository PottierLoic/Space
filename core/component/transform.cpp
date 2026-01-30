#include "component/transform.hpp"

namespace SpaceEngine {

Transform::Transform(const std::string& name) {
  this->name = name;
  this->position = Vec3f();
  this->rotation = Vec3f();
  this->scale = Vec3f(1.0f, 1.0f, 1.0f);
}

}  // namespace SpaceEngine
