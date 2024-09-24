// Author: Jake Rieger
// Created: 9/24/2024.
//

#pragma once

#include "Camera.h"
#include "Camera.h"
#include "Camera.h"
#include "Camera.h"
#include "Camera.h"
#include "Camera.h"
#include "Types.h"

#include <glm/mat4x4.hpp>
#include <glm/glm.hpp>

namespace GLTK {
    namespace AspectRatios {
        static constexpr f32 kAspect4by3   = 4.f / 3.f;
        static constexpr f32 kAspectSquare = 1.f;
        static constexpr f32 kAspect5by4   = 5.f / 4.f;
        static constexpr f32 kAspect16by9  = 16.0f / 9.0f;
        static constexpr f32 kAspect16by10 = 16.0f / 10.0f;
        static constexpr f32 kAspect32by9  = 32.0f / 9.0f;
    }  // namespace AspectRatios

    class ICamera {
    public:
        virtual ~ICamera()                                        = default;
        [[nodiscard]] virtual glm::mat4 GetViewProjection() const = 0;
        virtual void Update()                                     = 0;

        template<typename T>
        T* As() {
            return DCAST<T*>(this);
        }
    };

    template<typename T>
    concept Camera = std::is_base_of_v<ICamera, T>;

    template<Camera T, typename... Args>
    Shared<T> CreateCamera(Args&&... args) {
        return std::make_shared<T>(std::forward<Args>(args)...);
    }

    class OrthoCamera final : public ICamera {
    public:
        OrthoCamera(f32 width, f32 height, f32 near = -1.f, f32 far = 1.f);
        [[nodiscard]] glm::mat4 GetViewProjection() const override;
        void Update() override;

        void SetPosition(const glm::vec3& position);
        void SetZoom(f32 zoom);
        void SetBounds(f32 left, f32 right, f32 bottom, f32 top);
        void SetZBounds(f32 near, f32 far);
        void ResizeViewport(f32 width, f32 height);

        [[nodiscard]] glm::vec3 ScreenToWorld(const glm::vec2& screenPos,
                                              const glm::vec2& screenSize) const;
        [[nodiscard]] glm::vec2 WorldToScreen(const glm::vec3& worldPos,
                                              const glm::vec2& screenSize) const;

    private:
        void UpdateView();
        void UpdateProjection();
        static void WHToLRTB(f32 width, f32 height, f32& left, f32& right, f32& bottom, f32& top);

        glm::mat4 mView, mProjection;
        glm::vec3 mPosition;

        f32 mLeft, mRight, mBottom, mTop;
        f32 mNear, mFar, mAspect, mZoom;
    };
}  // namespace GLTK
