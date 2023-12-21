#include <string>
#include <iostream>
// GLFW
#include "glad/glad.h"
#include "glfw/glfw3.h"
#include "imgui/imgui_impl_glfw.h"

std::string programName = "GLFW window";
int windowWidth = 1200,
    windowHeight = 800;
float backgroundR = 0.1f,
      backgroundG = 0.3f,
      backgroundB = 0.2f;

static void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
  glViewport(0, 0, width, height);
}

void teardown(GLFWwindow *window) {
  if (window != NULL) { glfwDestroyWindow(window); }
  glfwTerminate();
}

int main(int argc, char *argv[]) {
  if (!glfwInit()) {
    std::cerr << "[ERROR] Couldn't initialize GLFW\n";
    return -1;
  }
  else {
    std::cout << "[INFO] GLFW initialized\n";
  }

  // setup GLFW window
  glfwWindowHint(GLFW_DOUBLEBUFFER , 1);
  glfwWindowHint(GLFW_DEPTH_BITS, 24);
  glfwWindowHint(GLFW_STENCIL_BITS, 8);

  glfwWindowHint(
    GLFW_OPENGL_PROFILE,
    GLFW_OPENGL_CORE_PROFILE
  );

  std::string glsl_version = "";
#ifdef __APPLE__
  // GL 3.2 + GLSL 150
  glsl_version = "#version 150";
  glfwWindowHint( // required on Mac OS
    GLFW_OPENGL_FORWARD_COMPAT,
    GL_TRUE
  );
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
#elif __linux__
  // GL 3.2 + GLSL 150
  glsl_version = "#version 150";
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
#elif _WIN32
  // GL 3.0 + GLSL 130
  glsl_version = "#version 130";
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
#endif

  float highDPIscaleFactor = 1.0;
#ifdef _WIN32
  // if it's a HighDPI monitor, try to scale everything
  GLFWmonitor *monitor = glfwGetPrimaryMonitor();
  float xscale, yscale;
  glfwGetMonitorContentScale(monitor, &xscale, &yscale);
  if (xscale > 1 || yscale > 1) {
    highDPIscaleFactor = xscale;
    glfwWindowHint(GLFW_SCALE_TO_MONITOR, GLFW_TRUE);
  }
#elif __APPLE__
  // to prevent 1200x800 from becoming 2400x1600
  glfwWindowHint(GLFW_COCOA_RETINA_FRAMEBUFFER, GLFW_FALSE);
#endif

  GLFWwindow *window = glfwCreateWindow(
    windowWidth,
    windowHeight,
    programName.c_str(),
    NULL,
    NULL
  );
  if (!window) {
    std::cerr << "[ERROR] Couldn't create a GLFW window\n";
    teardown(NULL);
    return -1;
  }
  // watch window resizing
  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
  glfwMakeContextCurrent(window);
  // VSync
  glfwSwapInterval(1);

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    std::cerr << "[ERROR] Couldn't initialize GLAD" << std::endl;
    teardown(window);
    return -1;
  } else {
    std::cout << "[INFO] GLAD initialized\n";
  }

  std::cout << "[INFO] OpenGL from glad "
            << GLVersion.major << "." << GLVersion.minor
            << std::endl;

  int actualWindowWidth, actualWindowHeight;
  glfwGetWindowSize(window, &actualWindowWidth, &actualWindowHeight);
  glViewport(0, 0, actualWindowWidth, actualWindowHeight);

  glClearColor(backgroundR, backgroundG, backgroundB, 1.0f);
  // --- rendering loop
  while (!glfwWindowShouldClose(window)) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  teardown(window);
  return 0;
}