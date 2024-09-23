// Author: Jake Rieger
// Created: 9/23/2024.
//

#pragma once

#include <glm/glm.hpp>

namespace GLTK {
    struct Vertex {
        glm::vec3 Position;
        glm::vec2 TexCoords;
    };

    struct VertexAttribute {
        const char* Name;
        uint32_t Index;
        uint32_t Offset;
    };
}  // namespace GLTK