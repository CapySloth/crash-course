#include <iostream>

#include "Game.h"

#include "InputManager.h"
#include "AssetManager.h"
#include "GameStateManager.h"

#include "NewHighScoreGS.h"
#include "HighScoreGS.h"

NewHighScoreGS::NewHighScoreGS()
	: mTitle("NEW HIGHSCORE", *FontManager::getInstance().getAsset("Assets/thunderstrike.ttf")),
	mScore("", *FontManager::getInstance().getAsset("Assets/thunderstrike.ttf")),
	mFirstLetter("_", *FontManager::getInstance().getAsset("Assets/thunderstrike.ttf")),
	mSecondLetter("_", *FontManager::getInstance().getAsset("Assets/thunderstrike.ttf")),
	mThirdLetter("_", *FontManager::getInstance().getAsset("Assets/thunderstrike.ttf")),
	mSubmit("Submit", *FontManager::getInstance().getAsset("Assets/thunderstrike.ttf"))
{
	mTitle.setPosition(240, 100);
	mTitle.setCharacterSize(24);
	mTitle.setColor(sf::Color::White);

	mScore.setFillColor(sf::Color(175, 0, 0, 255));
	mFirstLetter.setFillColor(sf::Color(240, 160, 0, 255));
	mSecondLetter.setFillColor(sf::Color(240, 160, 0, 255));
	mThirdLetter.setFillColor(sf::Color(240, 160, 0, 255));
	mSubmit.setFillColor(sf::Color::White);

	mScore.setOutlineColor(sf::Color(175, 0, 0, 255));
	mFirstLetter.setOutlineColor(sf::Color(240, 160, 0, 255));
	mSecondLetter.setOutlineColor(sf::Color(240, 160, 0, 255));
	mThirdLetter.setOutlineColor(sf::Color(240, 160, 0, 255));
	mSubmit.setOutlineColor(sf::Color::White);

	mScore.setPosition(340, 150);
	mFirstLetter.setPosition(300, 250);
	mSecondLetter.setPosition(350, 250);
	mThirdLetter.setPosition(400, 250);
	mSubmit.setPosition(300, 300);
}

NewHighScoreGS::~NewHighScoreGS()
{
}

void NewHighScoreGS::Update(float delta)
{
	if (InputManager::getInstance().wasKeyReleased(InputManager::GK_BACK_SPACE)) {
		if (mThirdLetter.getString() != "_") {
			mThirdLetter.setString("_");
		}
		else if (mSecondLetter.getString() != "_") {
			mSecondLetter.setString("_");
		}
		else if (mFirstLetter.getString() != "_") {
			mFirstLetter.setString("_");
		}
	}
	//Mouse Input
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		// get the local mouse position (relative to a window)
		sf::Vector2f localPosition = InputManager::getInstance().getMousePos(); // window is a sf::Window
		if (NewHighScoreGS::getInstance().getSubmit().getGlobalBounds().contains(localPosition.x, localPosition.y)) {
			if (mThirdLetter.getString() != "_") {
				std::string name;
				std::string score;

				name = mFirstLetter.getString() + mSecondLetter.getString() + mThirdLetter.getString();
				score = mScore.getString();
				HighScoreGS::getInstance().setHighScore(name, std::stoi(score));
				HighScoreGS::getInstance().saveData();
				mFirstLetter.setString("_");
				mSecondLetter.setString("_");
				mThirdLetter.setString("_");
				GameStateManager::getInstance().Push(HighScoreGS::getInstance());
			}
		}
	}


}

void NewHighScoreGS::Draw(sf::RenderWindow & window)
{
	window.draw(mTitle);
	window.draw(mScore);
	window.draw(mFirstLetter);
	window.draw(mSecondLetter);
	window.draw(mThirdLetter);
	window.draw(mSubmit);
}

void NewHighScoreGS::Init()
{
}

void NewHighScoreGS::Deinit()
{
}

bool NewHighScoreGS::IsInit()
{
	return false;
}
