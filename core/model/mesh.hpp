#pragma once

#include <vector>

#include "model/vertex.hpp"
#include "model/texture.hpp"
#include "shader/shader.hpp"

namespace SpaceEngine {

class Mesh {
public:
  std::vector<Vertex> vertices;
  std::vector<unsigned int> indices;
  std::vector<Texture> textures;

  Mesh(const std::vector<Vertex> &vertices, const std::vector<unsigned int> &indices, const std::vector<Texture> &textures);
  void draw(const Shader &shader) const;

private:
  unsigned int VAO{}, VBO{}, EBO{};
  void setupMesh();
};

}
