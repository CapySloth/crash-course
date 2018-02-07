#pragma once
#include <SFML/Window.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <map>
namespace sf {
	class RenderWindow;
}

class InputManager
{
public:
	static InputManager &getInstance() {
		static InputManager instance;
		return instance;
	}

	sf::Vector2f getMousePos();

	//Lazy way to do initial mapping, but note that it
	// does prevent multiple keyboard keys mapping to the
	// same game key.
	enum GameKey {
		GK_ENTER,
		GK_ESCAPE,
		GK_UP,
		GK_UP_ALT,
		GK_LEFT,
		GK_RIGHT,
		GK_SPACE,
		GK_BACK_SPACE,
		GK_BACK,
		GK_COUNT
	};

private:
	InputManager() {
		//Set default key mappings
		mKeyMap[GK_ENTER] = sf::Keyboard::Return,
			mKeyMap[GK_ESCAPE] = sf::Keyboard::Escape,
			mKeyMap[GK_UP] = sf::Keyboard::Up,
			mKeyMap[GK_UP_ALT] = sf::Keyboard::W,
			mKeyMap[GK_LEFT] = sf::Keyboard::Left,
			mKeyMap[GK_RIGHT] = sf::Keyboard::Right,
			mKeyMap[GK_SPACE] = sf::Keyboard::Space,
			mKeyMap[GK_BACK_SPACE] = sf::Keyboard::BackSpace,
			mKeyMap[GK_BACK] = sf::Keyboard::Num5,
		mKeyMap[GK_COUNT] = sf::Keyboard::KeyCount;
	}
	InputManager(InputManager const &); //No def
	InputManager &operator=(InputManager const &); //No def

public:
	bool isKeyUp(GameKey gk);
	bool isKeyDown(GameKey gk);
	bool wasKeyPressed(GameKey gk);
	bool wasKeyReleased(GameKey gk);
	void Update(sf::Window &window);
private:
	std::map<GameKey, sf::Keyboard::Key> mKeyMap;
	std::map<sf::Keyboard::Key, bool> mCurrentKeyState;
	std::map<sf::Keyboard::Key, bool> mPreviousKeyState;
	sf::Vector2f mMousePos;
};

