#include "component/model_renderer.hpp"

ModelRenderer::ModelRenderer() {
  model = nullptr;
}

ModelRenderer::~ModelRenderer() {}

void ModelRenderer::display() {
  if (ImGui::CollapsingHeader("Model Renderer")) {
    ImGui::Text("Model");
    ImGui::SameLine(100);
    // TODO:
    // Should make a empty field to place the mesh from project explorer.
  }
}
