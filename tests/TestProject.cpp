#include "Test.hpp"
#include "Project.hpp"

int testProject() {
  std::filesystem::path currentPath = __FILE__;
  std::filesystem::path sourceDir = currentPath.parent_path();

  Project test((sourceDir / "Generated").string(), "test");
  return 0;
}
