#ifndef HUI_CAMERA_BASIC_H
#define HUI_CAMERA_BASIC_H
#include "Mobject/Mobject.hpp"
#include "Projection/Projection.hpp"
#include "basic.hpp"

namespace hui
{
    namespace triD
    {
        class CameraBasic_v1 : public Mobject_v1, public Perspective
        {
        public:
            virtual const unsigned int getWidth() const = 0;
            virtual const unsigned int getHeight() const = 0;
            virtual float getViewDist() const = 0;
            virtual void setSize(unsigned int width, unsigned int height) = 0;
            virtual bool isDirty() const { return Perspective::isDirty() || Mobject_v1::isDirty(); }
        };
    }
}

#endif