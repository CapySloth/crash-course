#include "Game.h"
#include "Cloud.h"
#include "InputManager.h"
#include "AssetManager.h"
#include "GameStateManager.h"

#include "NewHighScoreGS.h"
#include "MainMenuGS.h"
#include "HighScoreGS.h"

#include "tinyxml2.h"
#include <iostream>

Game::Game()
	: mScreenWidth(700)
	, mScreenHeight(700)
	, mLivesText("LIVES | 3", *FontManager::getInstance().getAsset("Assets/thunderstrike.ttf"))
	, mPointsText("SCORE | 0", *FontManager::getInstance().getAsset("Assets/thunderstrike.ttf"))
	, trail(new Trail())
	, playerLives(3)
	, playerPoints(0)

{
	mPointsText.setCharacterSize(24);
	mLivesText.setCharacterSize(24);

	mLivesText.setFillColor(black);
	mPointsText.setFillColor(black);

	mLivesText.setOutlineColor(sf::Color::Black);
	mPointsText.setOutlineColor(sf::Color::Black);
	
	mLivesText.setPosition(10, 5);
	mPointsText.setPosition(333, 5);
}

Game::~Game()
{
	WriteGameSetup();
}

void Game::Update(float delta)
{
if (InputManager::getInstance().wasKeyReleased(InputManager::GK_ESCAPE)) {
	GameStateManager::getInstance().Change(MainMenuGS::getInstance());
}

ProcessEvents();
#pragma region Cloud Updates
	for (int i = 0; i < mClouds3.size(); i++) {
		mClouds3[i].Update(delta);
		mClouds3[i].CalculateTragectory(delta, mShip->getHeading());
	}
	for (int i = 0; i < mClouds2.size(); i++) {
		mClouds2[i].Update(delta);
		mClouds2[i].CalculateTragectory(delta, mShip->getHeading());
	}
	for (int i = 0; i < mClouds1.size(); i++) {
		mClouds1[i].Update(delta);
		mClouds1[i].CalculateTragectory(delta, mShip->getHeading());
	}

#pragma endregion

#pragma region Player Ship Updates
	if (mShip != nullptr) {
		mShip->Update(delta);
	}
	//Iterate through Bullets/Aircraft to see if any collision occured
	for (std::vector<Aircraft*>::iterator it = mEnemies.begin(); it != mEnemies.end(); it++) {
		for (std::vector<Bullet*>::iterator bit = mShip->bullets.begin(); bit != mShip->bullets.end(); bit++) {
			if ((*it)->getActive()) {
				if ((*bit)->BoundingBox().intersects((*it)->BoundingBox())) {
					std::cout << (*it)->BoundingBox().left << std::endl;
					std::cout << (*bit)->BoundingBox().left << std::endl;
					//Stop piercing bullets
					(*bit)->Reset();
					hitHurtSound.play();
					(*it)->RemoveArmor();
					if ((*it)->getArmor() <= 0) {
						expPosX = (*it)->BoundingBox().left + (*it)->BoundingBox().width;
						expPosY = (*it)->BoundingBox().top + (*it)->BoundingBox().height;
						blowThatShitUp = true;
						increasePoints();
						mPointsText.setString("SCORE | " + std::to_string(getPlayerPoints()));
						explosionSound.play();
						(*it)->Reset();
					}
				}
			}
		}
		if ((*it)->getActive()) {
			if (mShip->BoundingBox().intersects((*it)->BoundingBox())) {
				(*it)->Reset();
				std::cout << mShip->BoundingBox().left << std::endl;
				std::cout << (*it)->BoundingBox().left << std::endl;
				expPosX = 350;
				expPosY = 350;
				blowThatShitUp = true;
				//Player Lose Life/Game Over
				for (std::vector<Aircraft*>::iterator it = mEnemies.begin(); it != mEnemies.end(); it++) {
					(*it)->Reset();
				}
				for (std::vector<Bullet*>::iterator bit = mShip->bullets.begin(); bit != mShip->bullets.end(); bit++) {
					(*bit)->Reset();
				}
				reduceLife();
				hitHurtSound.play();
				explosionSound.play();
				if (getPlayerLives() == 0) {
					//CLEAN UP, GAME OVER
					// TO DO
					//Shutdown();
					NewHighScoreGS::getInstance().getScore().setString(std::to_string(getPlayerPoints()));
					GameStateManager::getInstance().Change(NewHighScoreGS::getInstance());
				}
				mLivesText.setString("LIVES | " + std::to_string(getPlayerLives()));
			}
		}
		(*it)->Update(delta, mShip->getHeading());
	}
}

void Game::Draw(sf::RenderWindow & window)
{
	window.clear(sf::Color(0, 175, 255, 255));

	// clear the screen
	double centerx = window.getSize().x / 2;
	double centery = window.getSize().y / 2;


	//Layer 1
	for (int i = 0; i < mClouds3.size(); i++) {
		mClouds3[i].Draw(window);
	}
	//Layer 2
	for (int i = 0; i < mClouds2.size(); i++) {
		mClouds2[i].Draw(window);
	}
	//Layer 3
	if (mShip != nullptr) {
		mShip->Draw(window);
		//window.draw(*trail);
	}

	for (std::vector<Aircraft*>::iterator it = mEnemies.begin(); it != mEnemies.end(); it++) {
		(*it)->Draw(window);
	}

	//Explosions
	if (blowThatShitUp) {
		sf::IntRect *current = &mSprites[frame / 8];
		mExplosion.render(window, expPosX, expPosY, current);

		frame++;

		if (frame / 4 >= animation_frames) {
			frame = 0;
			blowThatShitUp = false;
		}
	}

	//Layer 4
	for (int i = 0; i < mClouds1.size(); i++) {
		mClouds1[i].Draw(window);
	}

	mHeader->Draw(window);
	mFooter->Draw(window);
	window.draw(mLivesText);
	window.draw(mPointsText);
}

bool Game::LoadMedia()
{
	if (SoundBufferManager::getInstance().loadAsset("Assets/Explosion.wav")) {
		explosion = SoundBufferManager::getInstance().getAsset("Assets/Explosion.wav");
		explosionSound.setBuffer(*explosion);
	}

	if (SoundBufferManager::getInstance().loadAsset("Assets/Hit_Hurt.wav")) {
		hitHurt = SoundBufferManager::getInstance().getAsset("Assets/Hit_Hurt.wav");
		hitHurtSound.setBuffer(*hitHurt);
	}
	
	if (TextureManager::getInstance().loadAsset("Assets/player_fighter_jet.png")) {
	
	}

	if (TextureManager::getInstance().loadAsset("Assets/cloud.png")) {
		mCloudTexture = TextureManager::getInstance().getAsset("Assets/cloud.png");
	}

	if (TextureManager::getInstance().loadAsset("Assets/explode5edit.png")) {
		mSpriteSheet = TextureManager::getInstance().getAsset("Assets/explode5edit.png");
		mExplosion.texture = mSpriteSheet;
		//mExplosion.texture = mSpriteSheet;
		#pragma region SpriteLocations
					mSprites[0].left = 1;
					mSprites[0].top = 1;
					mSprites[0].width = 46;
					mSprites[0].height = 46;
		
					mSprites[1].left = 47;
					mSprites[1].top = 1;
					mSprites[1].width = 46;
					mSprites[1].height = 46;
		
					mSprites[2].left = 94;
					mSprites[2].top = 1;
					mSprites[2].width = 46;
					mSprites[2].height = 46;
		
					mSprites[3].left = 139;
					mSprites[3].top = 1;
					mSprites[3].width = 46;
					mSprites[3].height = 46;
		
					mSprites[4].left = 1;
					mSprites[4].top = 46;
					mSprites[4].width = 46;
					mSprites[4].height = 46;
		
					mSprites[5].left = 47;
					mSprites[5].top = 46;
					mSprites[5].width = 46;
					mSprites[5].height = 46;
		
					mSprites[6].left = 94;
					mSprites[6].top = 46;
					mSprites[6].width = 46;
					mSprites[6].height = 46;
		
					mSprites[7].left = 139;
					mSprites[7].top = 46;
					mSprites[7].width = 46;
					mSprites[7].height = 46;
		#pragma	endregion
	}
	return true;
}

bool Game::LoadClouds()
{
	////Cloud Set 3
	for (int i = 0; i < 15; i++) {
		mClouds3.push_back(Cloud(mCloudTexture, 40, 25, 255));
		mClouds3[i].posX = (float)(rand() % mScreenWidth);
		mClouds3[i].posY = (float)(rand() % mScreenHeight);
		mClouds3[i].defaultVel = 1;
		mClouds3[i].mScreenWidth = mScreenWidth;
		mClouds3[i].mScreenHeight = mScreenHeight;
	}
	////Cloud Set 2
	for (int i = 0; i < 10; i++) {
		mClouds2.push_back(Cloud(mCloudTexture, 80, 40, 200));
		mClouds2[i].posX = (float)(rand() % mScreenWidth);
		mClouds2[i].posY = (float)(rand() % mScreenHeight);
		mClouds2[i].defaultVel = 3;
		mClouds2[i].mScreenWidth = mScreenWidth;
		mClouds2[i].mScreenHeight = mScreenHeight;
	}
	////Cloud Set 1
	for (int i = 0; i < 5; i++) {
		mClouds1.push_back(Cloud(mCloudTexture, 120, 80, 150));
		mClouds1[i].posX = (float)(rand() % mScreenWidth);
		mClouds1[i].posY = (float)(rand() % mScreenHeight);
		mClouds1[i].defaultVel = 8;
		mClouds1[i].mScreenWidth = mScreenWidth;
		mClouds1[i].mScreenHeight = mScreenHeight;
	}

	return true;
}

bool Game::LoadShip()
{
	//Clean up entity if necessary
	if (mShip != nullptr) {
		delete mShip;
		mShip = nullptr;
	}

	mShip = new Player( sf::Vector2f((float)mScreenWidth/2, (float)mScreenHeight/2), mPlayerTexture);

	if (mShip == nullptr) {
		std::cerr << "*** Failed to create new Aircraft: " << std::endl;
		return false;
	}

	return true;
}

void Game::DeSpawn() {
	//mEnemies.clear();
}

bool Game::WriteGameSetup() {
	//tinyxml2::XMLDocument xmlDoc;
	//tinyxml2::XMLError eResult = xmlDoc.LoadFile("SavedData.xml");
	//if (eResult != tinyxml2::XML_SUCCESS) { xmlDoc.NewElement("SaveData"); }

	//tinyxml2::XMLNode* pRoot = xmlDoc.FirstChild();
	//if(pRoot == nullptr) {
	//	pRoot = xmlDoc.NewElement("SaveData");
	//	xmlDoc.InsertFirstChild(pRoot);
	//	xmlDoc.InsertFirstChild(pRoot);

	//	tinyxml2::XMLElement* pElement = xmlDoc.NewElement("GameData");
	//	pRoot->InsertEndChild(pElement);
	//	//tinyxml2::XMLElement * pElement = xmlDoc.NewElement("GameData");
	//	//Lives
	//	//Score
	//	pElement->SetAttribute("Lives", getPlayerLives());
	//	pElement->SetAttribute("Points", getPlayerPoints());
	//	pRoot->InsertEndChild(pElement);
	//}
	//else {
	//	tinyxml2::XMLElement* pElement = pRoot->FirstChildElement();
	//	if(pElement != nullptr) { 
	//		pElement = xmlDoc.NewElement("GameData"); 
	//		pRoot->InsertEndChild(pElement);
	//		pElement->SetAttribute("Lives", getPlayerLives());
	//		pElement->SetAttribute("Points", getPlayerPoints());
	//		pRoot->InsertEndChild(pElement);
	//	}
	//	else {
	//		pElement->DeleteAttribute("Lives");
	//		pElement->DeleteAttribute("Points");
	//		pElement->SetAttribute("Lives", getPlayerLives());
	//		pElement->SetAttribute("Points", getPlayerPoints());
	//		pRoot->InsertEndChild(pElement);
	//	}
	//	//tinyxml2::XMLElement * pElement = xmlDoc.NewElement("GameData");
	//	//Lives
	//	//Score
	//}
	//eResult = xmlDoc.SaveFile("SavedData.xml");
	//if (eResult != tinyxml2::XML_SUCCESS) {
	//	return false;
	//}
	return true;
}

void Game::Init()
{
	mLivesText.setString("LIVES | " + std::to_string(getPlayerLives()));
	mPointsText.setString("SCORE | " + std::to_string(getPlayerPoints()));
	
	std::cout << playerLives << std::endl;
	media = LoadMedia();
	if (!&media) {
		std::cerr << "*** Failed to load media: " << std::endl;
	}
	else {
		LoadClouds();
		LoadShip();
	}

	mHeader = new Entity(0.0f, 0.0f, mScreenWidth, 40.0f, orange);
	mFooter = new Entity(0.0f, mScreenHeight - 40.0f, mScreenWidth, mScreenHeight, orange);
}

void Game::Deinit()
{
}

bool Game::IsInit()
{
	return false;
}

void Game::Restart() {
	for (std::vector<Aircraft*>::iterator it = mEnemies.begin(); it != mEnemies.end(); it++) {
		(*it)->Reset();
	}
	setPlayerLives(3);
	mLivesText.setString("LIVES | " + std::to_string(getPlayerLives()));
	setPlayerPoints(0);
	mPointsText.setString("SCORE | " + std::to_string(getPlayerPoints()));
}