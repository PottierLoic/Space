#include "component/model_renderer.hpp"

namespace SpaceEngine {

ModelRenderer::ModelRenderer(std::weak_ptr<Entity> owner) : Component(owner) {
  model = nullptr;
}

ModelRenderer::~ModelRenderer() {}

}