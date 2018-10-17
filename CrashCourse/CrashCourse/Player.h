
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

	void CreateBullets(float delta);

	sf::IntRect Player::BoundingBox() const;

	sf::Vector2f getPosition() { return mPosition; }
private:
	sf::Vector2f mPosition;

	float mHeading;
	int fireRate;
	int maxBullets;

	sf::Texture *mTexture;
	sf::IntRect dstRect;
};

