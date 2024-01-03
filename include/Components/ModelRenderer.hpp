#pragma once

#include "Components/Component.hpp"

#include "Model/Model.hpp"

// TODO: Review names
class ModelRenderer : Component {
public:
  Model model = nullptr;

  /* Default constructor: Initializes a new empty ModelRenderer component. */
  ModelRenderer();

  /* Destructor: Destroys the ModelRenderer component. Note: May not have additional functionality in this case. */
  ~ModelRenderer();

  /* Display the ModelRenderer component properties in the inspector tab. */
  void display() override;
};
