#pragma once

namespace SpaceEngine {

struct Script {
  bool enabled = true;

  Script();
  virtual ~Script() = default;

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
