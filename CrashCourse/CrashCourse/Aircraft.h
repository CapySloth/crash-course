#pragma once
#include <SFML\Graphics.hpp>
#include "Bullet.h"

class Aircraft
{
	int mArmor;
	float velX;
	float velY;
	float mHeading;
	float mDirX;
	float mDirY;
	sf::Vector2f mPos;
	sf::Texture *mTexture;
	bool active;
	sf::IntRect dstRect;

public:
	Aircraft();
	~Aircraft();

	Aircraft(int armor, float speedX, float speedY, float dir, sf::Vector2f pos, sf::Texture *texture);

	std::vector<Bullet*> bullets;

	int GetArmor() { return mArmor; }
	void ReduceArmor() { mArmor--; }
	float GetVelocityX() { return velX; }
	float GetVelocityY() { return velY; }

	sf::Vector2f getPosition() const;
	void setPosition(sf::Vector2f pos);

	void setActive(bool act) { active = act; };
	bool getActive() const { return active; };
	sf::IntRect BoundingBox() const;

	void Move();
	void Fire();
	void Death();
	void Reset();

	void Update(float delta, float mHeading);

	void Draw(sf::RenderWindow & window);

	void RemoveArmor() { mArmor--; };

	int getArmor() const { return mArmor; };

	void setArmor(int armor) { mArmor = armor; };
};

