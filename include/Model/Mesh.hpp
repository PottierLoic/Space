#pragma once

#include <vector>

#include "glad/glad.h"

#include "Model/Vertex.hpp"
#include "Model/Texture.hpp"
#include "Shader.hpp"

class Mesh {
public:
  std::vector<Vertex> vertices;
  std::vector<unsigned int> indices;
  std::vector<Texture> textures;

  Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures);
  void draw(Shader &shader);

private:
  unsigned int VAO, VBO, EBO;
  void setupMesh();
};