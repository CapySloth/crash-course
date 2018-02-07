#include "Bullet.h"
#include "Utils.h"
#include "Entity.h"
#include <cmath>
#include <iostream>

const int Bullet::msDefaultWidth = 5;
const int Bullet::msDefaultHeight = 5;
const sf::Vector2f mVelocity = { 2, 2 };
const sf::Color	Bullet::msDefaultColor = { 255, 255, 255, 255 };		// white
int i = 0;
Bullet::Bullet()
	: mRect()
	, mColor()
{
	mRect.left = 0;
	mRect.top = 0;
	mRect.width = msDefaultHeight;
	mRect.height = msDefaultWidth;
	mColor = msDefaultColor;
	active = false;
	mRect.top = 100;
	mRect.left = 100;
	mVelocity;
}

float Bullet::GetVelocityX() {
	return mVelocity.x;
}
float Bullet::GetVelocityY() {
	return mVelocity.y;
}

sf::Vector2f Bullet::GetVelocity() {
	return mVelocity;
}
void Bullet::SetVelocity(float vx, float vy) {
	mVelocity.x = vx;
	mVelocity.y = vy;
}

void Bullet::SetVelocity(sf::Vector2f velocity) {
	mVelocity = velocity;
}

void Bullet::Reset()
{
	mRect.left = -500;
	mRect.top = -500;
	mRect.width = msDefaultWidth;
	mRect.height = msDefaultHeight;
	mColor = msDefaultColor;
	active = false;
	mVelocity;
}

void Bullet::Move()
{
	////Move the bullet on X axis
	mRect.left += GetVelocityX();
	////Move the bullet on Y axis
	mRect.top += GetVelocityY();

	//If the dot collided or went too far up or down
	//CheckCollision(mRect, object);
}

void Bullet::CalculateTragectory(float delta, float mHeading) {
	float acceleration = 1.0f;
	//Determine facing direction vector
	float dirX = cos(mHeading);
	float dirY = sin(mHeading);
	//Calculate velocity for this frame
	mVelocity.x = dirX  * delta * 500;
	mVelocity.y = dirY  * delta * 500;
}

sf::IntRect Bullet::BoundingBox() const
{
	return mRect;
}

void Bullet::Update(float delta)
{
	if (mRect.top < 0) {
		//mRect.x = mRect.x + 600;
		Reset();
	}
	if (mRect.left  > 700) {

		Reset();
		//mRect.x = mRect.x - 600;
	}

	if (mRect.top < 0) {
		//mRect.y = mRect.y + 600;
		Reset();
	}
	if (mRect.left > 700) {
		//mRect.y = mRect.y - 600;
		Reset();
	}
}

void Bullet::Draw(sf::RenderWindow & window) const
{
	if (active) {
		sf::RectangleShape bullet(sf::Vector2f(mRect.width, mRect.height));
		bullet.setOrigin(sf::Vector2f(1, 1));
		bullet.setFillColor(msDefaultColor);
		bullet.setPosition(sf::Vector2f(mRect.left, mRect.top));
		window.draw(bullet);
	}
}
