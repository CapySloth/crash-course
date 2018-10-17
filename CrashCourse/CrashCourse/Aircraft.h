#pragma once
#include <SFML\Graphics.hpp>

#include "Bullet.h"

class Aircraft
{
	int mArmor;

	sf::Vector2f mVelocity;
	sf::Vector2f mDirection;
	sf::Vector2f mPosition;
	float mHeading;

	sf::IntRect dstRect;//HitBox
	sf::Texture *mTexture;

	bool active;
public:
	Aircraft();
	~Aircraft();

	Aircraft(int armor,sf::Vector2f speed, float dir, sf::Vector2f pos, sf::Texture *texture);

	std::vector<Bullet*> bullets;

	int getArmor() { return mArmor; }

	sf::Vector2f getVelocity() { return mVelocity; }
	sf::Vector2f getPosition() { return mPosition; }
	sf::IntRect getHitBox() { return dstRect; }

	bool getActive() const { return active; };

	void setActive(bool act) { active = act; };
	void setPosition(sf::Vector2f pos) { mPosition = pos; }
	void removeArmor() { mArmor--; }



	void Move();
	void Fire();
	void Death();
	void Reset();

	void Update(float delta, float mHeading);

	void Draw(sf::RenderWindow & window);

	void setArmor(int armor) { mArmor = armor; };
};

