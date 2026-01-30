#include "renderer.hpp"

namespace SpaceEngine {

Renderer::Renderer() : fbo(0), textureColorBuffer(0), rbo(0), viewportWidth(0), viewportHeight(0) {}

Renderer::~Renderer() {
  if (fbo != 0) {
    glDeleteFramebuffers(1, &fbo);
  }
  if (textureColorBuffer != 0) {
    glDeleteTextures(1, &textureColorBuffer);
  }
  if (rbo != 0) {
    glDeleteRenderbuffers(1, &rbo);
  }
}

bool Renderer::initialize(const int width, const int height) {
  viewportWidth = width;
  viewportHeight = height;
  shader = std::make_unique<Shader>("./shaders/test.vs", "./shaders/test.fs", nullptr);
  setupFramebuffer(width, height);
  return true;
}

void Renderer::setupFramebuffer(const int width, const int height) {
  // Create framebuffer
  glGenFramebuffers(1, &fbo);
  glBindFramebuffer(GL_FRAMEBUFFER, fbo);

  // Create color texture
  glGenTextures(1, &textureColorBuffer);
  glBindTexture(GL_TEXTURE_2D, textureColorBuffer);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glFramebufferTexture2D(GL_FRAMEBUFFER,
                         GL_COLOR_ATTACHMENT0,
                         GL_TEXTURE_2D,
                         textureColorBuffer,
                         0);

  // Create renderbuffer for depth and stencil
  glGenRenderbuffers(1, &rbo);
  glBindRenderbuffer(GL_RENDERBUFFER, rbo);
  glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
  glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo);

  if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
    std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
  }
  glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Renderer::resize(const int width, const int height) {
  viewportWidth = width;
  viewportHeight = height;

  // Resize color texture
  glBindTexture(GL_TEXTURE_2D, textureColorBuffer);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);

  // Resize renderbuffer
  glBindRenderbuffer(GL_RENDERBUFFER, rbo);
  glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
}

void Renderer::render(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix,
                      const std::shared_ptr<Scene>& scene) const {
  if (!scene) {
    return;
  }

  glBindFramebuffer(GL_FRAMEBUFFER, fbo);
  glEnable(GL_DEPTH_TEST);
  glViewport(0, 0, viewportWidth, viewportHeight);

  glm::vec4 clearColor(0.1f, 0.1f, 0.1f, 1.0f);
  const auto camera = scene->world.get_component<Camera>(scene->selectedCamera);
  clearColor = glm::vec4(camera.skyboxColor.x,
                         camera.skyboxColor.y,
                         camera.skyboxColor.z,
                         camera.skyboxColor.w);

  glClearColor(clearColor.r, clearColor.g, clearColor.b, clearColor.a);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  shader->use();
  shader->setMat4("projection", projectionMatrix);
  shader->setMat4("view", viewMatrix);

  // Render all entities with model renderers
  for (Entity e : scene->world.view<ModelRenderer, Transform>()) {
    const auto& mr = scene->world.get_component<ModelRenderer>(e);
    const auto& tf = scene->world.get_component<Transform>(e);

    if (!mr.model) continue;

    auto model = glm::mat4(1.0f);
    // Apply transformations
    model = glm::translate(model, glm::vec3(tf.position.x(), tf.position.y(), tf.position.z()));
    model = glm::scale(model, glm::vec3(tf.scale.x(), tf.scale.y(), tf.scale.z()));
    model = glm::rotate(model, glm::radians(tf.rotation.x()), glm::vec3(1.0f, 0.0f, 0.0f));
    model = glm::rotate(model, glm::radians(tf.rotation.y()), glm::vec3(0.0f, 1.0f, 0.0f));
    model = glm::rotate(model, glm::radians(tf.rotation.z()), glm::vec3(0.0f, 0.0f, 1.0f));

    shader->setMat4("model", model);
    mr.model->draw(*shader);
  }

  glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

}  // namespace SpaceEngine