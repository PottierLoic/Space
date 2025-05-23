#pragma once

#include <vector>
#include <string>
#include <sstream>

#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"
#include "stb_image.h"

#include "log/logger.hpp"
#include "model/mesh.hpp"
#include "model/texture.hpp"
#include "shader/shader.hpp"

namespace SpaceEngine {

unsigned int textureFromFile(const char *path, const std::string &directory, bool gamma = false);

class Model {
public:
  explicit Model(const char *path);
  void draw(Shader &shader);
  std::string directory;

private:
  std::vector<Texture> textures_loaded;
  std::vector<Mesh> meshes;

  void loadModel(const std::string& path);
  void processNode(const aiNode *node, const aiScene *scene);
  Mesh processMesh(aiMesh *mesh, const aiScene *scene);
  std::vector<Texture> loadMaterialTextures(const aiMaterial *mat, aiTextureType type, const std::string& typeName);
};

}