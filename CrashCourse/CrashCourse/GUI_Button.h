#pragma once

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Color.hpp>
#include <string>
#include <vector>

class AGameState;

class GUI_Button : public sf::Drawable
{
public:
	GUI_Button(sf::Vector2f position, std::string text, sf::Color color, 
		AGameState &gs, 
		//void (AGameState::*callback)(GUI_Button &)
		void (*callback)(AGameState &, GUI_Button &)
		);
	~GUI_Button();

	void Update();

	void SetEnabled(bool enable);
	
protected:
	enum ButtonState {
		BS_NORMAL,
		BS_HOVERED,
		BS_PRESSED,
		BS_DISABLED,
		BS_COUNT
	};

	// Inherited via Drawable
	virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const override;
	void setState(ButtonState newState);
	

private:
	AGameState &mGameState;
	//void(AGameState::*mCallback)(GUI_Button &);
	void(*mCallback)(AGameState &, GUI_Button &);
	ButtonState mCurrentState;
	std::vector<sf::Drawable *> mButtonComponents;
	sf::Color mBaseColor;
	sf::Color mDarkColor;
	sf::Color mDarkestColor;
	sf::Color mBrightColor;
};

