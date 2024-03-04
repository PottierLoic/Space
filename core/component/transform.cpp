#include "component/transform.hpp"

namespace SpaceEngine {

Transform::Transform(std::string name) {
  this->name = name;
  this->position = Vector3();
}

Transform::~Transform() {}

}
