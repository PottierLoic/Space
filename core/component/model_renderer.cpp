#include "component/model_renderer.hpp"

namespace SpaceEngine {

ModelRenderer::ModelRenderer() {
  model = nullptr;
}

void ModelRenderer::setModel(std::string path) {
  model = std::make_shared<Model>(path.c_str());
}

}