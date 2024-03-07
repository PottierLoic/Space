#pragma once

#include "string"
#include "vector"
#include "algorithm"

#include "entity/entity.hpp"

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
 * - Scene(std::string name): Initializes a new scene with the specified name.
 *
 * Methods:
 * - void addEntity(Entity* obj): Adds an Entity to the scene.
 * - void removeEntity(Entity* obj): Removes an Entity from the scene.
 */
class Scene{
public:
  std::string name;

  // Vector of pointers to Entity contained within the scene
  std::vector<Entity*> entities;

  Camera selectedCamera;

  Scene();                    // Initializes a new empty scene with a default name.
  Scene(std::string name);    // Initializes a new scene with the specified name.

  /*
   * Add an Entity to the scene.
   * @param ent: Reference to the entity.
   */
  void addEntity(Entity* ent);

  /*
   * Remove an Entity from the scene.
   * @param ent: Reference to the entity.
   */
  void removeEntity(Entity* ent);
};

}
