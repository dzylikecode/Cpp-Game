#ifndef HUI_MOBJECT_V1_H
#define HUI_MOBJECT_V1_H
#include "basic.hpp"

namespace hui
{
    namespace triD
    {

        class Mobject_v1 : public Mobject
        {
        private:
            Mat4x4f m_local; // local matrix = inverse(world)
            Mat4x4f m_world;
            Mat4x4f m_translate;
            Mat4x4f m_rotate;
            Vec3f m_pos;
            bool m_dirty;   // 给类的内部使用的标记
            bool m_changed; // 给子类使用的标记

        public:
            Mobject_v1();
            virtual const Mat4x4f &getLocalMatrix() const { return const_cast<Mobject_v1 *>(this)->localMat(); }
            virtual const Mat4x4f &getWorldMatrix() const { return const_cast<Mobject_v1 *>(this)->worldMat(); }
            void setPos(const Vec3f &pos);
            void setRotate(const Mat4x4f &rotate);
            const Vec3f &getPos() const { return m_pos; }
            const Mat4x4f &getRotate() const { return m_rotate; }

        protected:
            bool clsDirtySub() { return !(m_changed = false); } // yes, equal
            bool isDirtySub() const { return m_changed; }

        private:
            const Mat4x4f &localMat();
            const Mat4x4f &worldMat();
            bool isDirty() const { return m_dirty; }
            bool clsDirty() { return true; }
        };
    }
}
#endif