#include "test.hpp"
#include "entity/entity.hpp"
#include "serializer/serializer.hpp"
#include "nlohmann/json.hpp"
using json = nlohmann::json;
using namespace SpaceEngine;

int testSerializeComponent() {
  // Transform test
  std::shared_ptr<Transform> tf = std::make_shared<Transform>(Transform("test-transform"));
  tf->position = Vec3f(1.0, 3.0, 5.0);
  tf->rotation = Vec3f(7.0, 9.0, 11.0);
  tf->scale = Vec3f(12.0, 13.0, 15.0);
  json j = Serializer::serialize(tf);
  std::shared_ptr<Transform> tf2 = std::dynamic_pointer_cast<Transform>(Serializer::deserializeComponent(j));
  custom_assert(tf->name == tf2->name, "Transform name serialization/deserialization failed")
  custom_assert(tf->position == tf2->position, "Transform position serialization/deserialization failed");
  custom_assert(tf->rotation == tf2->rotation, "Transform rotation serialization/deserialization failed");
  custom_assert(tf->scale == tf2->scale, "Transform scale serialization/deserialization failed");

  // TODO: add other components types
  std::shared_ptr<Camera> cam = std::make_shared<Camera>();
  cam->front = glm::vec3(0.0f, 0.0f, -1.0f);
  cam->up = glm::vec3(0.0f, 1.0f, 0.0f);
  cam->right = glm::vec3(1.0f, 0.0f, 0.0f);
  cam->worldUp = glm::vec3(0.0f, 1.0f, 0.0f);
  cam->yaw = -90.0f;
  cam->pitch = 0.0f;
  cam->zoom = 45.0f;
  cam->skyboxColor = ImVec4(0.1f, 0.2f, 0.3f, 1.0f);
  json cam_json = Serializer::serialize(cam);
  std::shared_ptr<Camera> cam2 = std::dynamic_pointer_cast<Camera>(Serializer::deserializeComponent(cam_json));
  custom_assert(cam->front == cam2->front, "Camera front serialization/deserialization failed");
  custom_assert(cam->up == cam2->up, "Camera up serialization/deserialization failed");
  custom_assert(cam->right == cam2->right, "Camera right serialization/deserialization failed");
  custom_assert(cam->worldUp == cam2->worldUp, "Camera worldUp serialization/deserialization failed");
  custom_assert(cam->yaw == cam2->yaw, "Camera yaw serialization/deserialization failed");
  custom_assert(cam->pitch == cam2->pitch, "Camera pitch serialization/deserialization failed");
  custom_assert(cam->zoom == cam2->zoom, "Camera zoom serialization/deserialization failed");
  custom_assert(cam->skyboxColor.x == cam2->skyboxColor.x && cam->skyboxColor.y == cam2->skyboxColor.y &&
                cam->skyboxColor.z == cam2->skyboxColor.z && cam->skyboxColor.w == cam2->skyboxColor.w,
                "Camera skyboxColor serialization/deserialization failed");
  return 0;
}
