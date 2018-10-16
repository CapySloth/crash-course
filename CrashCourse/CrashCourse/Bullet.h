#pragma once
#include <SFML/Graphics.hpp>

#include <vector>

class Bullet
{
	sf::IntRect mRect;
	sf::Color mColor;
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

	void SetLeft(int x) { mRect.left = x; }
	void SetRight(int x) { mRect.left = x - mRect.width; }
	void SetTop(int y) { mRect.top = y; }
	void SetBottom(int y) { mRect.top = y - mRect.height; }
	void SetWidth(int w) { mRect.width = w; }
	void SetHeight(int h) { mRect.height = h; }

	void SetActive(bool val) { active = val; }
	bool GetActive() { return active; }
	void Move();

	void SetColor(sf::Color color) { mColor = color; }
	void SetColor(sf::Uint8 r, sf::Uint8 g, sf::Uint8 b, sf::Uint8 a) { mColor.r = r; mColor.g = g; mColor.b = b; mColor.a = a; }

	void SetVelocity(float vx, float vy);
	void SetVelocity(sf::Vector2f mVelocity);

	float GetVelocityX();
	float GetVelocityY();

	sf::Vector2f GetVelocity();

	void Update(float delta);
	void Draw(sf::RenderWindow & window) const;



	void Reset();
	void CalculateTragectory(float delta, float mHeading);

	sf::IntRect BoundingBox() const;

private:
	static const int msDefaultWidth;
	static const int msDefaultHeight;

	static const sf::Color msDefaultColor;
	bool active;
};
