#include "model/model.hpp"

namespace SpaceEngine {

Model::Model(const char *path) {
  loadModel(path);
}

void Model::draw(Shader &shader) {
  for(auto & mesh : meshes) {
    mesh.draw(shader);
  }
}

void Model::loadModel(const std::string& path) {
  Assimp::Importer import;
  const aiScene *scene = import.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

  if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
    std::ostringstream msg;
    msg << "ERROR::ASSIMP:: " << import.GetErrorString();
    Logger::error(msg.str());
    return;
  }

  directory = path.substr(0, path.find_last_of('/'));

  processNode(scene->mRootNode, scene);
}

void Model::processNode(const aiNode *node, const aiScene *scene) {
  /* Processing all meshes */
  for(unsigned int i = 0; i < node->mNumMeshes; i++) {
    aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
    meshes.push_back(processMesh(mesh, scene));
  }

  /* Processing all children */
  for(unsigned int i = 0; i < node->mNumChildren; i++) {
    processNode(node->mChildren[i], scene);
  }
}

ModelMesh Model::processMesh(aiMesh *mesh, const aiScene *scene) {
  std::vector<ModelVertex> vertices;
  std::vector<unsigned int> indices;
  std::vector<ModelTexture> textures;

  for(unsigned int i = 0; i < mesh->mNumVertices; i++) {
    ModelVertex vertex{};
    glm::vec3 vector; // placeholder vector

    // position
    vector.x = mesh->mVertices[i].x;
    vector.y = mesh->mVertices[i].y;
    vector.z = mesh->mVertices[i].z;
    vertex.position = vector;

    // normals
    if(mesh->HasNormals()) {
      vector.x = mesh->mNormals[i].x;
      vector.y = mesh->mNormals[i].y;
      vector.z = mesh->mNormals[i].z;
      vertex.normal = vector;
    }

    // process materials
    if(mesh->mTextureCoords[0]) {
      glm::vec2 vec;
      vec.x = mesh->mTextureCoords[0][i].x;
      vec.y = mesh->mTextureCoords[0][i].y;
      vertex.texCoords = vec;
    } else {
      vertex.texCoords = glm::vec2(0.0f, 0.0f);
    }
    vertices.push_back(vertex);
  }

  // process indices
  for(unsigned int i = 0; i < mesh->mNumFaces; i++) {
    aiFace face = mesh->mFaces[i];
    for(unsigned int j = 0; j < face.mNumIndices; j++) {
      indices.push_back(face.mIndices[j]);
    }
  }

  aiMaterial *material = scene->mMaterials[mesh->mMaterialIndex];

  // diffuse maps
  std::vector<ModelTexture> diffuseMaps = loadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
  textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());

  // specular maps
  std::vector<ModelTexture> specularMaps = loadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
  textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());

  // normal maps
  std::vector<ModelTexture> normalMaps = loadMaterialTextures(material, aiTextureType_HEIGHT, "texture_normal");
  textures.insert(textures.end(), normalMaps.begin(), normalMaps.end());

  // height maps
  std::vector<ModelTexture> heightMaps = loadMaterialTextures(material, aiTextureType_AMBIENT, "texture_height");
  textures.insert(textures.end(), heightMaps.begin(), heightMaps.end());
  return {vertices, indices, textures};
}

std::vector<ModelTexture> Model::loadMaterialTextures(const aiMaterial *mat, const aiTextureType type, const std::string& typeName) {
  std::vector<ModelTexture> textures;
  for(unsigned int i = 0; i < mat->GetTextureCount(type); i++) {
    aiString str;
    mat->GetTexture(type, i, &str);
    bool skip = false;
    for(auto & tex : textures_loaded) {
      if(std::strcmp(tex.path.data(), str.C_Str()) == 0) {
        textures.push_back(tex);
        skip = true;
        break;
      }
    }

    if (!skip) {
      ModelTexture texture;
      texture.id = textureFromFile(str.C_Str(), directory);
      texture.type = typeName;
      texture.path = str.C_Str();
      textures.push_back(texture);
      textures_loaded.push_back(texture);
    }
  }
  return textures;
}

unsigned int textureFromFile(const char *path, const std::string &directory, bool /*gamma*/) {
  auto filename = std::string(path);
  filename = directory + '/' + filename;
  unsigned int textureID;
  glGenTextures(1, &textureID);

  int width, height, nrComponents;

  if(unsigned char *data = stbi_load(filename.c_str(), &width, &height, &nrComponents, 0)) {
    GLenum format = 0;
    if(nrComponents == 1) { format = GL_RED; }
    else if (nrComponents == 3) { format = GL_RGB; }
    else if (nrComponents == 4) { format = GL_RGBA; }

    glBindTexture(GL_TEXTURE_2D, textureID);
    glTexImage2D(GL_TEXTURE_2D, 0, static_cast<GLint>(format), width, height, 0, format, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    stbi_image_free(data);
  } else {
    std::ostringstream msg;
    msg << "Texture failed to load at path: " << path;
    Logger::error(msg.str());
    stbi_image_free(data);
  }
  return textureID;
}

}