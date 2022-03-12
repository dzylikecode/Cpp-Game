#ifndef HUI_PERSPECTIVE_H
#define HUI_PERSPECTIVE_H

#include "basic.hpp"

namespace hui
{
    namespace triD
    {
        class Perspective : public Mtransform
        {
        private:
            Mat4x4f m_transformation;
            float m_fov;
            float m_near;
            float m_far;
            float m_aspect;
            bool m_dirty;

        public:
            virtual const Mat4x4f &getTransformationMatrix();
            void setFov(float fov);
            void setNear(float near);
            void setFar(float far);
            void setAspect(float aspect);
            float getFov() const { return m_fov; }
            float getNear() const { return m_near; }
            float getFar() const { return m_far; }
            float getAspect() const { return m_aspect; }
            virtual bool isDirty() const { return m_dirty; }
        };
    }
}

#endif