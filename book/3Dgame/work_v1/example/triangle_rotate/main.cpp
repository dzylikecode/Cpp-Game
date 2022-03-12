/**
 * @file main.cpp
 * @author your name (you@domain.com)
 * @brief   using right coordinate system:
 * 
 *          up arrow key -> rotate y axis
 *          down arrow key -> rotate z axis
 *          right arrow key -> rotate z axis
 *
 * @version 0.1
 * @date 2022-03-13
 *
 * @copyright Copyright (c) 2022
 *
 */

#include "basic.hpp"
#include "Camera/Camera.hpp"
#include "geometric/geometric.hpp"
#include <iostream>
#include <sstream>
#include <cmath>

inline float DegToRad(float deg)
{
    return deg * M_PI / 180.0f;
}

const unsigned int WINDOW_WIDTH = 640;
const unsigned int WINDOW_HEIGHT = 480;

int main()
{
    using namespace hui::triD;
    using namespace std;
    CameraFocus_v1 camera;
    camera.setPos(Vec3f{100, 100, 100});
    camera.setLookAt(Vec3f{0, 0, 0});
    camera.setUp(Vec3f{0, 1, 0});
    camera.setFar(500);
    camera.setNear(50);
    camera.setFov(DegToRad(90));
    camera.setAspect(WINDOW_WIDTH / (float)WINDOW_HEIGHT);
    Geometric_v1 tri;
    tri.setCamera(camera);
    tri.setPos(Vec3f{0, 0, 0});
    tri.resize(3);
    tri.m_vert[0] = Vec3f{0, 50, 0};
    tri.m_vert[1] = Vec3f{50, -50, 0};
    tri.m_vert[2] = Vec3f{-50, -50, 0};
    tri.m_vert_array.setPrimitiveType(sf::Triangles);
    tri.m_vert_array[0].color = Color::Red;
    tri.m_vert_array[1].color = Color::Green;
    tri.m_vert_array[2].color = Color::Blue;

    Geometric_v1 x_axis;
    x_axis.setCamera(camera);
    x_axis.setPos(Vec3f{0, 0, 0});
    x_axis.resize(2);
    x_axis.m_vert[0] = Vec3f{-100, 0, 0};
    x_axis.m_vert[1] = Vec3f{100, 0, 0};
    x_axis.m_vert_array.setPrimitiveType(sf::Lines);
    x_axis.m_vert_array[0].color = Color::Red;
    x_axis.m_vert_array[1].color = Color::Red;

    Geometric_v1 y_axis;
    y_axis.setCamera(camera);
    y_axis.setPos(Vec3f{0, 0, 0});
    y_axis.resize(2);
    y_axis.m_vert[0] = Vec3f{0, -100, 0};
    y_axis.m_vert[1] = Vec3f{0, 100, 0};
    y_axis.m_vert_array.setPrimitiveType(sf::Lines);
    y_axis.m_vert_array[0].color = Color::Green;
    y_axis.m_vert_array[1].color = Color::Green;

    Geometric_v1 z_axis;
    z_axis.setCamera(camera);
    z_axis.setPos(Vec3f{0, 0, 0});
    z_axis.resize(2);
    z_axis.m_vert[0] = Vec3f{0, 0, -100};
    z_axis.m_vert[1] = Vec3f{0, 0, 100};
    z_axis.m_vert_array.setPrimitiveType(sf::Lines);
    z_axis.m_vert_array[0].color = Color::Blue;
    z_axis.m_vert_array[1].color = Color::Blue;

    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "SFML window 3D");
    window.setFramerateLimit(60);

    int angle = 0;
    enum
    {
        X_AXIS,
        Y_AXIS,
        Z_AXIS,
    } mode = Y_AXIS;
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Escape)
                    window.close();
                if (event.key.code == sf::Keyboard::Up)
                    mode = Y_AXIS;
                if (event.key.code == sf::Keyboard::Down)
                    mode = Z_AXIS;
                if (event.key.code == sf::Keyboard::Right)
                    mode = X_AXIS;
            }
        }
        ++angle;
        if (angle > 360)
            angle = 0;
        if (mode == X_AXIS)
            tri.setRotate(rotx_mat<4>(DegToRad(angle)));
        if (mode == Y_AXIS)
            tri.setRotate(roty_mat<4>(DegToRad(angle)));
        if (mode == Z_AXIS)
            tri.setRotate(rotz_mat<4>(DegToRad(angle)));
        window.clear();
        window.draw(tri);
        window.draw(x_axis);
        window.draw(y_axis);
        window.draw(z_axis);
        window.display();
    }

    return 0;
}