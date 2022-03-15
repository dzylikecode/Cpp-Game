#include "Geometric/Geometric_v1.h"

namespace hui
{
    namespace triD
    {
        void Geometric_v1::resize(std::size_t size)
        {
            m_vert.resize(size);
            m_vert_array.resize(size);
        }

        void Geometric_v1::convert_screen(unsigned int width, unsigned int height)
        {
            auto convert_matrix = m_camera->getTransformationMatrix() *
                                  this->getWorldMatrix();
            width = width / 2;
            height = height / 2;

            for (decltype(m_vert.size()) i = 0; i < m_vert.size(); ++i)
            {
                auto pos3D = convert_matrix * XYZ1(m_vert[i]);
                auto pos2D = XY(pos3D) / W(pos3D); // divide w instead of z
                X(pos2D) = (X(pos2D) + 1) * width;
                Y(pos2D) = (1 - Y(pos2D)) * height; // flip y
                m_vert_array[i].position = Vector2f(X(pos2D), Y(pos2D));
            }
        }

        void Geometric_v1::draw(RenderTarget &target, RenderStates states) const
        {
            const_cast<Geometric_v1 *>(this)->convert_screen(
                target.getView().getSize().x, target.getView().getSize().y);
            target.draw(m_vert_array, states);
        }
    }
}