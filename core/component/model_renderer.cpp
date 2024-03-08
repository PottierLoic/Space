#include "component/model_renderer.hpp"

namespace SpaceEngine {

ModelRenderer::ModelRenderer(Entity* owner) : Component(owner) {
  model = nullptr;
}

ModelRenderer::~ModelRenderer() {}

}