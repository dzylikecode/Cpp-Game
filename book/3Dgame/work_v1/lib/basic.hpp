#ifndef HUI_BASIC_H
#define HUI_BASIC_H

#include "boost/qvm/all.hpp"
#include "spdlog/spdlog.h"
#include "SFML/Graphics.hpp"
#include <vector>

namespace hui
{
    namespace triD
    {
        using namespace boost::qvm;
        using namespace spdlog;
        using namespace sf;
        using Quatf = quat<float>;
        using Vec3f = vec<float, 3>;
        using Vec2f = vec<float, 2>;
        using Vec4f = vec<float, 4>;
        using Mat3x3f = mat<float, 3, 3>;
        using Mat4x4f = mat<float, 4, 4>;
        using Vlist = std::vector<Vec4f>;
        using Vindex = unsigned int;

        class Vertex3 : public Vertex
        {
        public:
            Vec3f pos3D;
        };

        class Mobject
        {
        public:
            virtual const Mat4x4f &getLocalMatrix() const = 0;
            virtual const Mat4x4f &getWorldMatrix() const = 0;
        };

        inline Vec3f GetWorldPos(const Mobject &obj, const Vec3f &pos3D)
        {
            return transform_point(obj.getWorldMatrix(), pos3D);
        }
        inline Vec3f GetLocalPos(const Mobject &obj, const Vec3f &pos3D)
        {
            return transform_point(obj.getLocalMatrix(), pos3D);
        }

        // such as: projection matrix
        class Mtransform
        {
        public:
            virtual const Mat4x4f &getTransformationMatrix() const = 0;
        };

        template <class T>
        std::ostream &operator<<(std::ostream &os, const boost::qvm::quat<T> &q)
        {
            os << "[ ";
            for (int i = 0; i < 4; ++i)
            {
                if (i > 0)
                    os << ", ";
                os << q.a[i];
            }
            os << " ]";
            return os;
        }

        template <typename T, int D>
        std::ostream &operator<<(std::ostream &os, const boost::qvm::vec<T, D> &v)
        {
            os << "[ ";
            for (int i = 0; i < D - 1; ++i)
                os << v.a[i] << ", ";
            if (D > 0)
                os << v.a[D - 1];
            os << " ]";
            return os;
        }

        template <typename T, int Rows, int Cols>
        std::ostream &operator<<(std::ostream &os, const boost::qvm::mat<T, Rows, Cols> &m)
        {
            os << "[ ";
            for (int r = 0; r < Rows - 1; ++r)
            {
                for (int c = 0; c < Cols - 1; ++c)
                    os << m.a[r][c] << ", ";
                if (Cols > 0)
                    os << m.a[r][Cols - 1];
                os << ";\n  ";
            }
            if (Rows > 0)
            {
                for (int c = 0; c < Cols - 1; ++c)
                    os << m.a[Rows - 1][c] << ", ";
                if (Cols > 0)
                    os << m.a[Rows - 1][Cols - 1];
            }
            os << " ]";
            return os;
        }

    }
}

#endif