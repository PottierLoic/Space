#include "renderer.hpp"

namespace SpaceEngine {

Renderer::Renderer() : fbo(0), textureColorbuffer(0), rbo(0), viewportWidth(0), viewportHeight(0) {}

Renderer::~Renderer() {
  if (fbo != 0) {
    glDeleteFramebuffers(1, &fbo);
  }
  if (textureColorbuffer != 0) {
    glDeleteTextures(1, &textureColorbuffer);
  }
  if (rbo != 0) {
    glDeleteRenderbuffers(1, &rbo);
  }
}

bool Renderer::initialize(int width, int height) {
  viewportWidth = width;
  viewportHeight = height;
  shader = std::make_unique<Shader>("./shaders/test.vs", "./shaders/test.fs", nullptr);
  setupFramebuffer(width, height);
  return true;
}

void Renderer::setupFramebuffer(int width, int height) {
  // Create framebuffer
  glGenFramebuffers(1, &fbo);
  glBindFramebuffer(GL_FRAMEBUFFER, fbo);

  // Create color texture
  glGenTextures(1, &textureColorbuffer);
  glBindTexture(GL_TEXTURE_2D, textureColorbuffer);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textureColorbuffer, 0);

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

void Renderer::resize(int width, int height) {
  viewportWidth = width;
  viewportHeight = height;

  // Resize color texture
  glBindTexture(GL_TEXTURE_2D, textureColorbuffer);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);

  // Resize renderbuffer
  glBindRenderbuffer(GL_RENDERBUFFER, rbo);
  glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
}

void Renderer::render(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix, const std::shared_ptr<Scene>& scene) {
  if (!scene) {
    return;
  }

  glBindFramebuffer(GL_FRAMEBUFFER, fbo);
  glEnable(GL_DEPTH_TEST);
  glViewport(0, 0, viewportWidth, viewportHeight);

  // Get the camera's skybox color
  glm::vec4 clearColor(0.1f, 0.1f, 0.1f, 1.0f);
  if (scene->selectedCamera.lock()) {
    auto camera = scene->selectedCamera.lock();
    clearColor = glm::vec4(camera->skyboxColor.x, camera->skyboxColor.y, camera->skyboxColor.z, camera->skyboxColor.w);
  }

  // Clear the framebuffer with the camera's skybox color
  glClearColor(clearColor.r, clearColor.g, clearColor.b, clearColor.a);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // Use shader
  shader->use();
  shader->setMat4("projection", projectionMatrix);
  shader->setMat4("view", viewMatrix);

  // Render all entities with model renderers
  for (const auto& entity : scene->entities) {
    auto modelRenderer = entity->getComponent<ModelRenderer>();
    if (modelRenderer && modelRenderer->model) {
      auto transform = entity->getComponent<Transform>();
      glm::mat4 model = glm::mat4(1.0f);
      // Apply transformations
      model = glm::translate(model, glm::vec3(transform->position.x(),
                                              transform->position.y(),
                                              transform->position.z()));
      model = glm::scale(model, glm::vec3(transform->scale.x(),
                                          transform->scale.y(),
                                          transform->scale.z()));
      model = glm::rotate(model, glm::radians(transform->rotation.x()), glm::vec3(1.0f, 0.0f, 0.0f));
      model = glm::rotate(model, glm::radians(transform->rotation.y()), glm::vec3(0.0f, 1.0f, 0.0f));
      model = glm::rotate(model, glm::radians(transform->rotation.z()), glm::vec3(0.0f, 0.0f, 1.0f));

      shader->setMat4("model", model);
      modelRenderer->model->draw(*shader);
    }
  }

  glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

}