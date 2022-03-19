#include "Geometric/Geometric_v2.h"
#include <cmath>
#include "File/File3D.hpp"
namespace hui
{
    namespace triD
    {
        void Data3D_v2::estimate_radius()
        {
            m_max_radius = 0;
            m_avg_radius = 0;
            for (auto &v : m_vert)
            {
                auto radius = mag(v);
                m_max_radius = std::max(m_max_radius, radius);
                m_avg_radius += radius;
            }
            m_avg_radius /= m_vert.size();
        }

        void Data3D_v2::scaleShape(const Vec3f &ratio)
        {
            for (auto &v : m_vert)
            {
                X(v) *= X(ratio);
                Y(v) *= Y(ratio);
                Z(v) *= Z(ratio);
            }
            auto max_ratio = std::max(X(ratio), std::max(Y(ratio), Z(ratio)));
            m_max_radius *= max_ratio;
            m_avg_radius *= max_ratio;
        }

        bool Data3D_v2::loadFromFile(const std::string &filename)
        {
            FilePLG file;
            if (!file.open(filename))
            {
                spdlog::error("failed to open file {}", filename);
                return false;
            }
            *this = file.getData();
            return true;
        }

        bool Geometric_v2::loadFromData(const Data3D_v2 &data)
        {
            m_model = &data;
            m_tranformed = data;

            return true;
        }

        void Geometric_v2::cull(const Attribite &attr)
        {
            Vec3f vect_3 = zero_vec<float, 3>();
            Vec4f vect_4D = XYZ1(vect_3);
            // 转化为 camera 视角的原点
            // 不知道先算后面会不会加快呢
            vect_4D = m_camera->getLocalMatrix() * getWorldMatrix() * vect_4D;
            auto x = X(vect_4D);
            auto y = Y(vect_4D);
            auto z = Z(vect_4D);
            auto width = m_camera->getWidth();
            auto height = m_camera->getHeight();
            auto view_dist = -m_camera->getViewDist();
            if (attr & CULL_Z)
            {
                auto far = -m_camera->getFar(); // 看向的是负半轴
                auto near = -m_camera->getNear();
                // 此时 z 就是负值
                if (z + getMaxRadius() < far || // 负的更多,超出视野
                    z - getMaxRadius() > near)
                {
                    m_attribite |= CULL_Z;
                }
            }
            z -= getMaxRadius(); // 考虑最远的横截面
            if (attr & CULL_X)
            {
                // 根据相机的锥形视野, 计算物体(0,0)点所在的视口大小
                // 利用俯视图, 就是简单的相似三角形
                // 注意是负半轴
                auto width_max = width / 2.0f / view_dist * z;
                if (x + getMaxRadius() < -width_max ||
                    x - getMaxRadius() > width_max)
                {
                    m_attribite |= CULL_X;
                }
            }

            if (attr & CULL_Y)
            {
                auto height_max = height / 2.0f / view_dist * z;
                if (y + getMaxRadius() < -height_max ||
                    y - getMaxRadius() > height_max)
                {
                    m_attribite |= CULL_Y;
                }
            }
        }

        /**
         * @brief 当前应该针对物体在世界坐标系
         *
         */
        void Geometric_v2::removeBackFace()
        {
            if (m_attribite & CULLED)
                return;

            for (auto &poly : m_tranformed.m_poly)
            {
                if (poly.attr & Poly_v1::STATE_BACKFACE ||
                    poly.attr & Poly_v1::STATE_CLIPPED ||
                    poly.attr & Poly_v1::SIDED_DOUBLE)
                    continue;
                auto &v0 = m_tranformed.m_vert[poly.vertx[0]];
                auto &v1 = m_tranformed.m_vert[poly.vertx[1]];
                auto &v2 = m_tranformed.m_vert[poly.vertx[2]];
                // 逆时针为外法线
                auto normal = cross(v1 - v0, v2 - v0); // maybe we can nomalize it
                auto light_dir = m_camera->getPos() - v0;
                auto dot_product = dot(normal, light_dir);
                // 说明照相机在 ploy 的负半空间上
                // 也就是 ploy 表面的光照不会照到相机上面
                if (dot_product < 0)
                {
                    poly.attr |= Poly_v1::STATE_BACKFACE;
                }
            }
        }

        void Geometric_v2::process3D()
        {
            // clear the flag
            m_attribite = ATTR_NONE;
            m_tranformed = *m_model;
            // transform to the world coordinate
            for (auto &v : m_tranformed.m_vert)
            {
                v = XYZ(getWorldMatrix() * XYZ1(v));
            }
            cull(CULL_XYZ);
            removeBackFace();
            m_vert_array.clear();
            for (auto &v : m_tranformed.m_vert)
            {
                auto pos3D = m_camera->getTransformationMatrix() * XYZ1(v);
                v = XYZ(pos3D);
                auto pos2D = XY(pos3D) / W(pos3D);
                Vertex tmp_2D;
                tmp_2D.position = Vector2f(
                    (X(pos2D) + 1) / 2 * m_camera->getWidth(),
                    (1 - Y(pos2D)) / 2 * m_camera->getHeight());
                m_vert_array.append(tmp_2D);
            }
        }

        void Geometric_v2::draw(RenderTarget &target, RenderStates states) const
        {
            if (m_attribite & CULLED)
                return;
            for (auto &sur : m_tranformed.m_poly)
            {

                Vertex v_list[] = {m_vert_array[sur.vertx[0]],
                                   m_vert_array[sur.vertx[1]],
                                   m_vert_array[sur.vertx[2]],
                                   m_vert_array[sur.vertx[0]]};
                v_list[0].color = sur.color;
                v_list[1].color = sur.color;
                v_list[2].color = sur.color;

                if (sur.attr & Poly_v1::STATE_BACKFACE)
                {
                    continue;
                }
                if (sur.attr & Poly_v1::STATE_CLIPPED)
                {
                    continue;
                }
                target.draw(v_list, sizeof(v_list) / sizeof(Vertex),
                            PrimitiveType::LineStrip);
            }
        }
    }
}