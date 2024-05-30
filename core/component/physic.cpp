#include "component/physic.hpp"

namespace SpaceEngine {

Physic::Physic() {
  this->mass = 1.0;
  this->drag = 0;
  this->angularDrag = 0;
  this->gravity = false;
}

}
