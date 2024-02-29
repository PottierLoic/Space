#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include "Shader.hpp"
#include "Camera.hpp"
#include "Model/Model.hpp"

#include "Entity.hpp"
#include "Components/Component.hpp"
#include "Components/Transform.hpp"
#include "Components/Physic.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <string>
#include <iostream>

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

#if defined(IMGUI_IMPL_OPENGL_ES2)
  // GL ES 2.0 + GLSL 100
  const char* glsl_version = "#version 100";
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
  glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);
#elif defined(__APPLE__)
  // GL 3.2 + GLSL 150
  const char* glsl_version = "#version 150";
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // Required on Mac
#else
  // GL 3.0 + GLSL 130
  const char* glsl_version = "#version 130";
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
  //glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
  //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // 3.0+ only
#endif

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

  //TODO : Remove too
  // Scene creation
  Scene scene = Scene();
  scene.addEntity(new Entity("Test1"));
  scene.entities[0]->addComponent<Physic>(new Physic());

  // TODO: REMOVE OPENGL TESTS
  Shader testShader("../shaders/test.vs", "../shaders/test.fs", nullptr);

  // TODO: REMOVE TEST MODEL IMPORT
  Model testModel("../models/backpack/backpack.obj");

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