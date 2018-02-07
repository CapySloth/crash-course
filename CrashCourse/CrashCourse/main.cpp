/*
 * Kanstantsin Arlouski 
 * Game Engineering - Final Project
 * Instructor: Kevin Forest
 * 01-16-2018
 */

#include "GameStateManager.h"
#include "InputManager.h"

#include "Game.h"
#include "HighScoreGS.h"
//#include "TestGS.h"
#include "ButtonTestGS.h"
#include "SplashGS.h"

#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>

int main(int argc, char** argv) {
	//std::cout << argv[0] << std::endl;
	
	//GameStateManager::getInstance().Push(HighScoreGS::getInstance());
	//GameStateManager::getInstance().Push(Game::getInstance());
	//-g 1 - f dice - d10 - r20.png - d 10 - r 20
	GameStateManager::getInstance().Push(SplashGS::getInstance());
	return GameStateManager::getInstance().Play();
	//TestGS game;
	//game.execute();
	return 0;
}
