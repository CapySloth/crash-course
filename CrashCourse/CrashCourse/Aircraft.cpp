#include "aircraft.h"
#include <math.h>
#include <iostream>
#include "Player.h"

const float defaultVel = 1.0f;

Aircraft::Aircraft() {
}


Aircraft::~Aircraft() {
}

Aircraft::Aircraft(int armor, sf::Vector2f speed, float dir, sf::Vector2f pos, sf::Texture *texture)
	: mArmor(armor)
	, mVelocity(speed)
	, mHeading(dir)
	, mPosition(pos)
	, mTexture(texture)
	, active(true)
{
}

void Aircraft::Reset() {
	mArmor = 2;
	mVelocity.x = 0.0f;
	mVelocity.y = 0.0f;
	mHeading = 0.0f;
	mDirection = sf::Vector2f(0.0f, 0.f);
	active = false;
	//Far far away from player bullet range
	dstRect.top = -1000; 
	dstRect.left = -1000;
}
void Aircraft::Move() {
	setPosition(mPosition + getVelocity());
}

void Aircraft::Fire() {
	//instantiate bullet
}

void Aircraft::Death() {
	//Call destructor
}

void Aircraft::Update(float delta, float pHeading) {
	sf::Vector2f pPos = { 300.0f, 300.0f };//Player Position
	sf::Vector2f ePos = { this->getPosition() };//Enemy Position

	float x = 0, y = 0;
	//Calculate opp/adj
	x = pPos.x - ePos.x;
	y = pPos.y - ePos.y;
	//Calculate direction angle
	mHeading = atan2(y, x);
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
	mVelocity.x = -dirX * delta * 100 + x;
	mVelocity.y = -dirY * delta * 100 + y;
	Move();
	if (ePos.x < -400) {
		Reset();
	}
	if (ePos.x  > 1000) {
		Reset();
	}
	if (ePos.y < -400) {
		Reset();
	}
	if (ePos.y > 1000) {
		Reset();
	}

}

void Aircraft::Draw(sf::RenderWindow & window) {
	if (this->active) {
		dstRect = sf::IntRect(0, 0, 32, 32);

		dstRect.left = (int)mPosition.x - dstRect.width / 2;
		dstRect.top = (int)mPosition.y - dstRect.height / 2;

		sf::RectangleShape aircraft(sf::Vector2f(dstRect.width, dstRect.height));

		aircraft.setTexture(mTexture);
		aircraft.setOrigin(sf::Vector2f(dstRect.width / 2, dstRect.height / 2));
		
		float headingDegrees = mHeading * 180.0f / 3.14; //Change to consant PI
		aircraft.setRotation(headingDegrees);
		aircraft.setPosition((int)mPosition.x, (int)mPosition.y);
		window.draw(aircraft);
	}
}
