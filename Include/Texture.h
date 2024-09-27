// Author: Jake Rieger
// Created: 9/23/2024.
//

#pragma once

#include "Types.h"

#include <format>
#include <stb_image.h>
#include <glad/glad.h>
#include <Panic/Panic.h>

namespace GLTK::Texture {
    static constexpr auto kMaxSlot = 31;

    /// @brief Internal function used to convert a slot number into its corresponding
    /// enum value.
    inline u32 GetGLSlot(u32 slot) {
        if (slot > kMaxSlot)
            Panic(std::source_location::current(),
                  "Slot is out of range! Must be (> 0) and (< 32)");
        return GL_TEXTURE0 + slot;
    }

    /// @brief Loads an image file as an OpenGL texture object.
    /// @param width If not null, this function will set it to the width of the image.
    /// @param height If not null, this function will set it to the height the image.
    inline u32 Load(const char* filename, int* width = nullptr, int* height = nullptr) {
        u32 id;
        glGenTextures(1, &id);

        int w, h, c;
        stbi_set_flip_vertically_on_load(true);
        stbi_uc* data = stbi_load(filename, &w, &h, &c, 0);
        if (!data) {
            Panic(std::source_location::current(), "Failed to load texture: {}", filename);
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

    /// @brief Deletes an OpenGL texture object
    inline void Delete(u32 id) {
        glDeleteTextures(1, &id);
    }

    /// @brief Binds the supplied OpenGL texture object to the specified slot. The max slot is 31.
    inline void Bind(u32 id, u32 slot) {
        glBindTexture(GL_TEXTURE_2D, id);
        glActiveTexture(GetGLSlot(slot));
    }

    /// @brief Unbinds any currently bound texture.
    inline void Unbind() {
        glBindTexture(GL_TEXTURE_2D, 0);
    }
}  // namespace GLTK::Texture