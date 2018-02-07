#include "InputManager.h"
#include "AssetManager.h"
#include "GameStateManager.h"

#include "SplashGS.h"
#include "MainMenuGS.h"

#include <iostream>

SplashGS::SplashGS()
	: mTitle("Made By CapySloth", *FontManager::getInstance().getAsset("Assets/thunderstrike.ttf")),
	mDesclaimer("Press Space", *FontManager::getInstance().getAsset("Assets/thunderstrike.ttf")),
	mSplashWoot(sf::Vector2f(250.0f, 200.0f))
{
	mTitle.setPosition(160, 100);
	mTitle.setCharacterSize(30);
	mTitle.setOutlineColor(sf::Color(255, 255, 255, 255));
	mTitle.setFillColor(sf::Color(255, 255, 255, 255));

	mDesclaimer.setPosition(230, 500);
	mDesclaimer.setCharacterSize(30);
	mDesclaimer.setOutlineColor(sf::Color(255, 140, 0, 255));
	mDesclaimer.setFillColor(sf::Color(255, 140, 0, 255));

	if (TextureManager::getInstance().loadAsset("Assets/CapySlothLogo.png")) {
		mSplashWoot.setTexture(TextureManager::getInstance().getAsset("Assets/CapySlothLogo.png"));
	}
	mSplashWoot.setPosition(220, 250);
}

SplashGS::~SplashGS()
{
}

void SplashGS::Update(float delta)
{
	if (InputManager::getInstance().wasKeyReleased(InputManager::GK_SPACE)) {
		GameStateManager::getInstance().Change(MainMenuGS::getInstance());
	}
}

void SplashGS::Draw(sf::RenderWindow & window)
{
	window.draw(mTitle);
	window.draw(mSplashWoot);
	window.draw(mDesclaimer);

}

void SplashGS::Init()
{

}

void SplashGS::Deinit()
{
}

bool SplashGS::IsInit()
{
	return false;
}
