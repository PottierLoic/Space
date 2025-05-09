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
  virtual ~Script() = default; // TODO: Check Clang-tidy warning

  /**
   * @brief Called once when the component is instantiated
   */
  virtual void awake();

  /**
   * @brief Called once after all awake() functions have been called.
   */
  virtual void start();

  /**
   * @brief Called every frame during the game loop
   */
  virtual void update();

  /**
   * @brief Called at a fixed time frame, typically for physics
   */
  virtual void fixedUpdate();

  /**
   * @brief Called every frame after all update() functions have been called.
   */
  virtual void lateUpdate();

  /**
   * @brief Called once, right before the object is destroyed.
   */
  virtual void onDestroy();

  /**
   * @brief Called when the object is disabled (not destroyed).
   */
  virtual void onDisable();

  /**
   * @brief Called when the object is enabled again
   */
  virtual void onEnable();
};

}
