#pragma once

#include <iostream>
#include <glad/glad.h>
#include <glm/glm.hpp>

class FrameBuffer {
public:
  FrameBuffer(float width, float height);
  ~FrameBuffer();

  unsigned int getFrameTexture();
  void rescaleFrameBuffer(float width, float height);
  void bind() const;
  void unbind() const;

private:
  unsigned int fbo;
  unsigned int texture;
  unsigned int rbo;
};
