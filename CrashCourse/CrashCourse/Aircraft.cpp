#include "aircraft.h"
#include <math.h>
#include <iostream>
#include "Player.h"

const float defaultVel = 1.0f;

Aircraft::Aircraft() {
}


Aircraft::~Aircraft() {
}

Aircraft::Aircraft(int armor, float speedX, float speedY, float dir, sf::Vector2f pos, sf::Texture *texture)
	: mArmor(armor)
	, velX(speedX)
	, velY(speedY)
	, mHeading(dir)
	, mPos(pos)
	, mTexture(texture)
	, active(true)
{
}

sf::Vector2f Aircraft::getPosition() const {
	return mPos;
}

void Aircraft::setPosition(sf::Vector2f pos) {
	mPos = pos;
}

void Aircraft::Reset() {
	mArmor = 2;
	velX = 0.0f;
	velY = 0.0f;
	mHeading = 0.0f;
	mDirX = 0.0f;
	mDirY = 0.0f;
	active = false;
	dstRect.top = -1000; //Far far away from player bullet range
	dstRect.left = -1000;
}
void Aircraft::Move() {
	mPos.x += GetVelocityX();
	mPos.y += GetVelocityY();
}

void Aircraft::Fire() {
	//instantiate bullet
}

void Aircraft::Death() {
	//Call destructor
}

void Aircraft::Update(float delta, float pHeading) {
	//////Spining All logic 
	sf::Vector2f pPos = { 300.0f, 300.0f };//Player Position
	sf::Vector2f ePos = { this->getPosition() };//Enemy Position

	float x = 0, y = 0;
	//Calculate opp/adj
	x = pPos.x - mPos.x;
	y = pPos.y - mPos.y;
	//Calculate direction angle
	mHeading = atan2(y, x);
	//std::cout << mHeading << std::endl;
	//Calculate hyp
	float magnitude = sqrt(x*x + y*y);
	//For player "Counter velocity"
	float dirX = cos(pHeading);
	float dirY = sin(pHeading);
	//Normalize
	x /= magnitude;
	y /= magnitude;
	//Set speed
	x *= 1;
	y *= 1;
	//Player counter velocity + Enemy going ham to get to center, poor enemy
	velX = -dirX * delta * 100 + x;
	velY = -dirY * delta * 100 + y;
	Move();
	if (ePos.x < -400) {
		//mRect.x = mRect.x + 600;
		Reset();
	}
	if (ePos.x  > 1000) {
		Reset();
		//mRect.x = mRect.x - 600;
	}

	if (ePos.y < -400) {
		//mRect.y = mRect.y + 600;
		Reset();
	}
	if (ePos.y > 1000) {
		//mRect.y = mRect.y - 600;
		Reset();
	}

}

void Aircraft::Draw(sf::RenderWindow & window) {
	if (this->active) {
		dstRect = sf::IntRect(0, 0, 32, 32);

		dstRect.left = (int)mPos.x - dstRect.width / 2;
		dstRect.top = (int)mPos.y - dstRect.height / 2;

		sf::RectangleShape aircraft(sf::Vector2f(dstRect.width, dstRect.height));

		aircraft.setTexture(mTexture);
		aircraft.setOrigin(sf::Vector2f(dstRect.width / 2, dstRect.height / 2));
		
		float headingDegrees = mHeading * 180.0f / 3.14; //Change to consant PI
		aircraft.setRotation(headingDegrees);
		aircraft.setPosition((int)mPos.x, (int)mPos.y);
		/*sf::RectangleShape boxCollider(sf::Vector2f(dstRect.width, dstRect.height));
		boxCollider.setPosition(dstRect.left, dstRect.top);
		boxCollider.setFillColor(sf::Color::Green);
		window.draw(boxCollider);*/
		window.draw(aircraft);
		/*	SDL_RenderCopyEx(renderer, mTexture, nullptr, &dstRect,
			headingDegrees, nullptr, SDL_FLIP_NONE
		);*/
	}
}

sf::IntRect Aircraft::BoundingBox() const {
	return dstRect;
}

