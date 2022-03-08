#include <SFML/Graphics.hpp>
#include "settings/global.h"
using namespace sf;

template <typename T>
bool IsCollision(const T &rect1, const T &rect2)
{
    return !(rect1.left + rect1.width < rect2.left || rect1.left > rect2.left + rect2.width ||
             rect1.top + rect1.height < rect2.top || rect1.top > rect2.top + rect2.height);
}

template <typename T>
bool is_collision_bound(const T &rect)
{
    return rect.left < 0 || rect.left + rect.width > screen_width ||
           rect.top < 0 || rect.top + rect.height > screen_height;
}