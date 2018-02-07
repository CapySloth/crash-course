#pragma once
#include "GameState.h"
#include <SFML\Audio\Music.hpp>
#include <SFML\Graphics.hpp>

class MainMenuGS :
	public AGameState
{
public:
	static MainMenuGS &getInstance() {
		static MainMenuGS instance;
		return instance;
	}
private:
	MainMenuGS();
	MainMenuGS(MainMenuGS const &);
	MainMenuGS &operator=(MainMenuGS const &);
public:
	~MainMenuGS();
	sf::Music backgroundMusic;
	// Inherited via AGameState
	virtual void Update(float delta) override;
	virtual void Draw(sf::RenderWindow & window) override;
	virtual void Init() override;
	virtual void Deinit() override;
	virtual bool IsInit() override;
	
	virtual sf::Text &getTitleText() { return mTitle; }
	virtual sf::Text &getCreateNewGame() { return mCreateNewGame; }
	virtual sf::Text &getLoadLastGame() { return mLoadLastGame; }
	virtual sf::Text &getViewHighScores() { return mViewHighScores; }
	virtual sf::Text &getQuitText() { return mQuit; }

private:
	sf::Text mTitle;
	sf::Text mLoadLastGame;
	sf::Text mCreateNewGame;
	sf::Text mViewHighScores;
	sf::Text mQuit;
};

