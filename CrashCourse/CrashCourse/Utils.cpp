#include "Utils.h"
#include <stdlib.h>    
#include <time.h>
namespace RandHelpers
{
	void seedRandNumGenerator()
	{
		return srand(time(NULL));
	}
	void seedRandNumGenerator(int seed)
	{
		return srand(seed);
	}
	int genRandNumBetween(int lower, int upper)
	{
		return rand() % (upper - lower + 1) + lower;
	}
	//WHAT DO 3f
	sf::Vector2f genRandPoint(int x, int y, int w, int h) {
		sf::Vector2f point;
		point.x = genRandNumBetween(x, x + w);
		point.y = genRandNumBetween(y, y + h);
		return point;
	}
	sf::Vector2f genRandPoint(sf::IntRect rect) {
		sf::Vector2f point;
		point.x = genRandNumBetween(rect.left, rect.width);
		point.y = genRandNumBetween(rect.top, rect.height);
		return point;
	}
	sf::Color genRandColor() {
		sf::Color color;
		color.r = genRandNumBetween(0, 255);
		color.g = genRandNumBetween(0, 255);
		color.b = genRandNumBetween(0, 255);
		color.a = 255;
		return color;
	}
	sf::Color genRandBrightColor() {
		sf::Color color;
		color.r = genRandNumBetween(ceil(0.2126 * 255), 255);
		color.g = genRandNumBetween(ceil(0.7152 * 255), 255);
		color.b = genRandNumBetween(ceil(0.0722 * 255), 255);
		color.a = 255;
		return color;
	}
}
