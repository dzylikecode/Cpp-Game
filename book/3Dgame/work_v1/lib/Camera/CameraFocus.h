#include "Mobject/Mobject.hpp"
#include "Projection/Projection.hpp"

namespace hui
{
    namespace triD
    {
        class CameraFocus_v1 : public Mobject_v1, public Perspective
        {
        private:
            Vec3f m_look_at;
            Vec3f m_dir;
            Vec3f m_up;
            Vec3f m_right;
            bool m_dirty;
            Mat4x4f m_transformation;
            unsigned int m_width;
            unsigned int m_height;
            float m_view_dist;

        public:
            virtual const Mat4x4f &getTransformationMatrix();
            virtual const Mat4x4f &getTransformationMatrix() const { return const_cast<CameraFocus_v1 *>(this)->getTransformationMatrix(); }
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
            virtual bool isDirty() const { return m_dirty || Perspective::isDirty() || Mobject_v1::isDirty(); }
        };
    }
}