#pragma once

#include <iostream>

namespace SpaceEngine {

/**
 * The Component class serves as a base class for components in the entity-component system.
 *
 * Methods:
 * - Component(): Default constructor.
 * - virtual ~Component(): Virtual destructor to allow proper cleanup in derived classes.
 * - virtual void display(): Virtual method to display component properties in the user interface.
 */
class Component {
public:
  /**
   * @brief Default constructor.
   */
  Component();

  /**
   * @brief Virtual destructor to allow proper cleanup in derived classes.
   */
  virtual ~Component();

};

}