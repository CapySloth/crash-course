#pragma once
#include "GameState.h"

#include <SFML\Graphics.hpp>

class NewHighScoreGS :
	public AGameState
{
public:
	static NewHighScoreGS &getInstance() {
		static NewHighScoreGS instance;
		return instance;
	}
private:
	NewHighScoreGS();
	NewHighScoreGS(NewHighScoreGS const &);
	NewHighScoreGS &operator=(NewHighScoreGS const &);
public:
	~NewHighScoreGS();

	// Inherited via AGameState
	virtual void Update(float delta) override;
	virtual void Draw(sf::RenderWindow & window) override;
	virtual void Init() override;
	virtual void Deinit() override;
	virtual bool IsInit() override;
	void Reset();

	virtual sf::Text &getScore() { return mScore; }
	virtual sf::Text &getFirstLetter() { return mFirstLetter; }
	virtual sf::Text &getSecondLetter() { return mSecondLetter; }
	virtual sf::Text &getThirdLetter() { return mThirdLetter; }
	virtual sf::Text &getSubmit() { return mSubmit; }
private:
	sf::Text mTitle;
	sf::Text mScore;
	sf::Text mFirstLetter;
	sf::Text mSecondLetter;
	sf::Text mThirdLetter;
	sf::Text mSubmit;
};

