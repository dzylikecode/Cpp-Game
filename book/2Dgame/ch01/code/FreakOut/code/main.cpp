#include <SFML/Graphics.hpp>
#include <vector>
#include <boost/numeric/ublas/matrix.hpp>

#include "block.h"

const int screen_width = 600;
const int screen_height = 400;

using namespace boost::numeric::ublas;

matrix<Block> blocks;

void create_blocks(int rows, int cols)
{
    blocks.resize(rows, cols);
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            Block block;
            block.create(sf::Vector2f(i * 100, j * 100),
                         sf::Vector2f(100, 100));
            blocks(i, j) = block;
        }
    }
}

class Paddle
{
private:
    sf::RectangleShape shape;

public:
    sf::Vector2f position;

public:
    bool create(sf::Vector2f position)
    {
        this->position = position;
        shape.setSize(sf::Vector2f(100, 20));
        shape.setFillColor(sf::Color::Blue);
        shape.setPosition(position);
        return true;
    }
    void set_position(float x, float y)
    {
        this->position.x = x;
        this->position.y = y;
        shape.setPosition(x, y);
    }
    void draw(sf::RenderWindow &window)
    {
        window.draw(shape);
    }
};

Paddle paddle;

int main(int argc, char *argv[])
{
    sf::RenderWindow window(sf::VideoMode(screen_width, screen_height), "Freak Out!");
    window.setFramerateLimit(90);

    paddle.create(sf::Vector2f(screen_width / 2, screen_height - 20));
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
                switch (event.key.code)
                {
                case sf::Keyboard::A:
                case sf::Keyboard::Left:
                    paddle.set_position(paddle.position.x - 15, paddle.position.y);
                    break;
                case sf::Keyboard::D:
                case sf::Keyboard::Right:
                    paddle.set_position(paddle.position.x + 15, paddle.position.y);
                    break;
                }
            }
        }
        window.clear();
        paddle.draw(window);
        window.display();
    }
    return 0;
}
