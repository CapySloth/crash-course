#pragma once
#include <SFML\Graphics.hpp>
// header
namespace RandHelpers
{
	void seedRandNumGenerator();
	void seedRandNumGenerator(int seed);
	int genRandNumBetween(int lower, int upper);
	sf::Vector2f genRandPoint(int x, int y, int w, int h);
	sf::Vector2f genRandPoint(sf::IntRect);
	sf::Color genRandColor();
	sf::Color genRandBrightColor();
}

