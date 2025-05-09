#pragma once

#include <vector>

#include "glad/glad.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "component/camera.hpp"

namespace SpaceEditor {

enum CameraMovement {
  FORWARD,
  BACKWARD,
  LEFT,
  RIGHT
};

constexpr float SPEED = 2.5f;
constexpr float SENSITIVITY = 0.1f;
// TODO: edit this summary
/**
 * The EditorCamera class represents a 3D camera in a virtual scene.
 * It is based on the Camera component defined in core.
 *
 * Properties:
 * - position (glm::vec3): The position of the camera.
 * - front (glm::vec3): The front direction vector of the camera.
 * - up (glm::vec3): The up direction vector of the camera.
 * - right (glm::vec3): The right direction vector of the camera.
 * - worldUp (glm::vec3): The world up direction vector.
 * - yaw (float): The yaw angle of the camera.
 * - pitch (float): The pitch angle of the camera.
 * - movementSpeed (float): The speed at which the camera moves.
 * - mouseSensitivity (float): The sensitivity of the mouse movement.
 * - zoom (float): The zoom level of the camera.
 *
 * Methods:
 * - EditorCamera(glm::vec3 position, glm::vec3 up, float yaw, float pitch): Constructor with vector.
 * - glm::mat4 getViewMatrix(): Get the view matrix of the camera.
 * - void processKeyboard(CameraMovement direction, float deltaTime): Process keyboard input to move the camera.
 * - void processMouseMovement(float xoffset, float yoffset, bool constrainPitch = true): Process mouse movement to update camera angles.
 * - void processMouseScroll(float yoffset): Process mouse scroll to update zoom level.
 */
class EditorCamera final : public SpaceEngine::Camera {
public:
  glm::vec3 position{};         /* The position of the camera. */
  float movementSpeed = SPEED;        /* The speed at which the camera moves. */
  float mouseSensitivity = SENSITIVITY;     /* The sensitivity of the mouse movement. */

  /**
   * @brief Constructor with vector.
   */
  explicit EditorCamera();

  /**
   * @brief Process keyboard input to move the camera.
   * @param direction: The direction of movement (FORWARD, BACKWARD, LEFT, RIGHT).
   * @param deltaTime: Time between the current frame and the last frame.
   */
  void processKeyboard(enum CameraMovement direction, float deltaTime);

  /**
   * @brief Process mouse movement to update camera angles.
   * @param xOffset: Horizontal offset of the mouse movement.
   * @param yOffset: Vertical offset of the mouse movement.
   * @param constrainPitch: Whether to constrain the pitch angle.
   */
  void processMouseMovement(float xOffset, float yOffset, bool constrainPitch = true);

  /**
   * @brief Process mouse scroll to update zoom level.
   * @param yOffset: Vertical offset of the mouse scroll.
   */
  void processMouseScroll(float yOffset);

    /**
   * @brief Get the view matrix of the camera.
   * @return The view matrix.
   */
  [[nodiscard]] glm::mat4 getEditorViewMatrix() const;

  /**
   * @brief Get the projection matrix of the camera.
   * @return The projection matrix.
   */
  [[nodiscard]] glm::mat4 getEditorProjectionMatrix() const;
};

}