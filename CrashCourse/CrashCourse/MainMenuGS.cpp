#include "Game.h"
#include "InputManager.h"
#include "AssetManager.h"
#include "GameStateManager.h"

#include "MainMenuGS.h"
#include "HighScoreGS.h"

#include <iostream>

MainMenuGS::MainMenuGS()
	: mLoadLastGame("Continue", *FontManager::getInstance().getAsset("Assets/thunderstrike.ttf")),
		mCreateNewGame("New Game", *FontManager::getInstance().getAsset("Assets/thunderstrike.ttf")),
			mViewHighScores("High Scores", *FontManager::getInstance().getAsset("Assets/thunderstrike.ttf")),
				mQuit("Quit", *FontManager::getInstance().getAsset("Assets/thunderstrike.ttf")),
					mTitle("CRASH COURSE", *FontManager::getInstance().getAsset("Assets/thunderstrike.ttf"))
{
	mTitle.setPosition(333, 100);
	mTitle.setCharacterSize(30);
	mTitle.setOutlineColor(sf::Color(255, 140, 0, 255));
	mTitle.setFillColor(sf::Color(255, 140, 0, 255));


	mLoadLastGame.setFillColor(sf::Color::White);
	mCreateNewGame.setFillColor(sf::Color::White);
	mViewHighScores.setFillColor(sf::Color::White);
	mTitle.setFillColor(sf::Color::White);

	mLoadLastGame.setOutlineColor(sf::Color::White);
	mCreateNewGame.setOutlineColor(sf::Color::White);
	mViewHighScores.setOutlineColor(sf::Color::White);
	mQuit.setOutlineColor(sf::Color::White);

	mLoadLastGame.setPosition(333, 150);
	mCreateNewGame.setPosition(333, 200);
	mViewHighScores.setPosition(333, 250);
	mQuit.setPosition(333, 300);
}

MainMenuGS::~MainMenuGS()
{
}

void MainMenuGS::Update(float delta)
{
	//Mouse Input
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		std::cout << "Pressed" << std::endl;
		// get the local mouse position (relative to a window)
		sf::Vector2f localPosition = InputManager::getInstance().getMousePos(); // window is a sf::Window
		if (MainMenuGS::getInstance().getCreateNewGame().getGlobalBounds().contains(localPosition.x, localPosition.y)) {
			Game::getInstance().Restart();
			GameStateManager::getInstance().Push(Game::getInstance());
		}
		else if (MainMenuGS::getInstance().getLoadLastGame().getGlobalBounds().contains(localPosition.x, localPosition.y)) {
			HighScoreGS::getInstance().loadData();
			int lives = Game::getInstance().getPlayerLives();
			std::cout << lives << std::endl;
			if (lives > 0) {
				GameStateManager::getInstance().Change(Game::getInstance());
			} else {
				Game::getInstance().Restart();
				GameStateManager::getInstance().Change(Game::getInstance());
			}
		}
		else if (MainMenuGS::getInstance().getViewHighScores().getGlobalBounds().contains(localPosition.x, localPosition.y)) {
			GameStateManager::getInstance().Change(HighScoreGS::getInstance());
		}
		else if (MainMenuGS::getInstance().getQuitText().getGlobalBounds().contains(localPosition.x, localPosition.y)) {
			//I am very lazy
			HighScoreGS::getInstance().saveData();
			GameStateManager::getInstance().running = false;
		}
	}
}

void MainMenuGS::Draw(sf::RenderWindow & window)
{
	window.draw(mTitle);
	window.draw(mLoadLastGame);
	window.draw(mCreateNewGame);
	window.draw(mViewHighScores);
	window.draw(mQuit);
	
}

void MainMenuGS::Init()
{
	if (!backgroundMusic.openFromFile("Assets/To_the_Next_Destination.wav")) {

	}
	backgroundMusic.setVolume(20);
	backgroundMusic.play();
}

void MainMenuGS::Deinit()
{
}

bool MainMenuGS::IsInit()
{
	return false;
}
