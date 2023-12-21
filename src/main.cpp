#include <GLFW/glfw3.h>
#include <iostream>

int main(void) {
  std::cout << "Starting SPACE..." << std::endl;
  GLFWwindow* window;

  if (!glfwInit()) {
    std::cerr << "Error initalizing GLFW" << std::endl;
    return -1;
  }

  window = glfwCreateWindow(640, 480, "GLFW CMake starter", NULL, NULL);
  if (!window) {
    glfwTerminate();
    return -1;
  }

  glfwMakeContextCurrent(window);
  glClearColor( 0.4f, 0.3f, 0.4f, 0.0f );

  while (!glfwWindowShouldClose(window)) {
    /* Render */

    glClear(GL_COLOR_BUFFER_BIT);

    glfwSwapBuffers(window);

    glfwPollEvents();
  }

  glfwTerminate();
  return 0;
}