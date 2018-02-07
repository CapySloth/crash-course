#pragma once
#include <vector>

class AGameState;
namespace sf {
	class RenderWindow;
}

class GameStateManager
{
private:
	std::vector<AGameState *> mStates;
	//static GameStateManager *theInstance;
public:
	static GameStateManager &getInstance() {
	/*
		if (theInstance == nullptr) {
			theInstance = new GameStateManager();
		}
		return *theInstance;
	*/
		static GameStateManager instance;
		return instance;
	}

private:
	GameStateManager();
	GameStateManager(GameStateManager const &);
	GameStateManager &operator=(GameStateManager const &);


public:
	~GameStateManager();
	//Main program loop, run after any setup is done in main.
	int Play(); 
	void Update(float delta);
	void Draw(sf::RenderWindow &window);
	//GameState stack management
	void Pop();
	void Push(AGameState &newState);
	void Change(AGameState &newState);
	void PopAllThenPush(AGameState &newState);

	//Run management
	bool running = true;
};

