#include "ButtonTestGS.h"
#include "GUI_Button.h"
#include <SFML/Graphics.hpp>

void functionEventHandler(AGameState &gs, GUI_Button & comp) {
	ButtonTestGS &mgs = (ButtonTestGS &)gs;
	
}

ButtonTestGS::ButtonTestGS()
{
	GUI_Button *gb = new GUI_Button(
		sf::Vector2f(100.0f, 300.0f), 
		"q Test | Button j", 
		sf::Color(135, 200, 75), 
		*this,
		//&ImportantButtonWasPressed_event
		functionEventHandler
	);
	mDrawables.push_back(gb);
}


ButtonTestGS::~ButtonTestGS()
{
}

void ButtonTestGS::Update(float delta)
{
	for (std::size_t i = 0; i < mDrawables.size(); ++i) {
		GUI_Button *button = dynamic_cast<GUI_Button *> (mDrawables[i]);
		if (button != nullptr) {
			button->Update();
		}
	}
}

void ButtonTestGS::Draw(sf::RenderWindow & window)
{
	for (std::size_t i = 0; i < mDrawables.size(); ++i) {
		window.draw(*mDrawables[i]);
	}
}

void ButtonTestGS::Init()
{
}

void ButtonTestGS::Deinit()
{
}

bool ButtonTestGS::IsInit()
{
	return false;
}

void ButtonTestGS::handleButton_event(GUI_Button & comp)
{
	//Handle event here.
}

void ButtonTestGS::ImportantButtonWasPressed_event(GUI_Button &but) {
	
}
