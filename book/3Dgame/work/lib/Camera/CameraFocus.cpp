#ifndef HUI_CAMERAFOCUS_H
#define HUI_CAMERAFOCUS_H
#include "Camera/CameraFocus.h"

namespace hui
{
    namespace triD
    {

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

        const Mat4x4f &CameraFocus_v1::getTransformationMatrix()
        {
            if (this->isDirty())
            {
                // notice that camera is looking at the negative z axis
                m_dir = normalized(this->getPos() - m_look_at);
                m_right = normalized(cross(m_up, m_dir));
                m_up = normalized(cross(m_dir, m_right));
                Mat4x4f rotate{
                    X(m_right), X(m_up), X(m_dir), 0,
                    Y(m_right), Y(m_up), Y(m_dir), 0,
                    Z(m_right), Z(m_up), Z(m_dir), 0,
                    0, 0, 0, 1};
                this->setRotate(rotate);
                m_transformation = Perspective::getTransformationMatrix() *
                                   this->getLocalMatrix();
                m_dirty = false;
            }
            return m_transformation;
        }
        const Vec3f &CameraFocus_v1::getUp()
        {
            getTransformationMatrix();
            return m_up;
        }

        const Vec3f &CameraFocus_v1::getRight()
        {
            getTransformationMatrix();
            return m_right;
        }

        const Vec3f &CameraFocus_v1::getDir()
        {
            getTransformationMatrix();
            return m_dir;
        }
    }
}
#endif