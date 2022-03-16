#include "Projection/Perspective.h"

namespace hui
{
    namespace triD
    {

        const Mat4x4f &Perspective::transMat()
        {
            if (this->isDirty())
            {
                m_dirty = false;
                m_changed = clsDirty();
                m_transformation = perspective_rh(m_fov, m_aspect, m_near, m_far);
            }
            return m_transformation;
        }

        void Perspective::setFov(float fov)
        {
            if (m_fov != fov)
            {
                m_fov = fov;
                m_dirty = true;
                m_changed = true;
            }
        }

        void Perspective::setNear(float near)
        {
            if (m_near != near)
            {
                m_near = near;
                m_dirty = true;
                m_changed = true;
            }
        }

        void Perspective::setFar(float far)
        {
            if (m_far != far)
            {
                m_far = far;
                m_dirty = true;
                m_changed = true;
            }
        }

        void Perspective::setAspect(float aspect)
        {
            if (m_aspect != aspect)
            {
                m_aspect = aspect;
                m_dirty = true;
                m_changed = true;
            }
        }
    }
}