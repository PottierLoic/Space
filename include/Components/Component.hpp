#pragma once

#include <iostream>

class Component {
public:
  Component();
  virtual ~Component();
  virtual void display();
};
