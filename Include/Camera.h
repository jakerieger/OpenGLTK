// Author: Jake Rieger
// Created: 9/24/2024.
//

#pragma once
#pragma warning(disable : 4244)

#include "Camera.h"
#include "Types.h"

#include <glm/mat4x4.hpp>
#include <glm/glm.hpp>

namespace GLTK {
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
        f32 mNear, mFar, mZoom;
    };
}  // namespace GLTK
