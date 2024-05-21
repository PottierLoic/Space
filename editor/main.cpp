#include <string>
#include <iostream>

#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

#include "editor_gui/editor_gui.hpp"
#include "editor_camera/editor_camera.hpp" // maybe not stay here
#include "model/model.hpp" // maybe removed soon
#include "shader/shader.hpp"

/* TODO: REMOVE */
/* DEBUG */
#include "entity/entity.hpp"
#include "component/component.hpp"
#include "component/transform.hpp"
#include "component/physic.hpp"
#include "component/camera.hpp"
#include "component/model_renderer.hpp"
#include "log/logger.hpp"

// OPENGL TEST TODO REMOVE
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace SpaceEngine;
using namespace SpaceEditor;

// Camera
EditorCamera camera(glm::vec3(0.0f, 0.0f, 3.0f));
float lastX =  1920.0f / 2.0;
float lastY =  1080.0 / 2.0;
bool firstMouse = true;
bool inspectorFocus = false;

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

void mouseCallback(GLFWwindow* window, double xpos, double ypos) {
  if (inspectorFocus) {
    if (firstMouse) {
      lastX = xpos;
      lastY = ypos;
      firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos;

    lastX = xpos;
    lastY = ypos;

    camera.processMouseMovement(xoffset, yoffset);

    int display_w, display_h;
    glfwGetWindowSize(window, &display_w, &display_h);
    glfwSetCursorPos(window, display_w / 2.0, display_h / 2.0);
    lastX = display_w / 2.0;
    lastY = display_h / 2.0;
  }
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
  GLFWwindow* window = glfwCreateWindow(1920, 1080, "Space Engine", nullptr, nullptr);
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

  glEnable(GL_DEPTH_TEST);
  // stbi_set_flip_vertically_on_load(false);

  // test framebuffer
  unsigned int fbo;
  glGenFramebuffers(1, &fbo);
  glBindFramebuffer(GL_FRAMEBUFFER, fbo);

  unsigned int textureColorbuffer;
  glGenTextures(1, &textureColorbuffer);
  glBindTexture(GL_TEXTURE_2D, textureColorbuffer);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 1920, 1080, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textureColorbuffer, 0);

  unsigned int rbo;
  glGenRenderbuffers(1, &rbo);
  glBindRenderbuffer(GL_RENDERBUFFER, rbo);
  glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, 1920, 1080);
  glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo);

  if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
    std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
  glBindFramebuffer(GL_FRAMEBUFFER, 0);

  // Setup ImGui context
  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  ImGuiIO& io = ImGui::GetIO(); (void)io;
  io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
  io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

  // Setup Platform/Renderer backends
  ImGui_ImplGlfw_InitForOpenGL(window, true);
  ImGui_ImplOpenGL3_Init(glsl_version);

  // Maximize the window
  // glfwMaximizeWindow(window);

  //TODO : Remove too
  // Scene creation
  Scene scene = Scene();

  // Examples
  auto backpack = Entity::create("Backpack");
  backpack->addComponent<ModelRenderer>();

  auto backpackRenderer = backpack->getComponent<ModelRenderer>();
  backpackRenderer->setModel("./models/dio/dio.fbx");
  scene.addEntity(backpack);

  // gui creation
  EditorGui gui = EditorGui(std::make_shared<Scene>());
  gui.selectedEntity = scene.entities[0];

  // TODO: REMOVE OPENGL TESTS
  // TODO: Find a way to use better path.
  Shader shader("./shaders/test.vs", "./shaders/test.fs", nullptr);

  // Main loop
  while (!glfwWindowShouldClose(window)) {
    float currentFrame = static_cast<float>(glfwGetTime());
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;

    processInput(window);

    glBindFramebuffer(GL_FRAMEBUFFER, fbo);
    glEnable(GL_DEPTH_TEST);
    glViewport(0, 0, 1920, 1080);

    std::shared_ptr<Camera> cam = scene.selectedCamera.lock();
    glClearColor(cam->skyboxColor.x, cam->skyboxColor.y, cam->skyboxColor.z, cam->skyboxColor.w);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    shader.use();
    glm::mat4 projection = glm::perspective(glm::radians(camera.zoom), 1920.0f / 1080.0f, 0.1f, 100.0f);
    projection[1][1] *= -1;
    glm::mat4 view = camera.getViewMatrix();
    shader.setMat4("projection", projection);
    shader.setMat4("view", view);
    for (auto& entity : scene.entities) {
      auto modelRenderer = entity->getComponent<ModelRenderer>();
      if (modelRenderer && modelRenderer->model) {
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

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    int display_w, display_h;
    glfwGetFramebufferSize(window, &display_w, &display_h);
    glViewport(0, 0, display_w, display_h);
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    ImGui::Begin("Scene");

    if (!inspectorFocus && ImGui::IsWindowHovered() && io.MouseDown[1]) {
      inspectorFocus = true;
      glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    } else if (inspectorFocus && !io.MouseDown[1]) {
      inspectorFocus = false;
      glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
      firstMouse = true;
    }

    ImVec2 window_size = ImGui::GetContentRegionAvail();
    float aspect_ratio = 1920.0f / 1080.0f;
    float window_aspect_ratio = window_size.x / window_size.y;

    ImVec2 image_size;
    if (window_aspect_ratio > aspect_ratio) {
      image_size = ImVec2(window_size.y * aspect_ratio, window_size.y);
    } else {
      image_size = ImVec2(window_size.x, window_size.x / aspect_ratio);
    }

    ImGui::Image((void*)(intptr_t)textureColorbuffer, image_size);
    ImGui::End();

    gui.display();
    ImGui::Render();

    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    glfwSwapBuffers(window);
    glfwPollEvents();

  }

  // Cleanup ImGui
  ImGui_ImplOpenGL3_Shutdown();
  ImGui_ImplGlfw_Shutdown();
  ImGui::DestroyContext();

  // Cleanup GLFW
  glfwDestroyWindow(window);
  glfwTerminate();

  return 0;
}