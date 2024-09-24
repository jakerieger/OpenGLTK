// Author: Jake Rieger
// Created: 9/23/2024.
//

#pragma once

#include "Buffer.h"

#include <glad/glad.h>
#include <Panic/Panic.h>

namespace GLTK {
    struct VertexAttrib {
        const char* Name;
        u32 Location;
        int Size;
        u32 Type;
        u32 Normalized;
        int Stride;
        void* Offset;
    };

    class VertexArray {
    public:
        VertexArray() {
            glGenVertexArrays(1, &mVAO);
            if (mVAO == 0)
                Panic("VertexArray could not be created");
        }

        ~VertexArray() {
            if (!mVBOs.empty())
                glDeleteBuffers(CAST<GLsizei>(mVBOs.size()), mVBOs.data());
            if (!mEBOs.empty())
                glDeleteBuffers(CAST<GLsizei>(mEBOs.size()), mEBOs.data());

            glDeleteVertexArrays(1, &mVAO);
        }

        void Bind() const {
            glBindVertexArray(mVAO);
        }

        static void Unbind() {
            glBindVertexArray(0);
        }

        //                      loc size type    normalized      stride          offset
        // glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);

        template<typename T>
        void CreateVertexBuffer(const Vector<T>& vertices, Vector<VertexAttrib>& attribs) {
            auto vboDescriptor = Buffer::BufferDescriptor<f32>();
            vboDescriptor.Data = vertices.data();
            const auto vbo     = Buffer::CreateBuffer(vboDescriptor);

            glBindBuffer(GL_ARRAY_BUFFER, vbo);
            for (auto i = 0; i < attribs.size(); ++i) {
                glEnableVertexAttribArray(i);
                const auto attr = attribs[i];
                glVertexAttribPointer(attr.Location,
                                      attr.Size,
                                      attr.Type,
                                      attr.Normalized,
                                      attr.Stride,
                                      attr.Offset);
            }
            glBindBuffer(GL_ARRAY_BUFFER, 0);

            mVBOs.push_back(vbo);
        }

        template<typename T>
        void CreateElementBuffer(const Vector<T>& indices) {
            auto eboDescriptor = Buffer::BufferDescriptor<f32>();
            eboDescriptor.Type = GL_ELEMENT_ARRAY_BUFFER;
            eboDescriptor.Data = indices.data();

            const auto ebo = Buffer::CreateBuffer(eboDescriptor);

            mEBOs.push_back(ebo);
        }

        static void SetAttributeDivisor(u32 index, u32 divisor) {
            glVertexAttribDivisor(index, divisor);
        }

    private:
        u32 mVAO = 0;
        Vector<u32> mVBOs;
        Vector<u32> mEBOs;
    };
}  // namespace GLTK