#include "Images.h"

void Images::initTexture()
{
	texture = new sf::Texture(this->getSize());
}

void Images::initSprite()
{
	sprite = new sf::Sprite(*texture);
}

Images::Images(sf::Vector2u ImageSize)
{
	this->resize(ImageSize);
	initTexture();
	initSprite();
}	

Images::~Images()
{
	delete sprite;
	delete texture; 
}
