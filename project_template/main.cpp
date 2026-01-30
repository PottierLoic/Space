#include <iostream>
#include <string>

#include "model/model.hpp"  // maybe removed soon
#include "renderer/renderer.hpp"
#include "scene/scene.hpp"
#include "shader/shader.hpp"
#include "space/space.hpp"

/* TODO: REMOVE */
/* DEBUG */
#include "component/camera.hpp"
#include "component/component.hpp"
#include "component/model_renderer.hpp"
#include "component/physic.hpp"
#include "component/transform.hpp"
#include "entity/entity.hpp"

// OPENGL TEST TODO REMOVE
#define STB_IMAGE_IMPLEMENTATION
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "stb_image.h"

using namespace SpaceEngine;

// timing
float deltaTime = 0.0f;
float lastFrame = 0.0f;

std::unique_ptr<Renderer> renderer;

/* DEBUG */

void framebufferSizeCallback(GLFWwindow* /*window*/, int width, int height) {
  glViewport(0, 0, width, height);
}

int main() {
  // Initialize GLFW
  if (!glfwInit()) {
    std::cout << "Failed to initialize GLFW" << std::endl;
    return -1;
  }

#if defined(IMGUI_IMPL_OPENGL_ES2)
  const char* glsl_version = "#version 100";
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
  glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);
#elif defined(__APPLE__)
  const char* glsl_version = "#version 150";
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#else
  const char* glsl_version = "#version 130";
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
#endif

  // Create a window with graphic context
  GLFWwindow* window = glfwCreateWindow(1280, 720, "Space Engine", nullptr, nullptr);
  if (window == NULL) {
    std::cout << "Failed to create GLFW window" << std::endl;
    glfwTerminate();
    return -1;
  }

  glfwMakeContextCurrent(window);
  glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
  glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);

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

  // Initialize renderer
  renderer = std::make_unique<Renderer>();
  if (!renderer->initialize(1920, 1080)) {  // TODO: Not hardcode resolution
    std::cout << "Failed to initialize renderer" << std::endl;
    return -1;
  }

  // TODO : Remove too NOT SURE NOW
  // Scene creation
  auto space = std::make_shared<Space>("./", "template_space");
  auto test = Entity::create("test");
  test->addComponent<ModelRenderer>();
  auto testRenderer = test->getComponent<ModelRenderer>();
  testRenderer->path = "./models/dio/dio.fbx";
  testRenderer->setModel();
  space->currentScene->addEntity(test);

  // TODO: REMOVE OPENGL TESTS
  // TODO: Find a way to use better path.
  Shader shader("./shaders/test.vs", "./shaders/test.fs", nullptr);

  // Main loop
  while (!glfwWindowShouldClose(window)) {
    float currentFrame = static_cast<float>(glfwGetTime());
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;

    // TODO: should be processing inputs around here using a new core Class

    if (space->currentScene && space->currentScene->selectedCamera.lock()) {
      auto camera = space->currentScene->selectedCamera.lock();
      renderer->render(camera->getViewMatrix(), camera->getProjectionMatrix(), space->currentScene);
    }

    int display_w, display_h;
    glfwGetFramebufferSize(window, &display_w, &display_h);
    glViewport(0, 0, display_w, display_h);
    glClearColor(0.45f, 0.55f, 0.60f, 1.00f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  // Cleanup GLFW
  glfwDestroyWindow(window);
  glfwTerminate();

  return 0;
}