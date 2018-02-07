#include "Cloud.h"
#include <iostream>
Cloud::Cloud(sf::Texture *texture, int width, int height, sf::Uint8 alpha)
	:mTexture(*texture), mWidth(width), mHeight(height), mAlpha(alpha), velX(0.0f), velY(0.0f)
{
}

Cloud::~Cloud()
{
}

void Cloud::setSreenSize(int w, int h)
{
	mScreenWidth = w;
	mScreenHeight = h;
}

void Cloud::setVelocity(float x, float y)
{
	velX = x;
	velY = y;
}

void Cloud::CalculateTragectory(float delta, float mHeading) {
	//Get Dir
	float dirX = cos(mHeading);
	float dirY = sin(mHeading);
	velX = -dirX * delta * defaultVel * 80;
	velY = -dirY * delta * defaultVel * 80;
}

void Cloud::Update(float delta)
{
	posX += velX;
	posY += velY;

	if (posX - mWidth > mScreenWidth) {
		posX = 0 - mWidth / 2;
	}
	if (posY - mHeight > mScreenHeight) {
		posY = 0 - mHeight / 2;
	}
	if (posX < 0 - mWidth) {
		posX = mScreenWidth + mWidth / 2;
	}
	if (posY < 0 - mHeight) {
		posY = mScreenHeight + mWidth / 2;
	}
}

void Cloud::Draw(sf::RenderWindow & window)
{
	sf::IntRect dstRect;
	mTexture.setSmooth(true);
	sf::RectangleShape cloud(sf::Vector2f(mWidth, mHeight));

	cloud.setTexture(&mTexture);
	//dstRect.width = mWidth;
	//dstRect.height = mHeight;

	//cloud.setTextureRect(dstRect);
	cloud.setPosition((int)posX - dstRect.width / 2, (int)posY - dstRect.height / 2);
	cloud.setFillColor(sf::Color(255, 255, 255, mAlpha));

	window.draw(cloud);
}


