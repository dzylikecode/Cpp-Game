#ifndef HUI_GEOMETRIC_V2_H
#define HUI_GEOMETRIC_V2_H
#include "basic.hpp"
#include "Mobject/Mobject.hpp"
#include "Camera/Camera.hpp"

namespace hui
{
    namespace triD
    {
        typedef std::size_t Index_t;
        class Poly_v1
        {
        public:
            enum Attribute : int
            {
                ATTR_NONE = 0,
                SIDED_SINGLE = 0x0000,
                SIDED_DOUBLE = 0x1000,
                SHADE_PURE = 0x0000,
                SHADE_CONSTANT = 0x0000,
                SHADE_FLAT = 0x2000,
                SHADE_GOURAUD = 0x4000,
                SHADE_PHONG = 0x6000,
                STATE_CLIPPED = 0x0001,
                STATE_BACKFACE = 0x0002,
            };

        public:
            Index_t vertx[3];
            Attribute attr;
            Color color;

        public:
            Index_t &operator[](Index_t i) { return vertx[i]; }
            const Index_t &operator[](Index_t i) const { return vertx[i]; }
        };

        //##############################################################################
        // boring overloads for enum class
        //##############################################################################
        template <class T>
        inline T operator|(T a, T b)
        {
            return static_cast<T>(static_cast<int>(a) | static_cast<int>(b));
        }
        template <class T>
        inline T operator&(T a, T b)
        {
            return static_cast<T>(static_cast<int>(a) & static_cast<int>(b));
        }
        template <class T>
        inline T operator|=(T &a, T b)
        {
            return a = a | b;
        }
        template <class T>
        inline T operator&=(T &a, T b)
        {
            return a = a & b;
        }

        //##############################################################################
        // thanks, this is the end of boring overloads for enum class
        //##############################################################################

        class Data3D_v2
        {
        protected:
            float m_max_radius;
            float m_avg_radius;

        public:
            std::vector<Vec3f> m_vert;
            std::vector<Poly_v1> m_poly;

        public:
            float getMaxRadius() const { return m_max_radius; }
            float getAvgRadius() const { return m_avg_radius; }
            std::size_t getNumVert() const { return m_vert.size(); }
            std::size_t getNumPoly() const { return m_poly.size(); }
            void estimate_radius();
            // scale will scale the radius of the shape
            void scaleShape(const Vec3f &ratio);
            void scaleShape(float ratio) { scaleShape(Vec3f{ratio, ratio, ratio}); }
            void resizeVert(std::size_t size) { m_vert.resize(size); }
            void resizePoly(std::size_t size) { m_poly.resize(size); }
            bool loadFromFile(const std::string &filename);
        };

        class Geometric_v2 : public Mobject_v1, public Drawable
        {
        public:
            enum Attribite : int
            {
                ATTR_NONE = 0,
                CULL_X = 0x0001,
                CULL_Y = 0x0002,
                CULL_Z = 0x0004,
                CULL_XYZ = CULL_X | CULL_Y | CULL_Z,
                CULLED = CULL_XYZ,
            };

        private:
            const CameraBasic_v1 *m_camera;
            Attribite m_attribite;
#ifdef HUI_DEBUG
        public:
#endif
            const Data3D_v2 *m_model;
            Data3D_v2 m_tranformed;

        public:
            VertexArray m_vert_array;

        public:
            Geometric_v2() : m_camera(nullptr), m_attribite(ATTR_NONE){};
            void setCamera(const CameraBasic_v1 &camera) { m_camera = &camera; }
            // Data3D_v2 需要与 Geometric_v2 共存
            bool loadFromData(const Data3D_v2 &data);
            float getMaxRadius() const { return m_model->getMaxRadius(); }
            float getAvgRadius() const { return m_model->getAvgRadius(); }
            void update() { process3D(); }
            bool isCulled() const { return m_attribite & CULLED; }

        private:
            virtual void draw(RenderTarget &target, RenderStates states) const;
            void cull(const Attribite &attr);
            void removeBackFace();
            void process3D();
        };
    }
}
#endif