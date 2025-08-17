#include "Shapes.h"

// ========================Line========================
CreateLine:: CreateLine(sf::Vector2f Size, sf::Vector2f position)
{
    shape.setPosition(position);
    shape.setSize(Size);
}

sf::Vector2f CreateLine::getPosition() const
{
    return shape.getPosition();
}

sf::FloatRect CreateLine::getGlobalBounds() const
{
    return shape.getGlobalBounds();
}

void CreateLine::draw(sf::RenderWindow& window) const
{
    window.draw(shape);
}

void CreateLine::rotate(sf::Angle angle)
{
    shape.setRotation(angle);
}

void CreateLine::setOrigin(sf::Vector2f pos)
{
    shape.setOrigin(pos);
}

sf::Vector2f CreateLine::getOrigin() const
{
    return shape.getOrigin();
}

sf::Vector2f CreateLine::getSize() const
{
    return shape.getSize();
}

void CreateLine::setFillColor(sf::Color color)
{
    shape.setFillColor(color);
}

// ========================Circle======================== 
CreateCircle::CreateCircle(float Size, sf::Vector2f position)
{
    shape.setPosition(position);
    shape.setRadius(Size);
}

sf::Vector2f CreateCircle::getPosition() const
{
    return shape.getPosition();
}

sf::FloatRect CreateCircle::getGlobalBounds() const
{
    return shape.getGlobalBounds();
}

void CreateCircle::draw(sf::RenderWindow& window)
{
    window.draw(shape);
}

