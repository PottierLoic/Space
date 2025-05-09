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
  enum class ProjectionType {
    PERSPECTIVE,
    ORTHOGRAPHIC
  };

  // Camera orientation
  glm::vec3 front;            /* The front direction vector of the camera. */
  glm::vec3 up;               /* The up direction vector of the camera. */
  glm::vec3 right;            /* The right direction vector of the camera. */
  glm::vec3 worldUp;          /* The world up direction vector. */
  float yaw;                  /* The yaw angle of the camera. */
  float pitch;                /* The pitch angle of the camera. */

  // Projection settings
  ProjectionType projectionType = ProjectionType::PERSPECTIVE;  /* The type of projection to use */
  float fieldOfView = 45.0f;  /* The field of view angle in degrees (previously named zoom) */
  float aspectRatio = 16.0f/9.0f;  /* The aspect ratio of the camera view */
  float nearPlane = 0.1f;     /* The near clipping plane distance */
  float farPlane = 100.0f;    /* The far clipping plane distance */

  // Orthographic settings
  float orthographicSize = 5.0f;  /* The size of the orthographic view (half-height) */

  // Visual settings
  ImVec4 skyboxColor;         /* The color of the skybox. */

  /**
   * @brief Default constructor: Initializes a new empty Camera component.
   */
  Camera();

  /**
   * @brief Get the view matrix of the camera.
   * @return The view matrix.
   */
  glm::mat4 getViewMatrix();

  /**
   * @brief Get the projection matrix of the camera.
   * @return The projection matrix.
   */
  glm::mat4 getProjectionMatrix();

  /**
   * @brief Update camera direction vectors based on yaw and pitch angles.
   */
  void updateCameraVectors();
};

}
