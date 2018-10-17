#pragma once
#include <SFML/Graphics.hpp>

#include <vector>

class Bullet
{
	sf::IntRect mRect;
	sf::Color mColor;
	sf::Vector2f mPosition;
	float mPosX, mPosY;
	sf::Vector2f mVelocity;
public:
	Bullet();

	int Width() const { return mRect.width; }
	int Height() const { return mRect.height; }

	int Left() const { return mRect.left; }
	int Top() const { return mRect.top; }
	int Right() const { return mRect.left + mRect.width; }
	int Bottom() const { return mRect.top + mRect.height; }

	void setLeft(int x) { mRect.left = x; }
	void setRight(int x) { mRect.left = x - mRect.width; }
	void setTop(int y) { mRect.top = y; }
	void setBottom(int y) { mRect.top = y - mRect.height; }
	void setWidth(int w) { mRect.width = w; }
	void setHeight(int h) { mRect.height = h; }

	void setActive(bool val) { active = val; }
	bool getActive() { return active; }
	void Move();

	void setColor(sf::Color color) { mColor = color; }
	void setColor(sf::Uint8 r, sf::Uint8 g, sf::Uint8 b, sf::Uint8 a) { mColor.r = r; mColor.g = g; mColor.b = b; mColor.a = a; }

	void setVelocity(sf::Vector2f mVelocity);

	sf::Vector2f getVelocity() { return mVelocity; }
	sf::IntRect getHitBox() { return mRect; }

	void Update(float delta);
	void Draw(sf::RenderWindow & window) const;

	void Reset();
	void CalculateTragectory(float delta, float mHeading);

private:
	static const int msDefaultWidth;
	static const int msDefaultHeight;

	static const sf::Color msDefaultColor;
	bool active;
};
