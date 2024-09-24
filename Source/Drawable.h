// Author: Jake Rieger
// Created: 9/24/2024.
//

#pragma once

#include "Camera.h"
#include "Shader.h"
#include "Types.h"
#include "VertexArray.h"

namespace GLTK {
    class IDrawable {
    public:
        IDrawable();
        virtual ~IDrawable() = default;

        virtual void Draw(const Weak<ICamera>& camera) = 0;
        virtual void Update(f32 dT)                    = 0;
        virtual void FixedUpdate()                     = 0;

    protected:
        Unique<VertexArray> mVertexArray;
        Unique<Shader> mShader;
    };
}  // namespace GLTK
