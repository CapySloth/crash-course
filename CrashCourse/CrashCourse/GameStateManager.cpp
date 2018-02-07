#include "GameStateManager.h"
#include "GameState.h"
#include "InputManager.h"

#include "MainMenuGS.h"
#include "NewHighScoreGS.h"

#include <SFML/Graphics.hpp>

#include <iostream>
//GameStateManager *GameStateManager::theInstance = nullptr;

GameStateManager::GameStateManager()
{
	static int count = 0;
	++count;
	std::cout << "Count: " << count << std::endl;
}


GameStateManager::~GameStateManager()
{
}

int GameStateManager::Play()
{
	
	//Create window
	int const WINDOW_WIDTH = 700;
	int const WINDOW_HEIGHT = 700;
	sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Game State Management");
	InputManager &input = InputManager::getInstance();

	

	//Clock management
	bool drawRequested = false;
	int updatesSinceDraw = 0;
	int const FRAME_SKIP = 5;
	sf::Clock clock;
	float const TGT_FPS = 30.0f;
	float const TGT_DELTA = 1.0f / TGT_FPS;
	sf::Time deltaTime = sf::seconds(TGT_DELTA);
	sf::Time clockTime = clock.getElapsedTime();
	sf::Time gameTime = clockTime;

	//Main Game Loop
	while (running) {
		//Reset stateful variables
		drawRequested = false;
		updatesSinceDraw = 0;
		//Event handling
		sf::Event ev;
		while (window.pollEvent(ev)) {
			switch (ev.type) {
			case sf::Event::TextEntered:
				if (mStates.back() == &NewHighScoreGS::getInstance()) {
					if (ev.text.unicode < 128) {
						//Could not find a way to properly filter out n
						if (ev.text.unicode != '\b') {
							if (NewHighScoreGS::getInstance().getFirstLetter().getString() == "_") {
								NewHighScoreGS::getInstance().getFirstLetter().setString(ev.text.unicode);
								break;
							}
							else if (NewHighScoreGS::getInstance().getSecondLetter().getString() == "_") {
								NewHighScoreGS::getInstance().getSecondLetter().setString(ev.text.unicode);
								break;
							}
							else if (NewHighScoreGS::getInstance().getThirdLetter().getString() == "_") {
								NewHighScoreGS::getInstance().getThirdLetter().setString(ev.text.unicode);
								break;
							}
						}	
					}
					
				}
				break;
			case sf::Event::Closed:
				running = false;
				break;
			case sf::Event::MouseButtonReleased:
				break;
			case sf::Event::KeyReleased:
				break;
			}
		} //End event handling loop
		if (!mStates.empty()) {
			if (mStates.back() == &MainMenuGS::getInstance()) {
				//Mapped Key Input
				if (input.wasKeyReleased(InputManager::GK_ESCAPE)) {
					std::cout << "Quit" << std::endl;
					//running = false;
				}
			}
		}
		  //Game update (happens every TGT_DELTA seconds of gametime)
		while (updatesSinceDraw++ < FRAME_SKIP && (clockTime = clock.getElapsedTime()) > gameTime) {
			//Update game time and request a draw
			gameTime += deltaTime;
			drawRequested = true;

			//Update the input manager
			input.Update(window);
			//Update all entities in the game, remember that they should use TGT_DELTA
			Update(TGT_DELTA);
		} //End game update loop

		  //Draw to screen
		if (drawRequested) {

			Draw(window);

		} //End drawing code
	}

	return 0;
}

void GameStateManager::Update(float delta)
{
	//Update the top state in the stack
	if (!mStates.empty()) {
		mStates.back()->Update(delta);
	}
}

void GameStateManager::Draw(sf::RenderWindow & window)
{
	//Clear the window
	window.clear(sf::Color::Black);
	//Render drawables
	//TODO: Add opaque handling code.
	// Draw from the first Opaque state found starting from the top of the
	// stack and moving down, then draw that state and all states above it.
	if (!mStates.empty()) {
		mStates.back()->Draw(window);
	}

	//Show the window
	window.display();
}

void GameStateManager::Pop()
{
	if(!mStates.empty()) {
		mStates.back()->Deinit();
		mStates.pop_back();
	}
	if (!mStates.empty()) {
		mStates.back()->Resume();
	}
}

void GameStateManager::Push(AGameState & newState)
{
	if (!mStates.empty()) {
		mStates.back()->Pause();
	}
	newState.Init();
	//Call newState.Resume() iff newState.Init() doesn't
	// explicitly put the state in the non-paused state
	mStates.push_back(&newState);
}

void GameStateManager::Change(AGameState & newState)
{
	Pop();
	Push(newState);
}

void GameStateManager::PopAllThenPush(AGameState & newState)
{
	while (!mStates.empty()) {
		Pop();
	}
	Push(newState);
}
