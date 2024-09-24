// Author: Jake Rieger
// Created: 9/23/2024.
//

#pragma once

#include "Types.h"
#include "Panic.h"

#include <format>
#include <stb_image.h>
#include <glad/glad.h>

namespace GLTK {
    inline u32 LoadTexture(const char* filename, int* width = nullptr, int* height = nullptr) {
        u32 id;
        glGenTextures(1, &id);

        int w, h, c;
        stbi_set_flip_vertically_on_load(true);
        stbi_uc* data = stbi_load(filename, &w, &h, &c, 0);
        if (!data) {
            Panic(GetSourceLocation(), "Failed to load texture: {}", filename);
        }

        if (width)
            *width = w;
        if (height)
            *height = h;

        GLenum format = GL_RGBA;
        if (c == 1)
            format = GL_RED;
        else if (c == 3)
            format = GL_RGB;
        else if (c == 4)
            format = GL_RGBA;

        glBindTexture(GL_TEXTURE_2D, id);
        glTexImage2D(GL_TEXTURE_2D, 0, CAST<int>(format), w, h, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D,
                        GL_TEXTURE_WRAP_S,
                        format == GL_RGBA ? GL_CLAMP_TO_EDGE : GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D,
                        GL_TEXTURE_WRAP_T,
                        format == GL_RGBA ? GL_CLAMP_TO_EDGE : GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

        stbi_image_free(data);
        return id;
    }
}  // namespace GLTK