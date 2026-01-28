#pragma once

namespace SpaceEngine {

struct Physic {
  float mass;
  float drag;
  float angularDrag;
  bool gravity;

  Physic();
};

}