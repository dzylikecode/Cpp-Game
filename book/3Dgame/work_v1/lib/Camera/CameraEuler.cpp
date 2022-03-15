#include "Camera/CameraEuler.h"

namespace hui
{
    namespace triD
    {
        void CameraEuler_v1::setSize(unsigned int width, unsigned int height)
        {
            if (m_width != width || m_height != height)
            {
                m_width = width;
                m_height = height;
                setAspect(static_cast<float>(width) / static_cast<float>(height));
            }
        }

        const Mat4x4f &CameraEuler_v1::getTransformationMatrix()
        {
            if (this->isDirty())
            {
                auto &pers_mat = Perspective::getTransformationMatrix();
                m_transformation = pers_mat * this->getLocalMatrix();
                m_view_dist = std::abs(A<1, 1>(pers_mat)) * m_width / 2.0f;
                m_dirty = false;
            }
            return m_transformation;
        }

        float CameraEuler_v1::getViewDist() const
        {
            const_cast<CameraEuler_v1 *>(this)->getTransformationMatrix();
            return m_view_dist;
        }
    }
}