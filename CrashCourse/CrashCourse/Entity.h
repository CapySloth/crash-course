#ifndef PLAYER_H_
#define PLAYER_H_

#include <SFML\Graphics.hpp>
#include <vector>

class Entity
{
	sf::IntRect mRect;
	sf::Color mColor;

public:

	Entity(float x, float y, float w, float h, sf::Color color);

	int Width() const { return mRect.width; }
	int Height() const { return mRect.height; }

	int Left() const { return mRect.left; }
	int Top() const { return mRect.top; }
	int Right() const { return mRect.left + mRect.width; }
	int Bottom() const { return mRect.top + mRect.height; }

	sf::Vector2f Center() const;

	void SetLeft(int x) { mRect.left = x; }
	void SetRight(int x) { mRect.left = x - mRect.width; }
	void SetTop(int y) { mRect.top = y; }
	void SetBottom(int y) { mRect.top = y - mRect.height; }
	void SetWidth(int w) { mRect.width = w; }
	void SetHeight(int h) { mRect.height = h; }

	void SetCenter(int x, int y);

	void Move(sf::Vector2f vel);

	void SetColor(sf::Color color) { mColor = color; }
	void SetColor(sf::Uint8 r, sf::Uint8 g, sf::Uint8 b, sf::Uint8 a) { mColor.r = r; mColor.g = g; mColor.b = b; mColor.a = a; }

	void Update(const sf::Uint8* keys);
	void Draw(sf::RenderWindow & window) const;

	bool CheckCollision(sf::IntRect a, sf::IntRect b);
	sf::IntRect BoundingBox() const;
private:
	static const int msDefaultWidth;
	static const int msDefaultHeight;

	static const sf::Color msDefaultColor;
};

#endif
