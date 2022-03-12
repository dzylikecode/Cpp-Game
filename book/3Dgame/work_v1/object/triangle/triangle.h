#ifndef HUI_TRIANGLES_H
#define HUI_TRIANGLES_H

#include "basic.hpp"
#include "Camera/Camera.hpp"

namespace hui
{
    namespace triD
    {
        class Triangle3D : public Mobject_v1, public Drawable
        {
        private:
            Vertex3 m_vert[3];
            const Mtransform *m_camera;

        public:
            void setCamera(const Mtransform &camera) { m_camera = &camera; }
            Vertex3 &operator[](std::size_t index) { return m_vert[index]; }
            const Vertex3 &operator[](std::size_t index) const { return const_cast<Triangle3D *>(this)->operator[](index); }

        private:
            virtual void draw(RenderTarget &target, RenderStates states) const;
            void convert_screen(unsigned int width, unsigned int height);
        };
    }
}

#endif