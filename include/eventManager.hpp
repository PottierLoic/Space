#ifndef EVENTMANAGER_H
#define EVENTMANAGER_H

#include <iostream>
#include <SDL2/SDL.h>

class EventManager {
public:
  SDL_Event event;
  std::array<bool, SDL_NUM_SCANCODES> keyStates;
  bool quit = false;

  /* Default constructor. */
  EventManager();

  /* Cleaner */
  ~EventManager();

  /* Update the event manager and it's input list. */
  void update();
};

#endif