#include <SFML/Graphics.hpp>

class Block
{
private:
    sf::RectangleShape shape;
    sf::Vector2f position;
    sf::Vector2f size;
    sf::Color color;

public:
    bool create(sf::Vector2f position, sf::Vector2f size, sf::Color color = sf::Color::Green)
    {
        this->position = position;
        this->size = size;
        this->color = color;
        shape.setPosition(position);
        shape.setSize(size);
        shape.setFillColor(color);
        return true;
    }
    void draw(sf::RenderWindow &window)
    {
        window.draw(shape);
    }
};