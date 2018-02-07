#pragma once
#include "GameState.h"
#include <SFML/Graphics/Drawable.hpp>
#include <vector>

class GUI_Button;

class ButtonTestGS :
	public AGameState
{
	friend void functionEventHandler(AGameState &gs, GUI_Button & comp);
public:
	static ButtonTestGS &getInstance() {
		static ButtonTestGS instance;
		return instance;
	}
	~ButtonTestGS();

private:
	ButtonTestGS();
	ButtonTestGS(ButtonTestGS const &);
	ButtonTestGS &operator=(ButtonTestGS const &);

public:
	// Inherited via AGameState
	virtual void Update(float delta) override;
	virtual void Draw(sf::RenderWindow & window) override;
	virtual void Init() override;
	virtual void Deinit() override;
	virtual bool IsInit() override;

	void ImportantButtonWasPressed_event(GUI_Button &but);
	void handleButton_event(GUI_Button &comp);

private:
	std::vector<sf::Drawable *> mDrawables;
	
};

