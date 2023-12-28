#pragma once

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include "glad/glad.h"

class Shader {
public:
  unsigned int id;    // Program ID

  // Constructor reads and builds the shader
  Shader(const char* vertexPath, const char* fragmentPath);

  // Use / activate the shader
  void use();

  void setBool(const std::string& name, bool value) const;
  void setInt(const std::string& name, int value) const;
  void setFloat(const std::string& name, float value) const;
};