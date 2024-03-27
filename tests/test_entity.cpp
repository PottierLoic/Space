#include "test.hpp"
#include "entity/entity.hpp"
#include "component/camera.hpp"

using namespace SpaceEngine;

int testEntity() {
  auto ent1 = Entity::create("ent1");
  auto ent2 = Entity::create("ent2");

  auto tf1 = ent1->getComponent<Transform>();
  custom_assert(tf1 != nullptr, "Entity getComponent failed.");

  custom_assert(ent1->addComponent<Transform>("test") == false, "Entity adding duplicate component prevention failed.");

  ent1->addComponent<Camera>();
  custom_assert(ent1->getComponent<Camera>() != nullptr, "Entity addComponent failed.");

  ent1->getComponent<Transform>()->position.x() = 25.74f;
  custom_assert(ent1->getComponent<Transform>()->position.x() == 25.74f, "Entity component modification failed")

  ent1->removeComponent<Camera>();
  custom_assert(ent1->getComponent<Camera>() == nullptr, "Entity removeComponent failed");

  ent1->addChild(ent2);
  custom_assert(ent1->findChild("ent2") == ent2, "Entity findChild with name failed");

  ent1->removeChild("ent2");
  custom_assert(ent1->findChild("ent2") == nullptr, "Entity removeChild with name failed");
  return 0;
}
