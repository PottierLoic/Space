#pragma once

#include <iostream>

namespace SpaceEngine {

class Entity; // Forward declaration of Entity class to avoid circular dependencies.

/**
 * The Component class serves as a base class for components in the entity-component system.
 *
 * Attributes
 * - owner (Entity*): A pointer to the entity owning the component.
 *
 * Methods:
 * - Component(): Default constructor.
 * - virtual ~Component(): Virtual destructor to allow proper cleanup in derived classes.
 */
class Component {
protected:
  Entity* owner = nullptr; // Pointer to the entity owning the component.

public:
  /**
   * @brief Default constructor.
   * @param owner (Entity*): A pointer to the entity that store the component.
   */
  Component(Entity* owner);

  /**
   * @brief Virtual destructor to allow proper cleanup in derived classes.
   */
  virtual ~Component();
};

}