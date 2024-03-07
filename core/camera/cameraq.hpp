// #pragma once

// #include "glad/glad.h"
// #include "glm/glm.hpp"
// #include "glm/gtc/matrix_transform.hpp"

// #include <vector>

// namespace SpaceEngine {

// enum CameraMovement {
//   FORWARD,
//   BACKWARD,
//   LEFT,
//   RIGHT
// };

// const float YAW = -90.0f;
// const float PITCH = 0.0f;
// const float SPEED = 2.5f;
// const float SENSITIVITY = 0.1f;
// const float ZOOM = 45.0f;

// /**
//  * The Camera class represents a 3D camera in a virtual scene.
//  *
//  * Properties:
//  * - position (glm::vec3): The position of the camera.
//  * - front (glm::vec3): The front direction vector of the camera.
//  * - up (glm::vec3): The up direction vector of the camera.
//  * - right (glm::vec3): The right direction vector of the camera.
//  * - worldUp (glm::vec3): The world up direction vector.
//  * - yaw (float): The yaw angle of the camera.
//  * - pitch (float): The pitch angle of the camera.
//  * - movementSpeed (float): The speed at which the camera moves.
//  * - mouseSensitivity (float): The sensitivity of the mouse movement.
//  * - zoom (float): The zoom level of the camera.
//  *
//  * Methods:
//  * - Camera(glm::vec3 position, glm::vec3 up, float yaw, float pitch): Constructor with vector.
//  * - Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch): Constructor with scalars.
//  * - glm::mat4 getViewMatrix(): Get the view matrix of the camera.
//  * - void processKeyboard(CameraMovement direction, float deltaTime): Process keyboard input to move the camera.
//  * - void processMouseMovement(float xoffset, float yoffset, bool constrainPitch = true): Process mouse movement to update camera angles.
//  * - void processMouseScroll(float yoffset): Process mouse scroll to update zoom level.
//  */
// class Camera {
// public:
//   glm::vec3 position;         /* The position of the camera. */
//   glm::vec3 front;            /* The front direction vector of the camera. */
//   glm::vec3 up;               /* The up direction vector of the camera. */
//   glm::vec3 right;            /* The right direction vector of the camera. */
//   glm::vec3 worldUp;          /* The world up direction vector. */
//   float yaw;                  /* The yaw angle of the camera. */
//   float pitch;                /* The pitch angle of the camera. */
//   float movementSpeed;        /* The speed at which the camera moves. */
//   float mouseSensitivity;     /* The sensitivity of the mouse movement. */
//   float zoom;                 /* The zoom level of the camera. */

//   /**
//    * @brief Constructor with vector.
//    * @param position: The position of the camera.
//    * @param up: The up direction vector of the camera.
//    * @param yaw: The yaw angle of the camera.
//    * @param pitch: The pitch angle of the camera.
//    */
//   Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = -90.0f, float pitch = 0.0f);

//   /**
//    * @brief Constructor with scalars.
//    * @param posX: X-coordinate of the position.
//    * @param posY: Y-coordinate of the position.
//    * @param posZ: Z-coordinate of the position.
//    * @param upX: X-coordinate of the up direction vector.
//    * @param upY: Y-coordinate of the up direction vector.
//    * @param upZ: Z-coordinate of the up direction vector.
//    * @param yaw: The yaw angle of the camera.
//    * @param pitch: The pitch angle of the camera.
//    */
//   Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch);

//   /**
//    * @brief Get the view matrix of the camera.
//    * @return The view matrix.
//    */
//   glm::mat4 getViewMatrix();

//   /**
//    * @brief Process keyboard input to move the camera.
//    * @param direction: The direction of movement (FORWARD, BACKWARD, LEFT, RIGHT).
//    * @param deltaTime: Time between the current frame and the last frame.
//    */
//   void processKeyboard(enum CameraMovement direction, float deltaTime);

//   /**
//    * @brief Process mouse movement to update camera angles.
//    * @param xoffset: Horizontal offset of the mouse movement.
//    * @param yoffset: Vertical offset of the mouse movement.
//    * @param constrainPitch: Whether to constrain the pitch angle.
//    */
//   void processMouseMovement(float xoffset, float yoffset, bool constrainPitch = true);

//   /**
//    * @brief Process mouse scroll to update zoom level.
//    * @param yoffset: Vertical offset of the mouse scroll.
//    */
//   void processMouseScroll(float yoffset);

// private:
//   /**
//    * @brief Update camera direction vectors based on yaw and pitch angles.
//    */
//   void updateCameraVectors();
// };

// }
