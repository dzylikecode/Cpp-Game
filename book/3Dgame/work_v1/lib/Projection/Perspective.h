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
            bool m_changed;

        public:
            virtual const Mat4x4f &getTransformationMatrix() const { return const_cast<Perspective *>(this)->transMat(); }
            void setFov(float fov);
            void setNear(float near);
            void setFar(float far);
            void setAspect(float aspect);
            float getFov() const { return m_fov; }
            float getNear() const { return m_near; }
            float getFar() const { return m_far; }
            float getAspect() const { return m_aspect; }

        protected:
            bool clsDirtySub() { return !(m_changed = false); } // yes, equal
            bool isDirtySub() const { return m_changed; }

            
        private:
            const Mat4x4f &transMat();
            bool isDirty() const { return m_dirty; }
            bool clsDirty() { return true; }
        };
    }
}

#endif