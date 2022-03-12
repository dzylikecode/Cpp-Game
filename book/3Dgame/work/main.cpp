#include "basic.hpp"
#include "Camera/Camera.hpp"
#include "object/triangle/triangle.h"
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
    camera.setPos(Vec3f{0, 0, 100});
    camera.setLookAt(Vec3f{0, 0, 0});
    camera.setUp(Vec3f{0, 1, 0});
    camera.setFar(500);
    camera.setNear(50);
    camera.setFov(DegToRad(90));
    camera.setAspect(WINDOW_WIDTH / (float)WINDOW_HEIGHT);
    Triangle3D tri;
    tri[0].pos3D = Vec3f{0, 50, 0};
    tri[0].color = Color::Red;
    tri[1].pos3D = Vec3f{50, -50, 0};
    tri[1].color = Color::Red;
    tri[2].pos3D = Vec3f{-50, -50, 0};
    tri[2].color = Color::Red;
    tri.setCamera(camera);
    tri.setPos(Vec3f{0, 0, 0});

    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "SFML window 3D");
    window.setFramerateLimit(60);

    int angle = 0;
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        ++angle;
        if (angle > 360)
            angle = 0;
        tri.setRotate(roty_mat<4>(DegToRad(angle)));
        window.clear();
        window.draw(tri);
        window.display();
    }

    return 0;
}