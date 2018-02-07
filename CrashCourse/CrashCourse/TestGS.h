#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "Trail.h"

class TestGS {
private:
	sf::RenderWindow window;
	sf::ContextSettings settings;

	bool isPlaying;
	bool mousePressed;

	Trail *trail;
public:
	TestGS();
	void execute();
	void update();
	void render();

	static const int SCREEN_WIDTH;
	static const int SCREEN_HEIGHT;
};
