#pragma once

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include "glad/glad.h"
#include "glm/glm.hpp"

namespace SpaceEngine {

/*
 * The Shader class represents a shader program in OpenGL, encapsulating vertex, fragment, and geometry shaders.
 *
 * Properties:
 * - id (unsigned int): Program ID of the shader.
 *
 * Constructors:
 * - Shader(const char* vertexPath, const char* fragmentPath, const char* geometryPath): Reads and builds the shader from provided file paths.
 *
 * Methods:
 * - void use(): Activates the shader for rendering.
 * - void setBool(const std::string& name, bool value) const: Sets a boolean uniform value in the shader.
 * - void setInt(const std::string& name, int value) const: Sets an integer uniform value in the shader.
 * - void setFloat(const std::string& name, float value) const: Sets a floating-point uniform value in the shader.
 * - void setVec2(const std::string &name, const glm::vec2 &value) const: Sets a 2D vector uniform value in the shader.
 * - void setVec2(const std::string &name, float x, float y) const: Sets a 2D vector uniform value in the shader.
 * - void setVec3(const std::string &name, const glm::vec3 &value) const: Sets a 3D vector uniform value in the shader.
 * - void setVec3(const std::string &name, float x, float y, float z) const: Sets a 3D vector uniform value in the shader.
 * - void setVec4(const std::string &name, const glm::vec4 &value) const: Sets a 4D vector uniform value in the shader.
 * - void setVec4(const std::string &name, float x, float y, float z, float w) const: Sets a 4D vector uniform value in the shader.
 * - void setMat2(const std::string &name, const glm::mat2 &mat) const: Sets a 2x2 matrix uniform value in the shader.
 * - void setMat3(const std::string &name, const glm::mat3 &mat) const: Sets a 3x3 matrix uniform value in the shader.
 * - void setMat4(const std::string &name, const glm::mat4 &mat) const: Sets a 4x4 matrix uniform value in the shader.
 * - void checkCompileErrors(GLuint shader, std::string type): Checks and logs compilation errors for a shader.
 */
class Shader {
public:
  unsigned int id; // Program id

  /**
   * @brief Constructor that reads and builds the shader from provided file paths.
   * @param vertexPath: Path to the vertex shader file.
   * @param fragmentPath: Path to the fragment shader file.
   * @param geometryPath: Path to the geometry shader file.
   */
  Shader(const char* vertexPath, const char* fragmentPath, const char* geometryPath);

  /**
   * @brief activate the shader for rendering.
   */
  void use() const;

  /**
   * @brief Set a boolean uniform value in the shader.
   * @param name: Name of the boolean uniform.
   * @param value: Boolean value to set.
   */
  void setBool(const std::string& name, bool value) const;

  /**
   * @brief Set an integer uniform value in the shader.
   * @param name: Name of the integer uniform.
   * @param value: Integer value to set.
   */
  void setInt(const std::string& name, int value) const;

  /**
   * @brief Set a floating-point uniform value in the shader.
   * @param name: Name of the float uniform.
   * @param value: Float value to set.
   */
  void setFloat(const std::string& name, float value) const;

  /**
   * @brief Set a 2D vector uniform value in the shader.
   * @param name: Name of the vector uniform.
   * @param value: glm::vec2 value to set.
   */
  void setVec2(const std::string &name, const glm::vec2 &value) const;

  /**
   * @brief Set a 2D vector uniform value in the shader.
   * @param name: Name of the vector uniform.
   * @param x: x-component of the vector.
   * @param y: y-component of the vector.
   */
  void setVec2(const std::string &name, float x, float y) const;

  /**
   * @brief Set a 3D vector uniform value in the shader.
   * @param name: Name of the vector uniform.
   * @param value: glm::vec3 value to set.
   */
  void setVec3(const std::string &name, const glm::vec3 &value) const;

  /**
   * @brief Set a 3D vector uniform value in the shader.
   * @param name: Name of the vector uniform.
   * @param x: x-component of the vector.
   * @param y: y-component of the vector.
   * @param z: z-component of the vector.
   */
  void setVec3(const std::string &name, float x, float y, float z) const;

  /**
   * @brief Set a 4D vector uniform value in the shader.
   * @param name: Name of the vector uniform.
   * @param value: glm::vec4 value to set.
   */
  void setVec4(const std::string &name, const glm::vec4 &value) const;

  /**
   * @brief Set a 4D vector uniform value in the shader.
   * @param name: Name of the vector uniform.
   * @param x: x-component of the vector.
   * @param y: y-component of the vector.
   * @param z: z-component of the vector.
   * @param w: w-component of the vector.
   */
  void setVec4(const std::string &name, float x, float y, float z, float w) const;

  /**
   * @brief Set a 2x2 matrix uniform value in the shader.
   * @param name: Name of the matrix uniform.
   * @param mat: glm::mat2 value to set.
   */
  void setMat2(const std::string &name, const glm::mat2 &mat) const;

  /**
   * @brief Set a 3x3 matrix uniform value in the shader.
   * @param name: Name of the matrix uniform.
   * @param mat: glm::mat3 value to set.
   */
  void setMat3(const std::string &name, const glm::mat3 &mat) const;

  /**
   * @brief Set a 4x4 matrix uniform value in the shader.
   * @param name: Name of the matrix uniform.
   * @param mat: glm::mat4 value to set.
   */
  void setMat4(const std::string &name, const glm::mat4 &mat) const;

  /**
   * @brief Check and log compilation errors for a shader.
   * @param shader: ID of the shader to check.
   * @param type: Type of the shader (vertex, fragment, geometry).
   */
  static void checkCompileErrors(GLuint shader, const std::string& type);
};

}