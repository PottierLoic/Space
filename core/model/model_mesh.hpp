#pragma once

#include <vector>

#include "model/model_vertex.hpp"
#include "model/model_texture.hpp"
#include "shader/shader.hpp"

namespace SpaceEngine {

class ModelMesh {
public:
  std::vector<ModelVertex> vertices;
  std::vector<unsigned int> indices;
  std::vector<ModelTexture> textures;

  ModelMesh(const std::vector<ModelVertex> &vertices, const std::vector<unsigned int> &indices, const std::vector<ModelTexture> &textures);
  void draw(const Shader &shader) const;

private:
  unsigned int VAO{}, VBO{}, EBO{};
  void setupMesh();
};

}
