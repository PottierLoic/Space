#pragma once

#include "glad/glad.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include <vector>

enum CameraMovement {
  FORWARD,
  BACKWARD,
  LEFT,
  RIGHT
};

const float YAW = -90.0f;
const float PITCH = 0.0f;
const float SPEED = 2.5f;
const float SENSITIVITY = 0.1f;
const float ZOOM = 45.0f;

class Camera {
public:
  // Camera attributes
  glm::vec3 position;
  glm::vec3 front;
  glm::vec3 up;
  glm::vec3 right;
  glm::vec3 worldUp;

  // Euler angles
  float yaw;
  float pitch;

  // Options
  float movementSpeed;
  float mouseSensitivity;
  float zoom;

  // Constructor with vector
  Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = YAW, float pitch = PITCH);

  // Constructor with scalars
  Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch);

  glm::mat4 getViewMatrix();

  void processKeyboard(CameraMovement direction, float deltaTime);
  void processMouseMovement(float xoffset, float yoffset, bool constrainPitch = true);
  void processMouseScoll(float yoffset);

private:
  void updateCameraVectors();
};
