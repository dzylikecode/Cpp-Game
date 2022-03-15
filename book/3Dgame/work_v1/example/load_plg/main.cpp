#include "File/File3D.hpp"
#include <iostream>
#include "Geometric/Geometric.hpp"

inline float DegToRad(float deg)
{
    return deg * M_PI / 180.0f;
}

const unsigned int WINDOW_WIDTH = 640;
const unsigned int WINDOW_HEIGHT = 480;

int main()
{
    using namespace std;
    using namespace hui::triD;
    using namespace hui::triD;
    using namespace std;
    CameraFocus_v1 camera;
    camera.setPos(Vec3f{100, 100, 100});
    camera.setLookAt(Vec3f{0, 0, 0});
    camera.setUp(Vec3f{0, 1, 0});
    camera.setFar(500);
    camera.setNear(50);
    camera.setFov(DegToRad(90));
    camera.setSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    FilePLG file;
    file.open("cube1.plg");
    Data3D_v2 data = file.getData();
    data.scaleShape(5);
    Geometric_v2 geo;
    geo.loadFromData(data);
    geo.setCamera(camera);
    geo.setPos(Vec3f{0, 0, 0});

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

    RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "3D");
    window.setFramerateLimit(60);
    float x_ang = 0, y_ang = 2, z_ang = 0;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Down)
                    x_ang += 1;
                else if (event.key.code == sf::Keyboard::Up)
                    x_ang += -1;
                else if (event.key.code == sf::Keyboard::Left)
                    z_ang += 1;
                else if (event.key.code == sf::Keyboard::Right)
                    z_ang += -1;
            }
        }
        y_ang += 2;
        if (y_ang > 360)
            y_ang -= 360;
        geo.setRotate(rot_mat_xyz<4>(DegToRad(x_ang),
                                     DegToRad(y_ang),
                                     DegToRad(z_ang)));
        window.clear();
        window.draw(x_axis);
        window.draw(y_axis);
        window.draw(z_axis);
        window.draw(geo);
        window.display();
    }
    return 0;
}