#include "Game.h"
#include "AssetManager.h"
#include "Utils.h"
#include <iostream>

int const MAXENEMIES = 15;
int const arm = 2;

void Game::ProcessEvents()
{
	if (eTimer % 129 == 0) {
		Spawn();
	}
}

void Game::OnQuit()
{
	std::cout << "Application was told to quit" << std::endl;
	mShouldQuit = true;
}

void Game::Shutdown()
{
	DeSpawn();

	delete mHeader;
	mHeader = nullptr;
	delete mFooter;
	mFooter = nullptr;
}

//Spawn Based of time
void Game::Spawn() {
	static sf::Texture *texture = nullptr;
	
	if (TextureManager::getInstance().loadAsset("Assets/enemy1.png")) {
		texture = TextureManager::getInstance().getAsset("Assets/enemy1.png");
	}

	if (eCounter <= MAXENEMIES) {
		int decision = rand() % 4;
		Aircraft *enemy;
		switch (decision) {
		case 0://Spawn Up
			enemy = new Aircraft(arm, sf::Vector2f(0.0f, 0.0f), 0.0f, sf::Vector2f(RandHelpers::genRandNumBetween(20, mScreenWidth - 20),RandHelpers::genRandNumBetween(-30, 0)), texture);
			mEnemies.push_back(enemy);
			eCounter++;
			break;
		case 1:
			//Spawn somewhere to the Right 
			enemy = new Aircraft(arm, sf::Vector2f(0.0f, 0.0f), 0.0f, sf::Vector2f(RandHelpers::genRandNumBetween(mScreenWidth, mScreenWidth + 20), RandHelpers::genRandNumBetween(0, mScreenHeight)), texture);
			mEnemies.push_back(enemy);
			eCounter++;
			break;
		case 2:
			//Spawn to Left or Up
			enemy = new Aircraft(arm, sf::Vector2f(0.0f, 0.0f), 0.0f, sf::Vector2f(RandHelpers::genRandNumBetween(-20, 0), RandHelpers::genRandNumBetween(0, mScreenHeight)), texture);
			mEnemies.push_back(enemy);
			eCounter++;
			break;
		case 3://Spawn At the bottom
			enemy = new Aircraft(arm, sf::Vector2f(0.0f, 0.0f), 0.0f, sf::Vector2f(RandHelpers::genRandNumBetween(0, mScreenWidth + 20), RandHelpers::genRandNumBetween(mScreenHeight, mScreenHeight + 20)), texture);
			mEnemies.push_back(enemy);
			eCounter++;
			break;
		}
	}
	else {
		Reuse();
	}
	//sf::Delay(5);
}

void Game::Reuse() {
	for (std::vector<Aircraft*>::iterator it = mEnemies.begin(); it != mEnemies.end(); it++) {
		if (!(*it)->getActive()) {
			int decision = rand() % 4;
			switch (decision) {
			case 0://Spawn Up
				Respawn(sf::Vector2f(RandHelpers::genRandNumBetween(mScreenWidth, mScreenWidth + 100), RandHelpers::genRandNumBetween(mScreenHeight, mScreenHeight + 100)),it);
				break;
			case 1:
				//Spawn somewhere to the Right 
				Respawn(sf::Vector2f(RandHelpers::genRandNumBetween(mScreenWidth, mScreenWidth + 20), RandHelpers::genRandNumBetween(0, mScreenHeight)), it);
				break;
			case 2:
				//Spawn to Left or Up
				Respawn(sf::Vector2f(RandHelpers::genRandNumBetween(-20, 0), RandHelpers::genRandNumBetween(0, mScreenHeight)), it);
				break;
			case 3://Spawn At the bottom
				Respawn(sf::Vector2f(RandHelpers::genRandNumBetween(0, mScreenWidth + 20), RandHelpers::genRandNumBetween(mScreenHeight, mScreenHeight + 20)), it);
				break;
			}
		}
	}
}

void Game::Respawn(sf::Vector2f spawnCoordinates, std::vector<Aircraft*>::iterator it) {
	(*it)->setPosition(spawnCoordinates);
	(*it)->setArmor(arm);
	(*it)->setActive(true);
	eCounter++;
}

