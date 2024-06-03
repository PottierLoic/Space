#pragma once

#include <vector>

#include "glad/glad.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "../imgui/imgui_impl_glfw.h"
#include "../imgui/imgui_impl_opengl3.h"

#include "component/component.hpp"
#include "component/transform.hpp"

namespace SpaceEngine {

/*
TODO BIG COMMENT
*/
class Camera : public Component {
public:
  glm::vec3 front;            /* The front direction vector of the camera. */
  glm::vec3 up;               /* The up direction vector of the camera. */
  glm::vec3 right;            /* The right direction vector of the camera. */
  glm::vec3 worldUp;          /* The world up direction vector. */
  float yaw;                  /* The yaw angle of the camera. */
  float pitch;                /* The pitch angle of the camera. */
  float zoom;                 /* The zoom level of the camera. */
  // TODO: Use Vec4f instead of ImGui vector type.
  ImVec4 skyboxColor;          /* The color of the skybox. */

  /**
   * @brief Default constructor: Initializes a new empty Camera component.
   */
  Camera();

  /**
   * @brief Get the view matrix of the camera.
   * @return The view matrix.
   */
  glm::mat4 getViewMatrix();

private:
  /**
   * @brief Update camera direction vectors based on yaw and pitch angles.
   */
  void updateCameraVectors();

};

}
