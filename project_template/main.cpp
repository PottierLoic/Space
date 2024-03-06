#include <string>
#include <iostream>

#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include "shader/shader.hpp"
#include "scene/scene.hpp"
#include "camera/camera.hpp" // maybe not stay here
#include "model/model.hpp" // maybe removed soon

/* TODO: REMOVE */
/* DEBUG */
#include "entity/entity.hpp"
#include "component/component.hpp"
#include "component/transform.hpp"
#include "component/physic.hpp"

// OPENGL TEST TODO REMOVE
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace SpaceEngine;

// Camera
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
float lastX =  1280.0f / 2.0;
float lastY =  720.0 / 2.0;
bool firstMouse = true;

// timing
float deltaTime = 0.0f;
float lastFrame = 0.0f;

void processInput(GLFWwindow* window) {
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    glfwSetWindowShouldClose(window, true);
  if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    camera.processKeyboard(FORWARD, deltaTime);
  if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    camera.processKeyboard(BACKWARD, deltaTime);
  if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    camera.processKeyboard(LEFT, deltaTime);
  if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    camera.processKeyboard(RIGHT, deltaTime);
}

/* DEBUG */

void framebufferSizeCallback(GLFWwindow* /*window*/, int width, int height) {
  glViewport(0, 0, width, height);
}

void mouseCallback(GLFWwindow* /*window*/, double xpos, double ypos) {
  if (firstMouse) {
    lastX = xpos;
    lastY = xpos;
    firstMouse = false;
  }

  float xoffset = xpos - lastX;
  float yoffset = lastY - ypos;

  lastX = xpos;
  lastY = ypos;

  camera.processMouseMovement(xoffset, yoffset);
}

void scrollCallback(GLFWwindow* /*window*/, double /*xoffset*/, double yoffset) {
  camera.processMouseScroll(static_cast<float>(yoffset));
}

int main() {
  // Initialize GLFW
  if (!glfwInit()) {
    std::cout << "Failed to initialize GLFW" << std::endl;
    return -1;
  }

  // Create a window with graphic context
  GLFWwindow* window = glfwCreateWindow(1280, 720, "Space Engine", nullptr, nullptr);
  if (window == NULL) {
    std::cout << "Failed to create GLFW window" << std::endl;
    glfwTerminate();
    return -1;
  }
  glfwMakeContextCurrent(window);
  // glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
  glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);
  glfwSetCursorPosCallback(window, mouseCallback);
  glfwSetScrollCallback(window, scrollCallback);


  // Initialize Glad
  if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress))) {
    std::cout << "Failed to initialize Glad" << std::endl;
    int error = glGetError();
    std::cout << "OpenGL Error: " << error << std::endl;
    glfwDestroyWindow(window);
    glfwTerminate();
    return -1;
  }

  stbi_set_flip_vertically_on_load(true);

  glEnable(GL_DEPTH_TEST);
  // TODO: REMOVE
  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

  //TODO : Remove too
  // Scene creation
  Scene scene = Scene();
  scene.addEntity(new Entity("Test1"));
  scene.entities[0]->addComponent<Physic>(new Physic());

  // TODO: REMOVE OPENGL TESTS
  // TODO: Find a way to use better path.
  Shader testShader("../../shaders/test.vs", "../../shaders/test.fs", nullptr);

  // TODO: REMOVE TEST MODEL IMPORT
  // TODO: Find a way to use better path.
  Model testModel("../../models/backpack/backpack.obj");


  // Main loop
  while (!glfwWindowShouldClose(window)) {
    float currentFrame = static_cast<float>(glfwGetTime());
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;

    processInput(window);


    int display_w, display_h;
    glfwGetFramebufferSize(window, &display_w, &display_h);
    glViewport(0, 0, display_w, display_h);
    glClearColor(0.45f, 0.55f, 0.60f, 1.00f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    testShader.use();

    glm::mat4 projection = glm::perspective(glm::radians(camera.zoom), 1280.0f / 720.0f, 0.1f, 100.0f);
    glm::mat4 view = camera.getViewMatrix();
    testShader.setMat4("projection", projection);
    testShader.setMat4("view", view);

    // render model
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
    model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
    testShader.setMat4("model", model);
    testModel.draw(testShader);

    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  // Cleanup GLFW
  glfwDestroyWindow(window);
  glfwTerminate();

  return 0;
}