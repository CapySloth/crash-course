/*
 * Kanstantsin Arlouski 
 * Game Engineering - Final Project
 * Instructor: Kevin Forest
 * 01-16-2018
 */

#include <SFML/Graphics.hpp>

#include "GameStateManager.h"
#include "SplashGS.h"

int main(int argc, char** argv) {
	GameStateManager::getInstance().Push(SplashGS::getInstance());
	return GameStateManager::getInstance().Play();
	return 0;
}
