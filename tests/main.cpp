#include <cstring>
#include <filesystem>
#include <iomanip>
#include <iostream>

extern int testVector2();
extern int testVector3();
extern int testVector4();
extern int testLog();
extern int testLogger();
extern int testTime();
extern int testInputBinding();

struct TestFunction {
  const char* name;
  int (*function)();
};

TestFunction test_fn[] = {
    {"testVector2", testVector2},
    {"testVector3", testVector3},
    {"testVector4", testVector4},
    {"testLog", testLog},
    {"testLogger", testLogger},
    {"TestTime", testTime},
    {"testInputBinding", testInputBinding},
};

void run_all_tests() {
  int count = 0;
  std::cout << "\033[1;37mRunning tests . . .\033[0m" << std::endl;

  size_t max_length = 0;
  for (const auto& [name, function] : test_fn) {
    if (const size_t test_length = strlen(name); test_length > max_length) {
      max_length = test_length;
    }
  }

  for (const auto& [name, function] : test_fn) {
    std::cout << "\033[1;37mRunning test: " << std::setw(static_cast<int>(max_length)) << std::left
              << name << "         \033[0m";
    if (const int result = function(); result == 0) {
      std::cout << "\033[1;32mPassed\033[0m" << std::endl;
    } else {
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
    std::filesystem::remove_all((sourceDir / "generated").string());
    std::filesystem::create_directory((sourceDir / "generated").string());
  } catch (const std::exception& e) {
    std::cerr << e.what() << '\n';
  }

  run_all_tests();
  return 0;
}
