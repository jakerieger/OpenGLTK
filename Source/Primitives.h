// Author: Jake Rieger
// Created: 9/26/2024.
//

#pragma once

#include "Types.h"

#include <array>

namespace GLTK::Primitives {
    /// Quad defined by a 4D vector, x,y for position and z,w for tex coords.
    static const Vector<f32> QuadVertTex = {
      -1.0f,
      1.0f,
      0.0f,
      1.0f,
      -1.0f,
      -1.0f,
      0.0f,
      0.0f,
      1.0f,
      1.0f,
      1.0f,
      1.0f,
      1.0f,
      -1.0f,
      1.0f,
      0.0f,
    };
}  // namespace GLTK::Primitives