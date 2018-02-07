#pragma once
#include <SFML\Graphics.hpp>

class Animated {
public:
	Animated();
	~Animated();

	void free();

	void render(sf::RenderWindow &window, int x, int y, sf::IntRect *sprite);

	int getWidth();
	int getHeight();

	sf::Texture *texture;

private:
	int mWidth;
	int mHeight;
};