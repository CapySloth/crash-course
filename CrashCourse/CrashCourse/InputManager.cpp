#include <iostream>

#include "InputManager.h"
bool InputManager::isKeyUp(GameKey gk) {
	return !mCurrentKeyState[mKeyMap[gk]];
}

bool InputManager::isKeyDown(GameKey gk) {
	return !isKeyUp(gk);
}

bool InputManager::wasKeyPressed(GameKey gk) {
	return !mPreviousKeyState[mKeyMap[gk]] && mCurrentKeyState[mKeyMap[gk]];
}

bool InputManager::wasKeyReleased(GameKey gk) {
	// Down on prev frame && up on current frame
	return mPreviousKeyState[mKeyMap[gk]] && !mCurrentKeyState[mKeyMap[gk]];
}

void InputManager::Update(sf::Window &window) {
	//The old current state is now the new previous state
	mPreviousKeyState.swap(mCurrentKeyState);
	//Iterate through each game key and get the corresponding SFML Key code
	// that is mapped to that game key.
	for (int k = 0; k < GK_COUNT; ++k) {
		sf::Keyboard::Key key = mKeyMap[static_cast<GameKey>(k)];
		mCurrentKeyState[key] = sf::Keyboard::isKeyPressed(key);
	}
	//Set the mouse position relative to the window
	mMousePos.x = (float)sf::Mouse::getPosition(window).x;
	mMousePos.y = (float)sf::Mouse::getPosition(window).y;
	if (mMousePos.x < 0 || mMousePos.x >= window.getSize().x || mMousePos.y < 0 || mMousePos.y >= window.getSize().y) {
		mMousePos.x = -1.0f;
		mMousePos.y = -1.0f;
	}
}

sf::Vector2f InputManager::getMousePos()
{
	return mMousePos;
}