#include "component/model_renderer.hpp"

namespace SpaceEngine {

ModelRenderer::ModelRenderer() {
  model = nullptr;
  path = "";
}

void ModelRenderer::setModel() {
  model = std::make_shared<Model>(path.c_str());
}

}