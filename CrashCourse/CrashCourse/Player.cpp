#include "Player.h"
#include "InputManager.h"
#include <math.h>
#include <iostream>
#include <SFML\Audio\SoundBuffer.hpp>
#include <SFML\Audio\Sound.hpp>

#include "AssetManager.h"
#include "Game.h"

#define USE_MATH_DEFINES

Player::Player(sf::Vector2f position, sf::Texture * texture)
	: mPosition(position.x, position.y),
	mHeading(0.0f),
	fireRate(5),
	maxBullets(60),
	dstRect(0,0,32,32),
	mTexture(texture)
{
	if (SoundBufferManager::getInstance().loadAsset("Assets/Shot.wav")) {
		shot = SoundBufferManager::getInstance().getAsset("Assets/Shot.wav");
	}
	sound.setBuffer(*shot);
}

Player::~Player()
{
}

void Player::CreateBullets(float delta) {
	bullets.reserve(maxBullets);
	fireRate--;
	if (fireRate < 0) {
		if (bullets.size() <= maxBullets) {
			Bullet* bullet = new Bullet();
			bullet->setLeft((int)mPosition.x);
			bullet->setTop((int)mPosition.y);
			bullet->CalculateTragectory(delta, mHeading);
			bullet->setActive(true);
			bullets.push_back(bullet);
			fireRate = 5;
		}
		else {
			/* If max number of bullets is reached, then start reusing inactive bullets */
			for (int i = 0; i < bullets.size(); i++) {
				if (!bullets[i]->getActive()) {
					bullets[i]->setLeft((int)mPosition.x);
					bullets[i]->setTop((int)mPosition.y);
					bullets[i]->CalculateTragectory(delta, mHeading);
					bullets[i]->setActive(true);
					std::cout << i << std::endl;
					fireRate = 5;
					break;
				}
			}
		}
		sound.play();
	}
}

void Player::Update(float delta)
{
	float const SPIN_SPEED = 180.0f * 3.14f / 180.0f;

	//Determine spin
	float spinVelocity = 0.0f;
	if (InputManager::getInstance().isKeyDown(InputManager::GK_RIGHT)) {
		spinVelocity = SPIN_SPEED;
	}
	else if (InputManager::getInstance().isKeyDown(InputManager::GK_LEFT)) {
		spinVelocity = -SPIN_SPEED;
	}
	mHeading += spinVelocity * delta;
	int firing_before = 0;
	if (InputManager::getInstance().isKeyDown(InputManager::GK_SPACE)) {
		CreateBullets(delta);
	}
	
	for (int i = 0; i < bullets.size(); i++) {
		if (bullets[i]->getActive()) {
			bullets[i]->Move();
			bullets[i]->Update(delta);
		}
	}
}

void Player::Draw(sf::RenderWindow & window)
{
	dstRect.left = (int)mPosition.x - dstRect.width / 2;
	dstRect.top = (int)mPosition.y - dstRect.height / 2;
	
	float headingDegrees = mHeading * 180.0f / 3.14f;
	sf::RectangleShape player(sf::Vector2f((float)dstRect.width, (float)dstRect.height));
	player.setTexture(TextureManager::getInstance().getAsset("Assets/player_fighter_jet.png"));
	player.setPosition(350, 350);
	player.setRotation(headingDegrees);
	player.setOrigin((float)dstRect.width/2, (float)dstRect.height/2);
	window.draw(player);

	for (int i = 0; i < bullets.size(); i++)
	{
		if (bullets[i]->getActive()) {
			bullets[i]->Draw(window);
		}
	}
}

sf::IntRect Player::BoundingBox() const {
	return dstRect;
}
