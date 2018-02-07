#include "Player.h"
#include "InputManager.h"
#include "AssetManager.h"
#include "Game.h"
#define USE_MATH_DEFINES
#include <math.h>
#include <iostream>
#include <SFML\Audio\SoundBuffer.hpp>
#include <SFML\Audio\Sound.hpp>


Player::Player(sf::Vector2f position, sf::Texture * texture)
	: mPositionX(position.x), mPositionY(position.y),
	mVelocityX(0.0f),
	mVelocityY(0.0f),
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
	mTestText.setPosition(333, 100);
	mTestText.setCharacterSize(24);
	mTestText.setFillColor(sf::Color::White);
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
			bullet->SetLeft((int)mPositionX);
			bullet->SetTop((int)mPositionY);
			bullet->CalculateTragectory(delta, mHeading);
			bullet->SetActive(true);
			bullets.push_back(bullet);
			fireRate = 5;
		}
		else {
			/* If max number of bullets is reached, then start reusing inactive bullets */
			for (int i = 0; i < bullets.size(); i++) {
				if (!bullets[i]->GetActive()) {
					bullets[i]->SetLeft((int)mPositionX);
					bullets[i]->SetTop((int)mPositionY);
					bullets[i]->CalculateTragectory(delta, mHeading);
					bullets[i]->SetActive(true);
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
		if (bullets[i]->GetActive()) {
			bullets[i]->Move();
			bullets[i]->Update(delta);
		}
	}
}

void Player::Draw(sf::RenderWindow & window)
{
	
	dstRect.left = (int)mPositionX - dstRect.width / 2;
	dstRect.top = (int)mPositionY - dstRect.height / 2;
	
	float headingDegrees = mHeading * 180.0f / 3.14f;
	sf::RectangleShape player(sf::Vector2f((float)dstRect.width, (float)dstRect.height));
	player.setTexture(TextureManager::getInstance().getAsset("Assets/player_fighter_jet.png"));
	player.setPosition(350, 350);
	player.setRotation(headingDegrees);
	player.setOrigin((float)dstRect.width/2, (float)dstRect.height/2);
	/*sf::RectangleShape boxCollider(sf::Vector2f(dstRect.width, dstRect.height));
	boxCollider.setPosition(dstRect.left, dstRect.top);
	boxCollider.setFillColor(sf::Color::Green);
	window.draw(boxCollider);*/
	window.draw(player);

	for (int i = 0; i < bullets.size(); i++)
	{
		if (bullets[i]->GetActive()) {
			bullets[i]->Draw(window);
		}
	}
}

sf::IntRect Player::BoundingBox() const {
	return dstRect;
}
