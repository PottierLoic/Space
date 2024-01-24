#include <iostream>
#include <iomanip>
#include <cstring>
#include <filesystem>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

extern int testVector2();
extern int testVector3();
extern int testProject();

struct TestFunction {
  const char* name;
  int (*function)();
};

TestFunction test_fn[] = {
  {"testVector2", testVector2},
  {"testVector3", testVector3},
  {"testProject", testProject},
};

void run_all_tests() {
  int count = 0;
  std::cout << "\033[1;37mRunning tests . . .\033[0m" << std::endl;

  size_t max_lenght = 0;
  for (const auto& test : test_fn) {
    size_t test_lenght = strlen(test.name);
    if (test_lenght > max_lenght) {
      max_lenght = test_lenght;
    }
  }

  for (const auto& test : test_fn) {
    std::cout << "\033[1;37mRunning test: " << std::setw(max_lenght) << std::left << test.name << "         \033[0m";
    int result = test.function();
    if (result == 0) {
      std::cout << "\033[1;32mPassed\033[0m" << std::endl;
    } else {
      // Fail print is in the custom_assert macro
      count++;
    }
  }

  if (count > 0) {
    std::cout << count << " Tests failed." << std::endl;
  } else {
    std::cout << "All tests passed." << std::endl;
  }
}

int main() {
  std::filesystem::path currentPath = __FILE__;
  std::filesystem::path sourceDir = currentPath.parent_path();

  // Clear previously generated files
  try {
    std::filesystem::remove_all((sourceDir / "Generated").string());
    std::filesystem::create_directory((sourceDir / "Generated").string());
  }
  catch(const std::exception& e) {
    std::cerr << e.what() << '\n';
  }

  /* Distance check */
  run_all_tests();
  return 0;
}
