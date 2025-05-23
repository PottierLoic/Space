#pragma once

#include<string>
#include<chrono>

namespace SpaceEngine {

class Resource {
public:
  virtual ~Resource() = default;
  [[nodiscard]] const std::string& getPath() const { return m_path; }
  [[nodiscard]] virtual const char* getTypeName() const = 0;
  [[nodiscard]] std::chrono::duration<float> getTimeSinceLoad() const {
    return std::chrono::steady_clock::now() - m_loadTime;
  }
protected:
  explicit Resource(std::string path) : m_path(std::move(path)),  m_loadTime(std::chrono::steady_clock::now()) {}

private:
  std::string m_path;
  std::chrono::steady_clock::time_point m_loadTime;
};

}