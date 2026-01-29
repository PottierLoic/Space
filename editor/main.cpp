#include <string>
#include <iostream>

#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

#include "editor_gui/editor_gui.hpp"
#include "editor_camera/editor_camera.hpp"
#include "shader/shader.hpp"
#include "renderer/renderer.hpp"

/* TODO: REMOVE */
#include "input/input.hpp" // TODO: switch from using glfw input system to the engine input system
#include "ecs/world.hpp"

#include "component/camera.hpp"
#include "component/model_renderer.hpp"
#include "component/audio_source.hpp"
#include "log/logger.hpp"

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

// timing
float deltaTime = 0.0f;
float lastFrame = 0.0f;

// Renderers
std::unique_ptr<Renderer> sceneRenderer;
std::unique_ptr<Renderer> renderViewRenderer;

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

  // Input initialization
  Input::init(window);

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
  auto scene = std::make_shared<Scene>();
  gui.scene = scene;

  // TODO : remove too (Examples entities)
  auto test = scene->world.create();
  scene->world.add_component<Transform>(test, Transform{"test"});
  auto& mr = scene->world.add_component<ModelRenderer>(test, ModelRenderer{});
  mr.path = "./models/dio/dio.fbx";
  mr.setModel();

  // Main loop
  while (!glfwWindowShouldClose(window)) {
    const auto currentFrame = static_cast<float>(glfwGetTime());
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;

    Input::update();
    Input::dispatchBindings(); // TODO only supposed to be in the game code

    if (gui.inspectorFocus) {
      // Keyboard inputs handling
      if (Input::isKeyPressed(KeyCode::W))
        camera.processKeyboard(FORWARD, deltaTime);
      if (Input::isKeyPressed(KeyCode::S))
        camera.processKeyboard(BACKWARD, deltaTime);
      if (Input::isKeyPressed(KeyCode::A))
        camera.processKeyboard(LEFT, deltaTime);
      if (Input::isKeyPressed(KeyCode::D))
        camera.processKeyboard(RIGHT, deltaTime);

      // Mouse movements handling
      const float currentX = Input::getMouseX();
      const float currentY = Input::getMouseY();
      if (firstMouse) {
        lastX = currentX;
        lastY = currentY;
        firstMouse = false;
      }
      const float xOffset = Input::getMouseDeltaX();
      const float yOffset = Input::getMouseDeltaY();
      lastX = currentX;
      lastY = currentY;
      camera.processMouseMovement(xOffset, yOffset);
    }

    // Zoom handling
    if (Input::getScrollDelta() != 0.0f) {
      camera.processMouseScroll(Input::consumeScrollDelta() * 5); // TODO: Not hardcode this
    }

    // Rendering scene and render view in editor
    sceneRenderer->render(camera.getEditorViewMatrix(), camera.getProjectionMatrix(), scene);
    if (scene) { // TODO rework this
      const auto sceneCamera = scene->selectedCamera;
      Camera camera = scene->world.get_component<Camera>(sceneCamera);
      renderViewRenderer->render(camera.getViewMatrix(scene->world, sceneCamera), camera.getProjectionMatrix(), scene);
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

    if (!gui.inspectorFocus && gui.sceneHovered && Input::isMouseButtonPressed(MouseButton::Right)) {
      gui.inspectorFocus = true;
      glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    } else if (gui.inspectorFocus && !Input::isMouseButtonPressed(MouseButton::Right)) {
      gui.inspectorFocus = false;
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
