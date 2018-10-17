#pragma once
#include <SFML\Audio\SoundBuffer.hpp>
#include <SFML\Audio\Music.hpp>
#include <SFML\Graphics.hpp>

#include "GameState.h"
#include "Entity.h"
#include "Aircraft.h"
#include "Player.h"
#include "Cloud.h"
#include "Animated.h"


class Game :
	public AGameState
{
	int					mScreenWidth;
	int					mScreenHeight;
	Entity*				mHeader, *mFooter;
	bool				mShouldQuit;
	int					eCounter = 0; //enemy Counter

	sf::ContextSettings settings;

	sf::Color black = { 0, 0, 0, 255 };
	sf::Color orange = { 255, 140, 0, 255 };
	sf::Color white = { 255, 255, 255, 255 };
	
	sf::Sound explosionSound;
	sf::Sound hitHurtSound;

	sf::SoundBuffer *explosion = nullptr;
	sf::SoundBuffer *hitHurt = nullptr;

	sf::Texture *mCloudTexture = nullptr;
	std::vector<Cloud> mClouds1;
	std::vector<Cloud> mClouds2;
	std::vector<Cloud> mClouds3;
	std::vector<Aircraft*> mEnemies;

	sf::Texture *mPlayerTexture = nullptr;
	Player *mShip;

	int dirX;
	int dirY;

	bool media;
	//Check if recently hit
	bool recentHit = false;

	#pragma region Explosion Code
	bool blowThatShitUp = false;

	int frame = 0;
	int const static animation_frames = 8;
	
	sf::IntRect mSprites[animation_frames];
	sf::Texture *mSpriteSheet = nullptr;;
	Animated mExplosion;

	int expPosX;
	int expPosY;
public:
	static Game &getInstance() {
		static Game instance;
		return instance;
	}

	~Game();

	void Restart();
	void reduceLife() { playerLives--; }
	void increasePoints() { playerPoints += 100; }

	int getPlayerPoints() {
		return playerPoints;
	}
	int getPlayerLives() {
		return playerLives;
	}
	void setPlayerPoints(int points) {
		playerPoints = points;
	}
	void setPlayerLives(int lives) {
		playerLives = lives;
	}
private:
	Game();
	Game(Game const &);
	Game &operator=(Game const &);

	// Inherited via AGameState
	virtual void Update(float delta) override;
	virtual void Draw(sf::RenderWindow & window) override;

	bool LoadMedia();
	bool LoadClouds();
	bool LoadShip();

	void ProcessEvents();

	virtual void Init() override;
	virtual void Deinit() override;
	virtual bool IsInit() override;
	
	void OnQuit();
	void Shutdown();
	void Spawn();
	void Respawn(sf::Vector2f spawnCoordinates, std::vector<Aircraft*>::iterator it);
	void DeSpawn();
	void Reuse();

private:
	//Enemy timer
	unsigned int eTimer;

	sf::Text mLivesText;
	sf::Text mPointsText;

	int playerPoints;
	int playerLives;
};

