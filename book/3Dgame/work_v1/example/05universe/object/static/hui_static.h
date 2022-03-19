#pragma once

#include "basic.hpp"
#include "Camera/Camera.hpp"
#include "something/something.hpp"
#include "object/settings/hui_setting.h"
#include "Geometric/Geometric.hpp"
#include <vector>
#include <random>

class hui_static: public sf::Drawable
{
public:
    static const int tank_num = 24;
    static const int tower_num = 96;
    const hui::triD::CameraEuler_v1 &camera;
    static const int marker_size = 200;
    static const int marker_num_x = 2 * universe_radius / marker_size;
    static const int marker_num_z = 2 * universe_radius / marker_size;
    static const int marker_num = marker_num_x * marker_num_z;

public:
    std::vector<hui::triD::Geometric_v2> geo_tank;
    std::vector<hui::triD::Geometric_v2> geo_marker;
    std::vector<hui::triD::Geometric_v2> geo_tower;
    sf::RectangleShape sky;
    sf::RectangleShape ground;

public:
    hui_static(const hui::triD::CameraEuler_v1 &camera_o);
    void init();
    void update();
    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;
};

hui_static::hui_static(const hui::triD::CameraEuler_v1 &camera_o)
    : camera(camera_o) {}

void hui_static::init()
{
    using namespace hui::triD;
    static Data3D_v2 data_tank;
    data_tank.loadFromFile("RES/tank2.plg");
    data_tank.scaleShape(.75);
    static Data3D_v2 data_marker;
    data_marker.loadFromFile("RES/marker1.plg");
    data_marker.scaleShape(3);
    static Data3D_v2 data_tower;
    data_tower.loadFromFile("RES/tower1.plg");
    data_tower.scaleShape(Vec3f{1.0, 2.0, 1.0});
    for (int i = 0; i < tank_num; ++i)
    {
        using Random = effolkronium::random_static;
        hui::triD::Geometric_v2 tank;
        tank.loadFromData(data_tank);
        auto tank_x = Random::get<float>(-universe_radius, universe_radius);
        auto tank_y = 0.0f;
        auto tank_z = Random::get<float>(-universe_radius, universe_radius);
        tank.setPos(Vec3f{tank_x, tank_y, tank_z});
        tank.setCamera(camera);
        tank.setRotate(rot_mat_xyz<4>(
            0.0f,
            Random::get<float>(-180, 180),
            0.0f));
        geo_tank.emplace_back(tank);
    }
    for (int i = 0; i < tower_num; ++i)
    {
        using Random = effolkronium::random_static;
        hui::triD::Geometric_v2 tower;
        tower.loadFromData(data_tower);
        auto tower_x = Random::get<float>(-universe_radius, universe_radius);
        auto tower_y = 0.0f;
        auto tower_z = Random::get<float>(-universe_radius, universe_radius);
        tower.setPos(Vec3f{tower_x, tower_y, tower_z});
        tower.setCamera(camera);
        tower.setRotate(identity_mat<float, 4>());
        geo_tower.emplace_back(tower);
    }
    for (int i = 0; i < marker_num; ++i)
    {
        using Random = effolkronium::random_static;
        hui::triD::Geometric_v2 marker;
        marker.loadFromData(data_marker);
        // auto marker_x = Random::get<float>(-universe_radius, universe_radius);
        // auto marker_y = 0.0f;
        // auto marker_z = Random::get<float>(-universe_radius, universe_radius);
        // marker.setPos(Vec3f{marker_x, marker_y, marker_z});
        marker.setCamera(camera);
        marker.setRotate(identity_mat<float, 4>());
        geo_marker.emplace_back(marker);
    }

    sky.setPosition(0, 0);
    sky.setSize(Vector2f{video_mode.width, video_mode.height / 2});
    sky.setFillColor(Color(0, 140, 192));
    ground.setPosition(0, video_mode.height / 2);
    ground.setSize(Vector2f{video_mode.width, video_mode.height / 2});
    ground.setFillColor(Color(103, 62, 3));
}

void hui_static::update()
{
    for (int i = 0; i < marker_num_x; ++i)
    {
        for (int j = 0; j < marker_num_z; ++j)
        {
            using Random = effolkronium::random_static;
            using namespace hui::triD;
            auto x = i * marker_size - universe_radius +
                     Random::get<float>(-marker_size / 2, marker_size / 2);
            auto z = j * marker_size - universe_radius +
                     Random::get<float>(-marker_size / 2, marker_size / 2);
            auto y = 0.0f;
            geo_marker[i * marker_num_z + j].setPos(Vec3f{x, y, z});
        }
    }
    for (auto &tank : geo_tank)
    {
        tank.update();
    }
    for (auto &tower : geo_tower)
    {
        tower.update();
    }
    for (auto &marker : geo_marker)
    {
        marker.update();
    }
}

void hui_static::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(sky, states);
    target.draw(ground, states);
    for (auto &tank : geo_tank)
    {
        target.draw(tank, states);
    }
    for (auto &tower : geo_tower)
    {
        target.draw(tower, states);
    }
    for (auto &marker : geo_marker)
    {
        target.draw(marker, states);
    }
}