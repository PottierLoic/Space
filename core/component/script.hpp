#pragma once

#include "component/component.hpp"
#include "component/transform.hpp"

namespace SpaceEngine {

class Script : public Component {
public:
  // The transform of the entity that script is attached to.
  std::shared_ptr<Transform> transform;

  // if not enabled, update functions will not be called.
  bool enabled = true;

  Script();
  virtual ~Script() = default;

  virtual void awake();
  virtual void start();
  virtual void update();
  virtual void fixedUpdate();
  virtual void lateUpdate();
  virtual void onDestroy();
  virtual void onDisable();
  virtual void onEnable();
};

}
