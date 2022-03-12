#ifndef HUI_GEOMETRIC_H
#define HUI_GEOMETRIC_H

#include "basic.hpp"
#include "Camera/Camera.hpp"
#include <vector>
namespace hui
{
    namespace triD
    {
        class Geometric_v1 : public Mobject_v1, public Drawable
        {
        public:
            std::vector<Vec3f> m_vert;
            VertexArray m_vert_array;

        private:
            const Mtransform *m_camera;

        public:
            void setCamera(const Mtransform &camera) { m_camera = &camera; }
            void resize(std::size_t size);

        private:
            virtual void draw(RenderTarget &target, RenderStates states) const;
            void convert_screen(unsigned int width, unsigned int height);
        };
    }
}

#endif