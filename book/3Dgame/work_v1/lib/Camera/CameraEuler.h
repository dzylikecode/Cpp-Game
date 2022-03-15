#include "Camera/CameraBasic.h"

namespace hui
{
    namespace triD
    {
        class CameraEuler_v1 : public CameraBasic_v1
        {
        private:
            bool m_dirty;
            Mat4x4f m_transformation;
            unsigned int m_width;
            unsigned int m_height;
            float m_view_dist;

        public:
            virtual const Mat4x4f &getTransformationMatrix();
            virtual const Mat4x4f &getTransformationMatrix() const { return const_cast<CameraEuler_v1 *>(this)->getTransformationMatrix(); }
            const unsigned int getWidth() const { return m_width; }
            const unsigned int getHeight() const { return m_height; }
            float getViewDist() const;
            void setSize(unsigned int width, unsigned int height);
            virtual bool isDirty() const { return m_dirty || CameraBasic_v1::isDirty(); }
        };
    }
}