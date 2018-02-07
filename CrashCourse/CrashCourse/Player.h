#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/Audio/Sound.hpp>
#include <vector>
#include "Bullet.h"

class Player
{
public:
	sf::SoundBuffer *shot = nullptr;
	sf::Sound sound;

	std::vector<Bullet*> bullets;
	Player(sf::Vector2f position, sf::Texture *texture);
	~Player();

	void Update(float delta);
	void Draw(sf::RenderWindow & window);

	float getHeading() { return  mHeading; }
	//float getVelocityX() { return mVelocityX; }
	//float getVelocityY() { return mVelocityY; }kat
	sf::Vector2f GetVelocity();


	void CreateBullets(float delta);

	sf::IntRect Player::BoundingBox() const;

	float getVelocityX() { return mVelocityX; }
	float getVelocityY() { return mVelocityY; }
private:
	float mPositionX;
	float mPositionY;

	float mVelocityX;
	float mVelocityY;

	float mHeading;
	int fireRate;
	int maxBullets;

	sf::Texture *mTexture;
	sf::IntRect dstRect;
	sf::Text mTestText;
};

