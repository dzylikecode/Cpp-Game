#ifndef HUI_CAMERAFOCUS_H
#define HUI_CAMERAFOCUS_H
#include "Camera/CameraFocus.h"

namespace hui
{
    namespace triD
    {
        CameraFocus_v1::CameraFocus_v1() : m_look_at{0.0f, 0.0f, 0.0f},
                                           m_dir{0.0f, 0.0f, 0.0f},
                                           m_up{0.0f, 0.0f, 0.0f},
                                           m_right{0.0f, 0.0f, 0.0f},
                                           m_dirty(false),
                                           m_changed(false),
                                           m_width(0),
                                           m_height(0),
                                           m_view_dist(0.0f)
        {
        }

        void CameraFocus_v1::setLookAt(const Vec3f &look_at)
        {
            if (m_look_at != look_at)
            {
                m_look_at = look_at;
                m_dirty = true;
            }
        }

        void CameraFocus_v1::setUp(const Vec3f &up)
        {
            if (m_up != up)
            {
                m_up = up;
                m_dirty = true;
            }
        }

        const Mat4x4f &CameraFocus_v1::transMat()
        {
            if (this->isDirty())
            {
                // notice that camera is looking at the negative z axis
                m_dir = normalized(this->getPos() - m_look_at);
                m_right = normalized(cross(m_up, m_dir));
                if (mag(m_right) < 0.00001f)
                {
                    spdlog::error("m_up and m_dir are parallel");
                }
                m_up = normalized(cross(m_dir, m_right));
                Mat4x4f rotate{
                    X(m_right), X(m_up), X(m_dir), 0,
                    Y(m_right), Y(m_up), Y(m_dir), 0,
                    Z(m_right), Z(m_up), Z(m_dir), 0,
                    0, 0, 0, 1};
                this->setRotate(rotate);
                auto &pers_mat = Perspective::getTransformationMatrix();
                m_transformation = pers_mat * this->getLocalMatrix();
                m_view_dist = std::abs(A<1, 1>(pers_mat)) * m_width / 2.0f;
                m_dirty = false;
            }
            return m_transformation;
        }
        const Vec3f &CameraFocus_v1::getUp() const
        {
            const_cast<CameraFocus_v1 *>(this)->getTransformationMatrix();
            return m_up;
        }

        const Vec3f &CameraFocus_v1::getRight() const
        {
            const_cast<CameraFocus_v1 *>(this)->getTransformationMatrix();
            return m_right;
        }

        const Vec3f &CameraFocus_v1::getDir() const
        {
            const_cast<CameraFocus_v1 *>(this)->getTransformationMatrix();
            return m_dir;
        }

        void CameraFocus_v1::setSize(unsigned int width, unsigned int height)
        {
            if (m_width != width || m_height != height)
            {
                m_width = width;
                m_height = height;
                setAspect(static_cast<float>(width) / static_cast<float>(height));
            }
        }

        float CameraFocus_v1::getViewDist() const
        {
            const_cast<CameraFocus_v1 *>(this)->getTransformationMatrix();
            return m_view_dist;
        }
    }
}
#endif