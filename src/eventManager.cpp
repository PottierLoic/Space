#include "eventManager.hpp"

EventManager::EventManager() {
  keyStates.fill(false);
  std::cout << "EventManager initialized succesfully" << std::endl;
}

EventManager::~EventManager() {
  std::cout << "EventManager destroyed successfully" << std::endl;
}

void EventManager::update() {
  while (SDL_PollEvent(&event)) {
    if (event.type == SDL_QUIT) {
      quit = true;
    }
    if (event.type == SDL_KEYDOWN) {
      keyStates[event.key.keysym.scancode] = true;
    }
    if (event.type == SDL_KEYUP) {
      keyStates[event.key.keysym.scancode] = false;
    }
  }
  for (int i = 0; i < SDL_NUM_SCANCODES; i++) {
    if (keyStates[i]) {
      std::cout << "Key " << i << " is pressed" << std::endl;
    }
  }
}
