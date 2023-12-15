#pragma once

#define custom_assert(expression) \
  if (!(expression)) { \
    std::cout << "\033[1;31mFailed\033[0m" << std::endl; \
    std::cerr << "Assertion failed: " << #expression << " in " << __FILE__ << " line " << __LINE__ << std::endl; \
    return 1; \
  }

#include <iostream>
