// Author: Jake Rieger
// Created: 9/24/2024.
//

#pragma once

#include "Types.h"

#include <glad/glad.h>
#include <Panic/Panic.h>

/// @brief Utilities for managing OpenGL buffers.
namespace GLTK::Buffer {
    /// @brief Basic description of an OpenGL buffer.
    /// @tparam T The type of data the buffer stores, typically float or uint.
    template<typename T>
    struct BufferDescriptor {
        u32 Type  = GL_ARRAY_BUFFER;
        u32 Usage = GL_STATIC_DRAW;
        Vector<T> Data;

        /// @brief Returns the size of the data in bytes.
        std::size_t Size();
    };

    template<typename T>
    std::size_t BufferDescriptor<T>::Size() {
        return sizeof(T) * Data.size();
    }

    /// @brief Creates an OpenGL buffer based on the supplied buffer descriptor.
    /// @tparam T The type of data the buffer stores.
    template<typename T>
    u32 CreateBuffer(BufferDescriptor<T>& descriptor) {
        u32 buffer;
        glGenBuffers(1, &buffer);

        if (buffer == 0)
            Panic(std::source_location::current(), "Failed to create buffer");

        glBindBuffer(descriptor.Type, buffer);
        glBufferData(descriptor.Type, descriptor.Size(), descriptor.Data.data(), descriptor.Usage);
        glBindBuffer(descriptor.Type, 0);

        return buffer;
    }

    /// @brief Deletes an already created buffer. Basically just a wrapper for `glDeleteBuffers`.
    inline void DeleteBuffer(u32 buffer) {
        glDeleteBuffers(1, &buffer);
    }
}  // namespace GLTK::Buffer