#include <string>
#include <iostream>

#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

#include "editor_gui/editor_gui.hpp"
#include "editor_camera/editor_camera.hpp"
#include "shader/shader.hpp"
#include "space/space.hpp"
#include "renderer/renderer.hpp"

/* TODO: REMOVE */
#include "entity/entity.hpp"

#include "component/camera.hpp"
#include "component/model_renderer.hpp"
#include "log/logger.hpp"
#include "serializer/serializer.hpp"

// OPENGL TEST TODO REMOVE
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

using namespace SpaceEngine;
using namespace SpaceEditor;

// Camera
EditorCamera camera;
float lastX =  1920.0f / 2.0;
float lastY =  1080.0 / 2.0;
bool firstMouse = true;
bool inspectorFocus = false; // TODO: move in the inspector ?

// timing
float deltaTime = 0.0f;
float lastFrame = 0.0f;

// Renderers
std::unique_ptr<Renderer> sceneRenderer;
std::unique_ptr<Renderer> renderViewRenderer;

void processInput(GLFWwindow* window) {
  if (inspectorFocus) {
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
}

/* DEBUG */
void framebufferSizeCallback(GLFWwindow* /*window*/, const int width, const int height) {
  glViewport(0, 0, width, height);
  if (sceneRenderer) {
    sceneRenderer->resize(width, height);
  }
  if (renderViewRenderer) {
    renderViewRenderer->resize(width, height);
  }
}

void mouseCallback(GLFWwindow* window, const double px, const double py) {
  if (inspectorFocus) {
    const auto x = static_cast<float>(px);
    const auto y = static_cast<float>(py);
    if (firstMouse) {
      lastX = x;
      lastY = y;
      firstMouse = false;
    }

    const float xOffset = x - lastX;
    const float yOffset = lastY - y;

    lastX = x;
    lastY = y;

    camera.processMouseMovement(xOffset, yOffset);

    int display_w, display_h;
    glfwGetWindowSize(window, &display_w, &display_h);
    glfwSetCursorPos(window, display_w / 2.0, display_h / 2.0);
    lastX = static_cast<float>(display_w) / 2.0f;
    lastY = static_cast<float>(display_h) / 2.0f;
  }
}

void scrollCallback(GLFWwindow* /*window*/, double /*xOffset*/, const double yOffset) {
  camera.processMouseScroll(static_cast<float>(yOffset));
}

int main() {
  // Initialize GLFW
  if (!glfwInit()) {
    std::cout << "Failed to initialize GLFW" << std::endl;
    return -1;
  }

  #if defined(IMGUI_IMPL_OPENGL_ES2)
    auto glsl_version = "#version 100";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);
  #elif defined(__APPLE__)
    auto glsl_version = "#version 150";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
  #else
    auto glsl_version = "#version 130";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
  #endif

  GLFWwindow* window = glfwCreateWindow(1920, 1080, "Space Engine", nullptr, nullptr);
  if (window == nullptr) {
    std::cout << "Failed to create GLFW window" << std::endl;
    glfwTerminate();
    return -1;
  }

  glfwMakeContextCurrent(window);
  glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);
  glfwSetCursorPosCallback(window, mouseCallback);
  glfwSetScrollCallback(window, scrollCallback);

  // Initialize Glad
  if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress))) {
    std::cout << "Failed to initialize Glad" << std::endl;
    const int error = glGetError();
    std::cout << "OpenGL Error: " << error << std::endl;
    glfwDestroyWindow(window);
    glfwTerminate();
    return -1;
  }

  glEnable(GL_DEPTH_TEST);

  // Initialize renderers
  sceneRenderer = std::make_unique<Renderer>();
  renderViewRenderer = std::make_unique<Renderer>();
  
  if (!sceneRenderer->initialize(1920, 1080) || !renderViewRenderer->initialize(1920, 1080)) {
    std::cout << "Failed to initialize renderers" << std::endl;
    return -1;
  }

  // Setup ImGui context
  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  ImGuiIO& io = ImGui::GetIO(); (void)io;
  io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
  io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
  io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
  io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

  // Setup Platform/Renderer backends
  ImGui_ImplGlfw_InitForOpenGL(window, true);
  ImGui_ImplOpenGL3_Init(glsl_version);

  auto gui = EditorGui(sceneRenderer->getRenderedTexture(), renderViewRenderer->getRenderedTexture());

  //TODO : Remove too
  auto space = std::make_shared<Space>("./", "test_space");
  gui.space = space;

  // Examples
  auto test = Entity::create("test");
  test->addComponent<ModelRenderer>();
  auto testRenderer = test->getComponent<ModelRenderer>();
  testRenderer->path = "./models/dio/dio.fbx";
  testRenderer->setModel();
  space->currentScene->addEntity(test);

  // read content from test file
  // if (std::ifstream file("./test.space"); file.is_open()) {
  //   json j;
  //   file >> j;
  //   file.close();
  //   auto scene = Serializer::deserializeScene(j);
  //   space->currentScene = scene;
  // }

  // Main loop
  while (!glfwWindowShouldClose(window)) {
    const auto currentFrame = static_cast<float>(glfwGetTime());
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;

    processInput(window);

    // Rendering scene and render view in editor
    sceneRenderer->render(camera.getEditorViewMatrix(), camera.getProjectionMatrix(), space->currentScene);
    if (space->currentScene && space->currentScene->selectedCamera.lock()) {
      const auto sceneCamera = space->currentScene->selectedCamera.lock();
      renderViewRenderer->render(sceneCamera->getViewMatrix(), sceneCamera->getProjectionMatrix(), space->currentScene);
    }

    // Clear the main framebuffer
    int display_w, display_h;
    glfwGetFramebufferSize(window, &display_w, &display_h);
    glViewport(0, 0, display_w, display_h);
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
    ImGui::DockSpaceOverViewport();

    if (!inspectorFocus && gui.sceneHovered && io.MouseDown[1]) {
      inspectorFocus = true;
      glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    } else if (inspectorFocus && !io.MouseDown[1]) {
      inspectorFocus = false;
      glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
      firstMouse = true;
    }

    gui.display();
    ImGui::Render();
    GLFWwindow* backup_current_context = glfwGetCurrentContext();
    ImGui::UpdatePlatformWindows();
    ImGui::RenderPlatformWindowsDefault();
    glfwMakeContextCurrent(backup_current_context);

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
