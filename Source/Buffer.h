// Author: Jake Rieger
// Created: 9/24/2024.
//

#pragma once

#include "Types.h"

#include <glad/glad.h>
#include <Panic/Panic.h>

namespace GLTK::Buffer {
    template<typename T>
    struct BufferDescriptor {
        u32 Type  = GL_ARRAY_BUFFER;
        u32 Usage = GL_STATIC_DRAW;
        Vector<T> Data;

        std::size_t Size();
    };

    template<typename T>
    std::size_t BufferDescriptor<T>::Size() {
        return sizeof(T) * Data.size();
    }

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

    inline void DeleteBuffer(u32 buffer) {
        glDeleteBuffers(1, &buffer);
    }
}  // namespace GLTK::Buffer