// DEMO8_3.CPP 8-bit polygon demo
// g++ main.cpp -o ../../bin/main -lsfml-graphics -lsfml-window -lsfml-system -g
// ../../bin/main
#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>
#include <boost/format.hpp>
#include <spdlog/spdlog.h>
#include <vector>
#include "boost/random.hpp"
#include "boost/generator_iterator.hpp"
#include <time.h>

// default screen size
#define SCREEN_WIDTH 640 // size of screen
#define SCREEN_HEIGHT 480

#define NUM_ASTEROIDS 64

class Polygon
{
private:
    sf::VertexArray vertices;
    std::vector<sf::Vector2f> shape;

public:
    sf::Color color;
    sf::Vector2f position;
    sf::Vector2f velocity;

private:
    void convert_local_to_world()
    {
        for (int i = 0; i < vertices.getVertexCount(); i++)
        {
            vertices[i].position = shape[i] + position;
        }
    }

public:
    bool create_shape(const std::vector<sf::Vector2f> &shape)
    {
        this->shape = shape;
        vertices.setPrimitiveType(sf::PrimitiveType::LineStrip);
        vertices.resize(shape.size());
        for (int i = 0; i < shape.size(); i++)
        {
            vertices[i].position = shape[i];
            vertices[i].color = color;
        }
        return true;
    }
    void draw(sf::RenderWindow &window)
    {
        convert_local_to_world();
        window.draw(vertices);
    }
};

Polygon asteroids[NUM_ASTEROIDS]; // the asteroids

typedef boost::mt19937 RNGType;
RNGType rng(time(NULL));
boost::uniform_int<> color_part(0, 255);
boost::variate_generator<RNGType, boost::uniform_int<>>
    color_part_generator(rng, color_part);

#define random_color() sf::Color(color_part_generator(), color_part_generator(), color_part_generator())

boost::uniform_int<> position_part_x(0, SCREEN_WIDTH);
boost::uniform_int<> position_part_y(0, SCREEN_HEIGHT);
boost::variate_generator<RNGType, boost::uniform_int<>>
    position_part_x_generator(rng, position_part_x);
boost::variate_generator<RNGType, boost::uniform_int<>>
    position_part_y_generator(rng, position_part_y);

#define random_position() sf::Vector2f(position_part_x_generator(), position_part_y_generator())

boost::uniform_int<> velocity_part_x(-8, 8);
boost::uniform_int<> velocity_part_y(-8, 8);
boost::variate_generator<RNGType, boost::uniform_int<>>
    velocity_part_x_generator(rng, velocity_part_x);
boost::variate_generator<RNGType, boost::uniform_int<>>
    velocity_part_y_generator(rng, velocity_part_y);

#define random_velocity() sf::Vector2f(velocity_part_x_generator(), velocity_part_y_generator())

// define points of asteroid

sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Polygon");

int main(int argc, char *argv[])
{
    window.setFramerateLimit(30);

    std::vector<sf::Vector2f> asteroid_vertices = {
        sf::Vector2f(33, -3),
        sf::Vector2f(9, -18),
        sf::Vector2f(-12, -9),
        sf::Vector2f(-21, -12),
        sf::Vector2f(-9, 6),
        sf::Vector2f(-15, 15),
        sf::Vector2f(-3, 27),
        sf::Vector2f(21, 21),
        sf::Vector2f(33, -3),
    };

    // loop and initialize all asteroids
    for (int curr_index = 0; curr_index < NUM_ASTEROIDS; curr_index++)
    {
        // initialize the asteroid intonation
        asteroids[curr_index].position = random_position(); // position it
        asteroids[curr_index].velocity = random_velocity(); // give it a velocity
        asteroids[curr_index].color = random_color();
        asteroids[curr_index].create_shape(asteroid_vertices);
    }
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // clear out the back buffer
        window.clear();

        // draw all the asteroids
        for (int curr_index = 0; curr_index < NUM_ASTEROIDS; curr_index++)
        {
            // glow asteroids
            asteroids[curr_index].color = random_color();

            // do the graphics
            asteroids[curr_index].draw(window);

            // move the asteroid
            asteroids[curr_index].position += asteroids[curr_index].velocity;

            // test for out of bounds
            if (asteroids[curr_index].position.x > SCREEN_WIDTH + 100)
                asteroids[curr_index].position.x = -100;

            if (asteroids[curr_index].position.y > SCREEN_HEIGHT + 100)
                asteroids[curr_index].position.y = -100;

            if (asteroids[curr_index].position.x < -100)
                asteroids[curr_index].position.x = SCREEN_WIDTH + 100;

            if (asteroids[curr_index].position.y < -100)
                asteroids[curr_index].position.y = SCREEN_HEIGHT + 100;
        }

        window.display();
    }
}