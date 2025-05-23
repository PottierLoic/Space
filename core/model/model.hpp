#pragma once

#include <vector>
#include <string>
#include <sstream>

#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"
#include "stb_image.h"

#include "log/logger.hpp"
#include "model/model_mesh.hpp"
#include "model/model_texture.hpp"
#include "shader/shader.hpp"

namespace SpaceEngine {

unsigned int textureFromFile(const char *path, const std::string &directory, bool gamma = false);

class Model {
public:
  explicit Model(const char *path);
  void draw(Shader &shader);
  std::string directory;

private:
  std::vector<ModelTexture> textures_loaded;
  std::vector<ModelMesh> meshes;

  void loadModel(const std::string& path);
  void processNode(const aiNode *node, const aiScene *scene);
  ModelMesh processMesh(aiMesh *mesh, const aiScene *scene);
  std::vector<ModelTexture> loadMaterialTextures(const aiMaterial *mat, aiTextureType type, const std::string& typeName);
};

}