#include "object/triangle/triangle.h"
namespace hui
{
    namespace triD
    {
        void Triangle3D::convert_screen(unsigned int width, unsigned int height)
        {
            auto convert_matrix = m_camera->getTransformationMatrix() *
                                  this->getWorldMatrix();
            width = width / 2;
            height = height / 2;

            for (auto &v : m_vert)
            {
                auto pos3D = convert_matrix * XYZ1(v.pos3D);
                auto pos2D = XY(pos3D) / W(pos3D); // divide w instead of z
                X(pos2D) = (X(pos2D) + 1) * width;
                Y(pos2D) = (1 - Y(pos2D)) * height; // flip y
                v.position = Vector2f(X(pos2D), Y(pos2D));
            }
        }
        void Triangle3D::draw(RenderTarget &target, RenderStates states) const
        {
            const_cast<Triangle3D *>(this)->convert_screen(
                target.getView().getSize().x, target.getView().getSize().y);
            VertexArray tmp;
            tmp.resize(3);
            tmp[0] = m_vert[0];
            tmp[1] = m_vert[1];
            tmp[2] = m_vert[2];
            target.draw(&tmp[0], 3, sf::Triangles, states);
        }
    }
}