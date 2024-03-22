#include "component/model_renderer.hpp"

namespace SpaceEngine {

ModelRenderer::ModelRenderer(std::weak_ptr<Entity> owner) : Component(owner) {
  model = nullptr;
}

void ModelRenderer::setModel(std::string path) {
  model = std::make_shared<Model>(path.c_str());
}

}