#include "Mobject/Mobject_v1.h"

namespace hui
{
    namespace triD
    {
        Mobject_v1::Mobject_v1() : m_dirty(false), m_changed(false)
        {
            set_identity(m_translate);
            set_identity(m_rotate);
        }
        void Mobject_v1::setPos(const Vec3f &pos)
        {
            if (m_pos != pos)
            {
                m_pos = pos;
                m_translate = translation_mat(m_pos);
                m_dirty = true;
                m_changed = true;
            }
        }
        void Mobject_v1::setRotate(const Mat4x4f &rotate)
        {
            if (m_rotate != rotate)
            {
                m_rotate = rotate;
                m_dirty = true;
                m_changed = true;
            }
        }
        const Mat4x4f &Mobject_v1::localMat()
        {
            if (this->isDirty())
            {
                m_world = m_translate * m_rotate;
                // 有两种理解方式: (注意这里的位置坐标是世界坐标)
                // 1. 先将相机旋转, 然后按照世界坐标系平移
                //    即 xyz1 = view * xyz; xyz2 = pos_mat * xyz1
                // 2. 先将相机坐标系平移, 然后按照相机坐标系进行旋转
                //    即 coord1 = coord * pos_mat; coord2 = coord1 * view
                // 二者是一致的
                m_local = inverse(m_world);
                m_dirty = false;
                m_changed = clsDirty();
            }
            return m_local;
        }
        const Mat4x4f &Mobject_v1::worldMat()
        {
            getLocalMatrix();
            return m_world;
        }
    }
}