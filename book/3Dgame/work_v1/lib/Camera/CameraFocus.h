#ifndef HUI_CAMERA_FOCUS_H
#define HUI_CAMERA_FOCUS_H
#include "Camera/CameraBasic.h"

namespace hui
{
    namespace triD
    {
        class CameraFocus_v1 : public CameraBasic_v1
        {
        private:
            Vec3f m_look_at;
            Vec3f m_dir;
            Vec3f m_up;
            Vec3f m_right;
            bool m_dirty;
            bool m_changed;
            Mat4x4f m_transformation;
            unsigned int m_width;
            unsigned int m_height;
            float m_view_dist;

        public:
            CameraFocus_v1();
            virtual const Mat4x4f &getTransformationMatrix() const { return const_cast<CameraFocus_v1 *>(this)->transMat(); }
            void setLookAt(const Vec3f &look_at);
            void setUp(const Vec3f &up);
            const Vec3f &getLookAt() const { return m_look_at; }
            const Vec3f &getUp() const;
            const Vec3f &getRight() const;
            const Vec3f &getDir() const;
            const unsigned int getWidth() const { return m_width; }
            const unsigned int getHeight() const { return m_height; }
            float getViewDist() const;
            void setSize(unsigned int width, unsigned int height);

        protected:
            bool clsDirtySub() { return !(m_changed = false) && CameraBasic_v1::clsDirtySub(); } // yes, equal
            bool isDirtySub() const { return m_changed || CameraBasic_v1::isDirtySub(); }

        private:
            const Mat4x4f &transMat();
            bool isDirty() const { return m_dirty || CameraBasic_v1::isDirtySub(); }
            bool clsDirty() { return CameraBasic_v1::clsDirtySub(); }
        };
    }
}
#endif