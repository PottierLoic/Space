#pragma once

#include <memory>
#include <string>
#include <vector>
#include <algorithm>

#include "entity/entity.hpp"
#include "component/camera.hpp"

namespace SpaceEngine {

/*
 * The Scene class represents a container for managing Entities in a scene.
 *
 * Properties:
 * - name (std::string): The name of the scene.
 * - objects (std::vector<Entity*>): A vector of pointers to all Entities contained within the scene.
 *
 * Constructors:
 * - Scene(): Initializes a new empty scene with a default name.
 *
 * Methods:
 * - void addEntity(Entity* obj): Adds an Entity to the scene.
 * - void removeEntity(Entity* obj): Removes an Entity from the scene.
 */
class Scene{
public:
  std::string name;

  // Vector of pointers to Entity contained within the scene
  std::vector<std::shared_ptr<Entity>> entities;

  // Main camera component in the scene. Used to render game.
  std::weak_ptr<Camera> selectedCamera;

  /**
   * @brief Initialize a Scene with default name.
   */
  Scene();

  /**
   * @brief Add an Entity to the scene.
   * @param ent: Reference to the entity.
   */
  void addEntity(std::shared_ptr<Entity> ent);

  /** TODO CHECK IF INDEX IS GOOD AND REWORK IF NEEDED
   * @brief Remove an Entity from the scene.
   * @param index: index of the entity.
   */
  void removeEntity(int index);
};

}
