#pragma once

#include <vector>
#include <string>

#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"
#include "stb_image.h"

#include "Model/Mesh.hpp"
#include "Model/Texture.hpp"
#include "Shader.hpp"

unsigned int textureFromFile(const char *path, const std::string &directory, bool gamma = false);

class Model {
public:
  Model(const char *path);
  void draw(Shader &shader);

private:
  std::vector<Texture> textures_loaded;

  std::vector<Mesh> meshes;
  std::string directory;

  void loadModel(std::string path);
  void processNode(aiNode *node, const aiScene *scene);
  Mesh processMesh(aiMesh *mesh, const aiScene *scene);
  std::vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, std::string typeName);
};