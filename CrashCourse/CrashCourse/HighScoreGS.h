#pragma once
#include "GameState.h"

#include <iostream>
#include <SFML\Graphics.hpp>

class HighScoreGS :
	public AGameState
{
public:
	static HighScoreGS &getInstance() {
		static HighScoreGS instance;
		return instance;
	}
private:
	HighScoreGS();
	HighScoreGS(HighScoreGS const &);
	HighScoreGS &operator=(HighScoreGS const &);
public:
	~HighScoreGS();

	// Inherited via AGameState
	virtual void Update(float delta) override;
	virtual void Draw(sf::RenderWindow & window) override;
	virtual void Init() override;
	virtual void Deinit() override;
	virtual bool IsInit() override;

	template <typename A, typename B>
	std::multimap<B, A> flip_map(std::map<A, B> & src) {

		std::multimap<B, A> dst;

		for (std::map<A, B>::const_iterator it = src.begin(); it != src.end(); ++it)
			dst.insert(std::pair<B, A>(it->second, it->first));

		return dst;
	}

	void prepareHighScoreDisplay() {
		int y = 0;
		int b = 0;
		std::multimap<int, std::string> reverseTest = flip_map(highScores);

		//Reverse map used, because map is sorted by key (Ordered high scores)
		for (std::multimap<int, std::string>::const_reverse_iterator it = reverseTest.rbegin(); it != reverseTest.rend(); ++it) {
			std::cout << it->first << " " << it->second << std::endl;
			std::string k = it->second;
			int v = it->first;
			b++;
			highScoresDisplay[y].setString(std::to_string(b) + ". " + k + "\t.\t.\t.\t.\t.\t.\t.\t.\t.\t.\t" + std::to_string(v));
			y++;
		}
	}

	void setHighScore(std::string name, int highscore) {
		auto it = highScores.find(name);
		if (it != highScores.end()) {
			//Name already exists, overwrite highscore, if the score is higher
			if (highScores[name] > highscore) {
				highScores[name] = highscore;
			} 
		}
		else {
			highScores[name] = highscore;
		}
	}
	bool loadData();
	bool saveData();

	std::map<std::string, int> *getHighScores() {
		return &highScores;
	}

	virtual sf::Text &getBack() { return mBack; }
private:
	std::map<std::string, int> highScores;
	//Only display top 10 scores + most recent
	sf::Text highScoresDisplay[10];

	sf::Text mTitle;
	sf::Text mBack;
};

