/**
 * @file main.cpp
 * @author your name (you@domain.com)
 * @brief
 * command : make run
 * @version 0.1
 * @date 2022-03-15
 *
 * @copyright Copyright (c) 2022
 *
 */
#include "File/File3D.hpp"
#include <iostream>
#include "Geometric/Geometric.hpp"
#include "something/something.hpp"
#include "boost/format.hpp"

const unsigned int WINDOW_WIDTH = 640;
const unsigned int WINDOW_HEIGHT = 480;

int main(int argc, char *argv[])
{
    using namespace std;
    using namespace hui::triD;
    using namespace hui::triD;
    using namespace std;
    CameraFocus_v1 camera;
    camera.setPos(Vec3f{0, 200, 400});
    camera.setLookAt(Vec3f{0, 0, 0});
    camera.setUp(Vec3f{0, 1, 0});
    camera.setFar(8000);
    camera.setNear(50);
    camera.setFov(DegToRad(90));
    camera.setSize(WINDOW_WIDTH, WINDOW_HEIGHT);

    FilePLG file;
    std::string filename;

    if (argv[1] != nullptr)
    {
        filename = argv[1];
    }
    else
    {
        filename = "tank1.plg";
    }

    file.open(filename);
    Data3D_v2 data = file.getData();
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
    float y_ang = 0;
    int view_angle = 0;

    std::vector<Geometric_v2> geo_array;
    std::vector<Vector2f> pos_array;
#define NUM_OBJECTS 16
    for (int x = -NUM_OBJECTS / 2; x < NUM_OBJECTS / 2; x++)
        for (int z = -NUM_OBJECTS / 2; z < NUM_OBJECTS / 2; z++)
        {
            geo_array.push_back(geo);
            pos_array.push_back(Vector2f{float(x), float(z)});
        }

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
            }
        }
        y_ang += 2;
        if (y_ang > 360)
        {
            y_ang -= 360;
        }
        view_angle += 1;
        if (view_angle > 360)
        {
            view_angle -= 360;
        }
        // set camera
        const int camera_dist = 1750;
        auto camera_x = camera_dist * std::cos(DegToRad(view_angle));
        auto camera_y = camera_dist * std::sin(DegToRad(view_angle));
        auto camera_z = 2 * camera_dist * std::sin(DegToRad(view_angle));
        camera.setPos(Vec3f{camera_x, camera_y, camera_z});
        camera.setLookAt(Vec3f{0, 0, 0});

        std::string info = "Objects Culled: ";
        for (decltype(pos_array.size()) i = 0; i < pos_array.size(); ++i)
        {
            auto &geo = geo_array[i];
            auto &pos = pos_array[i];
            auto &x = pos.x;
            auto &y = pos.y;
            auto geo_x = x * 250 + 250 / 2;
            auto geo_y = 0.0f;
            auto geo_z = y * 250 + 250 / 2;
            geo.setPos(Vec3f{geo_x, geo_y, geo_z});
            geo.setRotate(rot_mat_xyz<4>(0.0f,
                                         DegToRad(y_ang),
                                         0.0f));
            geo.update();
            if (geo.isCulled())
            {
                auto pos = boost::format("[%1%, %2%]") % x % y;
                info += pos.str();
            }
        }

        window.clear();

        window.draw(x_axis);
        window.draw(y_axis);
        window.draw(z_axis);

        for (auto &geo : geo_array)
        {
            window.draw(geo);
        }
        window.display();
        std::cout << info << '\r';
    }
    return 0;
}