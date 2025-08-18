#pragma once
#include <SFML/Graphics.hpp>

struct CreateLine
{
    sf::RectangleShape shape;

    CreateLine(sf::Vector2f Size, sf::Vector2f position);

    sf::Vector2f getPosition() const; 

    sf::FloatRect getGlobalBounds() const; 

    void draw(sf::RenderWindow& window) const;

    void setPosition(sf::Vector2f pos);

    void rotate(sf::Angle angle);

    void setOrigin(sf::Vector2f pos);

    sf::Vector2f getOrigin() const;

    sf::Vector2f getSize() const;

    void setFillColor(sf::Color color);
};

struct CreateCircle
{
    sf::CircleShape shape;

    CreateCircle(float Size, sf::Vector2f position);

    sf::Vector2f getPosition() const;

    sf::FloatRect getGlobalBounds() const;

    void draw(sf::RenderWindow& window);
};