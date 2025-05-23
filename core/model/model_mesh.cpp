#include "model/model_mesh.hpp"

namespace SpaceEngine {

ModelMesh::ModelMesh(const std::vector<ModelVertex> &vertices, const std::vector<unsigned int> &indices, const std::vector<ModelTexture> &textures) {
  this->vertices = vertices;
  this->indices = indices;
  this->textures = textures;

  setupMesh();
}

void ModelMesh::setupMesh() {
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);
  glGenBuffers(1, &EBO);

  glBindVertexArray(VAO);

  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(ModelVertex), &vertices[0], GL_STATIC_DRAW);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

  // vertex positions
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(ModelVertex), nullptr);

  // vertex normals
  glEnableVertexAttribArray(1);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(ModelVertex), reinterpret_cast<void *>(offsetof(ModelVertex, normal)));

  // vertex texture coords
  glEnableVertexAttribArray(2);
  glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(ModelVertex), reinterpret_cast<void *>(offsetof(ModelVertex, texCoords)));

  // vertex tangent
  glEnableVertexAttribArray(3);
  glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(ModelVertex), reinterpret_cast<void *>(offsetof(ModelVertex, tangent)));

  // vertex bitangent
  glEnableVertexAttribArray(4);
  glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(ModelVertex), reinterpret_cast<void *>(offsetof(ModelVertex, bitangent)));

  // ids
  glEnableVertexAttribArray(5);
  glVertexAttribIPointer(5, 4, GL_INT, sizeof(ModelVertex), reinterpret_cast<void *>(offsetof(ModelVertex, m_BoneIDs)));

  // weights
  glEnableVertexAttribArray(6);
  glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, sizeof(ModelVertex), reinterpret_cast<void *>(offsetof(ModelVertex, m_Weights)));

  glBindVertexArray(0);
}

void ModelMesh::draw(const Shader &shader) const {
  unsigned int diffuseNr = 1;
  unsigned int specularNr = 1;
  unsigned int normalNr = 1;
  unsigned int heightNr = 1;

  for(unsigned int i = 0; i < textures.size(); i++) {
    glActiveTexture(GL_TEXTURE0 + i);
    std::string number;
    std::string name = textures[i].type;
    if (name == "texture_diffuse") {
      number = std::to_string(diffuseNr++);
    } else if (name == "texture_specular") {
      number = std::to_string(specularNr++);
    } else if (name == "texture_normal") {
      number = std::to_string(normalNr++);
    } else if (name == "texture_height") {
      number = std::to_string(heightNr++);
    }
    shader.setInt(name + number, static_cast<int>(i));
    glBindTexture(GL_TEXTURE_2D, textures[i].id);
  }

  glBindVertexArray(VAO);
  glDrawElements(GL_TRIANGLES, static_cast<int>(indices.size()), GL_UNSIGNED_INT, nullptr);
  glBindVertexArray(0);

  glActiveTexture(GL_TEXTURE0);
}

}
