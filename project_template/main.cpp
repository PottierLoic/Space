#include <string>
#include <iostream>

#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include "shader/shader.hpp"
#include "scene/scene.hpp"
#include "model/model.hpp" // maybe removed soon

/* TODO: REMOVE */
/* DEBUG */
#include "entity/entity.hpp"
#include "component/component.hpp"
#include "component/transform.hpp"
#include "component/physic.hpp"
#include "component/model_renderer.hpp"
#include "component/camera.hpp"


// OPENGL TEST TODO REMOVE
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace SpaceEngine;

// timing
float deltaTime = 0.0f;
float lastFrame = 0.0f;

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

  //TODO : Remove too
  // Scene creation
  Scene scene = Scene();
  scene.addEntity(Entity::create("Test"));
  scene.entities[1]->addComponent<ModelRenderer>();
  scene.entities[1]->getComponent<ModelRenderer>()->setModel("./models/dio/dio.fbx");

  // TODO: REMOVE OPENGL TESTS
  // TODO: Find a way to use better path.
  Shader shader("./shaders/test.vs", "./shaders/test.fs", nullptr);

  // Main loop
  while (!glfwWindowShouldClose(window)) {
    float currentFrame = static_cast<float>(glfwGetTime());
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;

    int display_w, display_h;
    glfwGetFramebufferSize(window, &display_w, &display_h);
    glViewport(0, 0, display_w, display_h);
    glClearColor(0.45f, 0.55f, 0.60f, 1.00f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    std::shared_ptr<Camera> cam = scene.selectedCamera.lock();
    glClearColor(cam->skyboxColor.x, cam->skyboxColor.y, cam->skyboxColor.z, cam->skyboxColor.w);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    shader.use();
    glm::mat4 projection = glm::perspective(glm::radians(cam->zoom), 1920.0f / 1080.0f, 0.1f, 100.0f);
    projection[1][1] *= -1;
    glm::mat4 view = cam->getViewMatrix();
    shader.setMat4("projection", projection);
    shader.setMat4("view", view);
    for (auto& entity : scene.entities) {
      auto modelRenderer = entity->getComponent<ModelRenderer>();
      if (modelRenderer != nullptr) {
        auto tf = entity->getComponent<Transform>();
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(tf->position.x(), tf->position.y(), tf->position.z()));
        model = glm::scale(model, glm::vec3(tf->scale.x(), tf->scale.y(), tf->scale.z()));
        model = glm::rotate(model, glm::radians(tf->rotation.x()), glm::vec3(1.0f, 0.0f, 0.0f));
        model = glm::rotate(model, glm::radians(tf->rotation.y()), glm::vec3(0.0f, 1.0f, 0.0f));
        model = glm::rotate(model, glm::radians(tf->rotation.z()), glm::vec3(0.0f, 0.0f, 1.0f));
        shader.setMat4("model", model);
        modelRenderer->model->draw(shader);
      }
    }

    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  // Cleanup GLFW
  glfwDestroyWindow(window);
  glfwTerminate();

  return 0;
}