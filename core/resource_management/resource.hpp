#pragma once

#include<string>

namespace SpaceEngine {

class Resource {
public:
  virtual ~Resource() = default;
  [[nodiscard]] const std::string& getPath() const { return m_path; }

protected:
  explicit Resource(std::string path) : m_path(std::move(path)) {}

private:
  std::string m_path;
};

}