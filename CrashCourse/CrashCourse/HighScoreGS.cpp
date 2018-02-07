#include "InputManager.h"
#include "AssetManager.h"
#include "GameStateManager.h"

#include "MainMenuGS.h"
#include "HighScoreGS.h"
#include "Game.h"

#include "tinyxml2.h"
#include <iostream>

HighScoreGS::HighScoreGS()
	: mTitle("HIGH SCORES", *FontManager::getInstance().getAsset("Assets/thunderstrike.ttf")),
	mBack("BACK", *FontManager::getInstance().getAsset("Assets/thunderstrike.ttf"))
{
	mTitle.setPosition(250, 10);
	mTitle.setCharacterSize(24);
	mTitle.setColor(sf::Color::White);

	mBack.setPosition(300, 550);
	mBack.setCharacterSize(24);
	mBack.setColor(sf::Color::White);
}

HighScoreGS::~HighScoreGS()
{
	//Only called when on full health. Wat
	saveData();
}

void HighScoreGS::Update(float delta)
{
	if (InputManager::getInstance().wasKeyReleased(InputManager::GK_ESCAPE)) {
		GameStateManager::getInstance().Change(MainMenuGS::getInstance());
	}
	//Mouse Input
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		// get the local mouse position (relative to a window)
		sf::Vector2f localPosition = InputManager::getInstance().getMousePos(); // window is a sf::Window
		if (HighScoreGS::getInstance().getBack().getGlobalBounds().contains(localPosition.x, localPosition.y)) {
			GameStateManager::getInstance().Change(MainMenuGS::getInstance());
		}
	}
}

void HighScoreGS::Draw(sf::RenderWindow & window)
{
	window.draw(mTitle);
	for (int i = 0; i < sizeof(highScoresDisplay); i++) {
		if (highScoresDisplay[i].getString() == "") {
			break;
		}
		window.draw(highScoresDisplay[i]);
		//If there are no more entries in high score array, don't go trying to draw the next item which is empty
	}
	window.draw(mBack);
}

void HighScoreGS::Init()
{
	loadData();
	prepareHighScoreDisplay();
	if (highScores.empty()) {
		highScoresDisplay[0].setString("NO HIGHSCORES TO DISPLAY");
		highScoresDisplay[0].setFont(*FontManager::getInstance().getAsset("Assets/thunderstrike.ttf"));
		highScoresDisplay[0].setCharacterSize(24);
		highScoresDisplay[0].setFillColor(sf::Color(175, 0, 0, 255));
		highScoresDisplay[0].setPosition(120, 60);
	}
	else {
		int y = 30;
		int i = 0;
		while (highScoresDisplay[i].getString() != "") {
			highScoresDisplay[i].setFont(*FontManager::getInstance().getAsset("Assets/thunderstrike.ttf"));
			highScoresDisplay[i].setCharacterSize(24);
			highScoresDisplay[i].setFillColor(sf::Color(255, 160, 0, 255));
			highScoresDisplay[i].setPosition(50, y * i + 100);
			i++;
		} 
	}
}

void HighScoreGS::Deinit()
{
}

bool HighScoreGS::IsInit()
{
	return false;
}

bool HighScoreGS::saveData() {
	tinyxml2::XMLDocument xmlDoc;
	tinyxml2::XMLNode * pRoot;
	tinyxml2::XMLError eResult = xmlDoc.LoadFile("SavedData.xml");

	if (eResult != tinyxml2::XML_SUCCESS) {
		//xmlDoc.NewElement("SaveData");
		pRoot = xmlDoc.NewElement("SaveData");
		xmlDoc.InsertFirstChild(pRoot);
	}
	else {
		pRoot = xmlDoc.FirstChildElement("SaveData");
	}

	tinyxml2::XMLElement* pElement = pRoot->FirstChildElement("GameData");
	if (pElement == NULL) {
		pElement = xmlDoc.NewElement("GameData");
		pElement->SetAttribute("Lives", Game::getInstance().getPlayerLives());
		pElement->SetAttribute("Points", Game::getInstance().getPlayerPoints());
		pRoot->InsertEndChild(pElement);
	}
	else {
		//if (pElement != nullptr) {
		//	pElement = xmlDoc.NewElement("GameData");
		//	pElement->SetAttribute("Lives", Game::getInstance().getPlayerLives());
		//	pElement->SetAttribute("Points", Game::getInstance().getPlayerPoints());
		//	pRoot->InsertEndChild(pElement);
		//} else {
			//pElement->DeleteAttribute("Lives");
			//pElement->DeleteAttribute("Points");
		int lives = Game::getInstance().getPlayerLives();
		int points = Game::getInstance().getPlayerPoints();
		pElement->SetAttribute("Lives", Game::getInstance().getPlayerLives());
		pElement->SetAttribute("Points", Game::getInstance().getPlayerPoints());
		pRoot->InsertEndChild(pElement);
		//}
	}
	pElement = pRoot->FirstChildElement("HighScores");
	if (pElement == NULL) {
		pElement = xmlDoc.NewElement("HighScores");
		pRoot->InsertEndChild(pElement);
	}
	std::map<std::string, int>*hs = HighScoreGS::getInstance().getHighScores();
	//Delete all high scores in file before inserting new top 10
	pElement->DeleteChildren();

	for (std::map<std::string, int>::iterator it = hs->begin(); it != hs->end(); ++it)
	{
		tinyxml2::XMLElement* pListElement;
		const char *cstr = it->first.c_str();
		//List of 10 Highscores
		//Name (3 Letter) - HighScore
		pListElement = xmlDoc.NewElement("HighScoreEntry");
		pListElement->SetAttribute("Name", cstr);
		pListElement->SetText(it->second);
		pElement->InsertEndChild(pListElement);
	}
	//pRoot->InsertEndChild(pInsertAfter);
	eResult = xmlDoc.SaveFile("SavedData.xml");
	if (eResult != tinyxml2::XML_SUCCESS) {
		return false;
	}
	return true;
}

bool HighScoreGS::loadData() {
	tinyxml2::XMLDocument xmlDoc;
	tinyxml2::XMLError eResult = xmlDoc.LoadFile("SavedData.xml");

	if (eResult != tinyxml2::XML_SUCCESS)
	{
		printf("Error: %i\n", eResult);
	}

	tinyxml2::XMLNode * pRoot = xmlDoc.FirstChild();

	if (pRoot == nullptr) 
		return tinyxml2::XML_ERROR_FILE_READ_ERROR;
	tinyxml2::XMLElement * pElement = pRoot->FirstChildElement("HighScores");
	if (pElement == nullptr)
		return tinyxml2::XML_ERROR_PARSING_ELEMENT;

	tinyxml2::XMLElement * pListElement = pElement->FirstChildElement("HighScoreEntry");
	while (pListElement != nullptr)
	{
		int iOutListValue;
		const char * nameAt = nullptr;
		nameAt = pListElement->Attribute("Name");
		if (nameAt == nullptr) return tinyxml2::XML_ERROR_PARSING_ATTRIBUTE;
		std::string name = nameAt;

		eResult = pListElement->QueryIntText(&iOutListValue);
		if (eResult != tinyxml2::XML_SUCCESS)
		{
			printf("Error: %i\n", eResult);
		}
		else {
			setHighScore(name, iOutListValue);
		}
		pListElement = pListElement->NextSiblingElement("HighScoreEntry");
	}
	pElement = pRoot->FirstChildElement("GameData");
	const char * livesAt = nullptr;
	livesAt = pElement->Attribute("Lives");
	if (livesAt == nullptr) return tinyxml2::XML_ERROR_PARSING_ATTRIBUTE;
	int lives = std::stoi(livesAt);

	const char * pointsAt = nullptr;
	pointsAt = pElement->Attribute("Points");
	if (pointsAt == nullptr) return tinyxml2::XML_ERROR_PARSING_ATTRIBUTE;
	int points = std::stoi(pointsAt);

	Game::getInstance().setPlayerLives(lives);
	Game::getInstance().setPlayerPoints(points);

	if (pElement == nullptr) return tinyxml2::XML_ERROR_PARSING_ELEMENT;
}
