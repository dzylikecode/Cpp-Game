#pragma once

#include "basic.hpp"
#include "Camera/Camera.hpp"
#include "something/something.hpp"
#include "object/settings/hui_setting.h"
#include "Geometric/Geometric.hpp"
#include <iostream>

class hui_player : public sf::Drawable
{
public:
    hui::triD::Geometric_v2 geo_play;
    hui::triD::CameraEuler_v1 camera;
    int tank_acc;
    static const int TANK_ACC = 15;
    int cam_y_angle;
    int turning_angle; // 描述玩家转向与 camera 的角度差
    float tank_speed;
    static const int camera_distance = 150;
    static const int max_turning_angle = 15;
    bool bturning;

public:
    void init();
    void input(const sf::Event &event);
    void update(const sf::Time &delta_time);
    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;
};

void hui_player::init()
{
    using namespace hui::triD;
    camera.setPos(Vec3f{0, 40, 0});
    camera.setRotate(identity_mat<float, 4>());
    camera.setFov(DegToRad(120));
    camera.setFar(12000);
    camera.setNear(100);
    camera.setSize(video_mode.width, video_mode.height);

    static Data3D_v2 data_play;
    data_play.loadFromFile("RES/tank3.plg");
    data_play.scaleShape(Vec3f{.75, .75, -.75});
    geo_play.loadFromData(data_play);
    geo_play.setPos(Vec3f{0, 0, 0});
    geo_play.setRotate(identity_mat<float, 4>());
    geo_play.setCamera(camera);
    tank_acc = TANK_ACC;
    tank_speed = 0;
    cam_y_angle = 0;
    turning_angle = 0;
    bturning = false;
}

void hui_player::input(const sf::Event &event)
{
    using namespace hui::triD;
    // if (event.type == sf::Event::KeyPressed)
    // {
    //     if (event.key.code == sf::Keyboard::Space)
    //     {
    //         tank_acc = TANK_ACC * 5;
    //     }
    //     if (event.key.code == sf::Keyboard::W)
    //     {
    //         tank_speed = tank_acc;
    //     }
    //     if (event.key.code == sf::Keyboard::S)
    //     {
    //         tank_speed = -tank_acc;
    //     }
    //     if (event.key.code == sf::Keyboard::D)
    //     {
    //         cam_y_angle -= 3;
    //         turning_angle -= 2;
    //         if (turning_angle < -max_turning_angle)
    //         {
    //             turning_angle = -max_turning_angle;
    //         }
    //         bturning = true;
    //     }
    //     if (event.key.code == sf::Keyboard::A)
    //     {
    //         cam_y_angle += 3;
    //         turning_angle += 2;
    //         if (turning_angle > max_turning_angle)
    //         {
    //             turning_angle = max_turning_angle;
    //         }
    //         bturning = true;
    //     }
    // }
    // if (event.type == sf::Event::KeyReleased)
    // {
    //     if (event.key.code == sf::Keyboard::Space)
    //     {
    //         tank_acc = TANK_ACC;
    //     }
    //     if (event.key.code == sf::Keyboard::A || event.key.code == sf::Keyboard::D)
    //     {
    //         bturning = false;
    //     }
    // }
}

void hui_player::update(const sf::Time &delta_time)
{
    using namespace hui::triD;

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        {
            tank_acc = TANK_ACC * 5;
        }
        else 
        {
            tank_acc = TANK_ACC;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        {
            tank_speed = tank_acc;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        {
            tank_speed = -tank_acc;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        {
            cam_y_angle -= 3;
            turning_angle -= 2;
            if (turning_angle < -max_turning_angle)
            {
                turning_angle = -max_turning_angle;
            }
            bturning = true;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        {
            cam_y_angle += 3;
            turning_angle += 2;
            if (turning_angle > max_turning_angle)
            {
                turning_angle = max_turning_angle;
            }
            bturning = true;
        }
        if (!sf::Keyboard::isKeyPressed(sf::Keyboard::A) && !sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        {
            bturning = false;
        }


    // 更新 camera 的角度
    camera.setRotate(rot_mat_xyz<4>(0.0f,
                                    DegToRad(cam_y_angle),
                                    0.0f));
    // 更新 camera 的位置
    Vec3f camera_relative_speed{0, 0, -tank_speed}; // 注意坐标系
    Vec3f camera_absolute_speed = XYZ(camera.getWorldMatrix() * XYZ1(camera_relative_speed));
    camera_absolute_speed -= camera.getPos();
    // auto camera_new_pos = camera.getPos() + camera_absolute_speed * delta_time.asSeconds();
    auto camera_new_pos = camera.getPos() + camera_absolute_speed;
    camera.setPos(camera_new_pos);
    // 更新 geo_play 的位置, 相对于 camera
    Vec3f geo_play_pos{0, -70, -camera_distance};
    Vec3f geo_world_pos = XYZ(camera.getWorldMatrix() * XYZ1(geo_play_pos));
    geo_play.setPos(geo_world_pos);
    // 更新 geo_play 的角度, 相对于 camera
    auto geo_play_rotate = rot_mat_xyz<4>(0.0f,
                                          DegToRad(cam_y_angle + turning_angle),
                                          0.0f);
    geo_play.setRotate(geo_play_rotate);
    geo_play.update();

    tank_speed = 0;
    if (!bturning)
    {
        if (turning_angle < 0)
        {
            turning_angle += 1;
        }
        if (turning_angle > 0)
        {
            turning_angle -= 1;
        }
    }
}

void hui_player::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(geo_play);
}