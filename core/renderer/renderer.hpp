#pragma once

#include <memory>
#include <iostream>
#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "shader/shader.hpp"
#include "component/camera.hpp"
#include "component/transform.hpp"
#include "component/model_renderer.hpp"
#include "scene/scene.hpp"
#include "ecs/world.hpp"
#include "ecs/entity.hpp"

namespace SpaceEngine {

class Renderer {
 public:
  Renderer();
  ~Renderer();

  bool initialize(int width, int height);
  void render(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix,
              const std::shared_ptr<Scene>& scene) const;
  [[nodiscard]] unsigned int getRenderedTexture() const {
    return textureColorBuffer;
  }
  void resize(int width, int height);

 private:
  void setupFramebuffer(int width, int height);

  unsigned int fbo;
  unsigned int textureColorBuffer;
  unsigned int rbo;
  std::unique_ptr<Shader> shader;
  int viewportWidth;
  int viewportHeight;
};

}  // namespace SpaceEngine