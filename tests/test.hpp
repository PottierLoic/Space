#pragma once

#define custom_assert(expression, message) \
  if (!(expression)) { \
    std::cout << "\033[1;31mAssertion Failed: " << message << "\033[0m" << std::endl; \
    std::cerr << "Failed condition: " << #expression << "\nIn file: " << __FILE__ << ", line " << __LINE__ << std::endl; \
    return 1; \
  }

#include <iostream>