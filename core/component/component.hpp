#pragma once

#include <memory>

namespace SpaceEngine {

class Entity; // Forward declaration of Entity class to avoid circular dependencies.

/**
 * @class Component
 * @brief Serves as a base class for components in the entity-component system.
 *
 * The Component class acts as a base class that other components derive from.
 * Each component holds a weak reference to its owning entity.
 *
 * Attributes:
 * - owner (std::weak_ptr<Entity>): A weak pointer to the entity owning the component.
 *
 * Methods:
 * - Component(std::weak_ptr<Entity> owner): Constructor that sets the owning entity.
 * - virtual ~Component(): Virtual destructor to allow proper cleanup in derived classes.
 */
class Component : public std::enable_shared_from_this<Component> {
protected:
  std::weak_ptr<Entity> owner; // Pointer to the entity owning the component.

public:
  /**
   * @brief Constructor that sets the owning entity.
   */
  Component();

  /**
   * @brief Virtual destructor to allow proper cleanup in derived classes.
   */
  virtual ~Component() = default;

  /**
   * @brief Set the owner of the component.
   */
  void setOwner(const std::weak_ptr<Entity> &owner);

  /**
   * @brief Called when the parent entity is destroyed.
   * Used to unregister component in the ResourceManager.
   */
  virtual void onEntityDestroyed();
};

}
