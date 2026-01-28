#pragma once

#include "model/model.hpp"
#include <memory>

namespace SpaceEngine {

struct ModelRenderer {
  std::shared_ptr<Model> model;
  std::string path; // TODO this should not be a path

  ModelRenderer();
  void setModel(); // TODO can't remember why I did it like this, should be refactored
};

}
