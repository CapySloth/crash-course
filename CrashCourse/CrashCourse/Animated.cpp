#include "Animated.h"
#include "Utils.h"
#include <iostream>
Animated::Animated()
{
	texture = nullptr;
	mWidth = 0;
	mHeight = 0;
}

Animated::~Animated()
{
	free();
}

void Animated::free()
{
	if (texture != nullptr) {
		texture = nullptr;
		mWidth = 0;
		mHeight = 0;
	}
}

void Animated::render(sf::RenderWindow &window, int x, int y, sf::IntRect *sprite)
{
	sf::IntRect quad = { x, y, mWidth, mHeight };

	
	//if (sprite != nullptr) {
	quad.width = sprite->width;
	quad.height = sprite->height;
	quad.left = sprite->left;
	quad.top = sprite->top;
	//}

	sf::Sprite explosion(*texture);
	//explosion.setScale();//Set width of sprite 46
	explosion.setTextureRect(quad);
	explosion.setPosition(x - quad.width / 2, y - quad.height / 2);
	//explosion.setOrigin(sf::Vector2f(quad.width/2, quad.height/2));
	//std::cout << quad.top << std::endl;
	window.draw(explosion);
	//SDL_RenderCopy(renderer, text, sprite, &quad);
}

int Animated::getWidth()
{
	return mWidth;
}

int Animated::getHeight()
{
	return mHeight;
}
