#pragma once

#include "component/component.hpp"
#include "model/model.hpp"

namespace SpaceEngine {

/**
 * The ModelRenderer class represents a component responsible for rendering a 3D model.
 *
 * Properties:
 * - model (Model): The 3D model to be rendered.
 *
 * Methods:
 * - ModelRenderer(): Default constructor: Initializes a new empty ModelRenderer component.
 * - ~ModelRenderer(): Destructor: Destroys the ModelRenderer component. Note: May not have additional functionality in this case.
 */
class ModelRenderer : public Component {
public:
  Model* model = nullptr; /* The 3D model to be rendered. */

  /**
   * @brief Default constructor: Initializes a new empty ModelRenderer component.
   */
  ModelRenderer();

  /**
   * @brief Destructor: Destroys the ModelRenderer component. Note: May not have additional functionality in this case.
   */
  ~ModelRenderer();

};

}
