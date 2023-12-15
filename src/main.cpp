#include <SFML/Graphics.hpp>
#include <imgui.h>
#include <imgui-sfml.h>

#include <GL/glew.h>

int main() {
  sf::RenderWindow window(sf::VideoMode(800, 600), "Space Engine");
  glewInit();
  ImGui::SFML::Init(window);
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed)
        window.close();

      ImGui::SFML::Update(window);
    }

    glClear(GL_COLOR_BUFFER_BIT);
    ImGui::Begin("Space engine");

    ImGui::End();
    window.display();
  }

  ImGui::SFML::Shutdown();
  window.close();

  return 0;
}
