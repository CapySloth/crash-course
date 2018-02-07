#include "GUI_Button.h"
#include "ColorHelper.h"
#include "AssetManager.h"
#include "InputManager.h"
#include "ButtonTestGS.h"
#include "GameState.h"
#include <SFML/Graphics.hpp>

GUI_Button::GUI_Button(sf::Vector2f position, std::string text, sf::Color color, 
		AGameState &gs, 
		//void(AGameState::*callback)(GUI_Button &))
		void(*callback)(AGameState &, GUI_Button &))
	:	mBaseColor(color), mCurrentState(BS_NORMAL), mButtonComponents(21),
		mGameState(gs), mCallback(callback)
{
	HSV_Color hbsc = rgb2hsv(mBaseColor);
	HSV_Color hbrc = shiftHSV(hbsc, 5, 10, 10);
	mBrightColor = hsv2rgb(hbrc);
	HSV_Color hdkc = shiftHSV(hbsc, -5, -20, -20);
	mDarkColor = hsv2rgb(hdkc);
	HSV_Color hdkstc = shiftHSV(hbsc, -5, -20, -40);
	mDarkestColor = hsv2rgb(hdkstc);

	sf::Texture &outline = *TextureManager::getInstance().getAsset("assets/btn_outline.png");
	sf::Vector2u osize = outline.getSize();
	int ox3 = osize.x / 3;
	int oy3 = osize.y / 3;
	sf::Texture &background = *TextureManager::getInstance().getAsset("assets/btn_background.png");
	//Assume that background and outline are same size. If not, oh well!
	sf::Font &font = *FontManager::getInstance().getAsset("assets/Orbitron Medium.ttf");
	//Figure out how big the text will be.
	sf::Text *txt = new sf::Text(text, font); //use default font size for now.
	txt->setPosition(position + sf::Vector2f((float)ox3 * 0.5f, (float)oy3 * 0.5f));
	txt->setFillColor(sf::Color::Black);
	sf::FloatRect size = txt->getLocalBounds();
	int cheight = txt->getCharacterSize() * 3 / 2;
	float midw = (size.width - (float)(ox3) + 5);
	float midh = (float)(cheight - (2 * oy3));
	//mButtonComponents
	//Draw order:	1. Background (9 sprites) 0-8
	//				2. Outline (8 sprites) 9-16
	//				3. Shadow (3 sprites, only sometimes drawn) 17-19
	//				4. Text (1 text) 20
	//States:
	// NORMAL:		Background	Base
	//				Outline		Dark
	//				Shadow		not drawn
	// HOVER:		Background	Bright
	//				Outline		Base
	//				Shadow		Darkest
	// PRESSED:		Background	Base
	//				Outline		Darkest
	//				Shadow		Bright
	// DISABLED		Background	Dark
	//				Outline		Darkest
	//				Shadow		not drawn
	//Slice sprites
	int outlineCount = 0;
	int centerFudge = 0;
	for (int y = 0; y < 3; ++y) {
		for (int x = 0; x < 3; ++x) {
			sf::Sprite *osprite = new sf::Sprite(outline, sf::IntRect(x * ox3, y * oy3, ox3, oy3));
			osprite->setPosition(position);
			osprite->setColor(mDarkColor);
			sf::Sprite *bsprite = new sf::Sprite(background, sf::IntRect(x * ox3, y * oy3, ox3, oy3));
			bsprite->setPosition(position);
			bsprite->setColor(mBaseColor);
			//Is this a left, middle, or right slice?
			if (x == 0) {
				//left, no move needed
			}
			else if (x == 1) {
				//middle, move and stretch needed
				osprite->move(sf::Vector2f((float)ox3,0.0f));
				osprite->scale(midw / (float)ox3, 1.0f);
				bsprite->move(sf::Vector2f((float)ox3, 0.0f));
				bsprite->scale(midw / (float)ox3, 1.0f);
			}
			else if (x == 2) {
				//right, move needed
				osprite->move(sf::Vector2f(ox3 + midw, 0.0f));
				bsprite->move(sf::Vector2f(ox3 + midw, 0.0f));
			}
			//Is this a top, middle, or bottom slice
			if (y == 0) {
				//top, no move needed
			}
			else if (y == 1) {
				//middle, move and stretch needed
				osprite->move(sf::Vector2f(0.0f, (float)oy3));
				osprite->scale(1.0f, midh / (float)oy3);
				bsprite->move(sf::Vector2f(0.0f, (float)oy3));
				bsprite->scale(1.0f, midh / (float)oy3);
			}
			else if (y == 2) {
				osprite->move(sf::Vector2f(0.0f, oy3 + midh));
				bsprite->move(sf::Vector2f(0.0f, oy3 + midh));
			}
			if (x == 1 && y == 1) {
				//Don't add the center piece for outline
				mButtonComponents[3 * y + x] = bsprite;
				centerFudge = 1;
			}
			else {
				mButtonComponents[3*y + x] = bsprite;
				mButtonComponents[3 * y + x + 9 - centerFudge] = osprite;
			}
			if (((x == 1 || x == 2) && y == 2) || (x == 2 && y ==1)) {
				sf::Sprite *ssprite = new sf::Sprite(*osprite);
				ssprite->move(3.0f, 3.0f);
				ssprite->setColor(mDarkestColor);
				mButtonComponents[17 + outlineCount] = ssprite;
				++outlineCount;
			}
		}
	}
	//Add the text last.
	mButtonComponents.back() = txt;

}


GUI_Button::~GUI_Button()
{
}

void GUI_Button::Update()
{
	switch (mCurrentState) {
		case BS_DISABLED:
			break;
		case BS_NORMAL:
			for (std::size_t i = 0; i < 9; ++i) {
				if (((sf::Sprite *)mButtonComponents[i])->getGlobalBounds().contains(InputManager::getInstance().getMousePos())) {
					setState(BS_HOVERED);
					break;
				}
			}
			break;
		case BS_HOVERED: {
			bool inBounds = false;
			for (std::size_t i = 0; i < 9; ++i) {
				if (((sf::Sprite *)mButtonComponents[i])->getGlobalBounds().contains(InputManager::getInstance().getMousePos())) {
					inBounds = true;
					break;
				}
			}
			if (!inBounds) {
				setState(BS_NORMAL);
			}
			else if (InputManager::getInstance().wasKeyPressed(InputManager::GK_ENTER)) {
				setState(BS_PRESSED);
			}
			break;
		}
		case BS_PRESSED:
			bool inBounds = false;
			for (std::size_t i = 0; i < 9; ++i) {
				if (((sf::Sprite *)mButtonComponents[i])->getGlobalBounds().contains(InputManager::getInstance().getMousePos())) {
					inBounds = true;
					break;
				}
			}
			if (!inBounds) {
				setState(BS_NORMAL);
			}
			else if (InputManager::getInstance().wasKeyReleased(InputManager::GK_ENTER)) {
				setState(BS_HOVERED);
				//Trigger an event
				//mGameState.handleButton_event(*this);
				//(mGameState.*(mCallback))(*this);
				(*mCallback)(mGameState, *this);
			}
			break;
			
	}
}

void GUI_Button::SetEnabled(bool enable)
{
	if (mCurrentState == BS_DISABLED && enable) {
		setState(BS_NORMAL);
	}
	else if (mCurrentState != BS_DISABLED && !enable) {
		setState(BS_DISABLED);
	}
}

void GUI_Button::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	for (std::size_t i = 0; i < mButtonComponents.size() - 4; ++i) {
		target.draw(*mButtonComponents[i], states);
	}
	if (mCurrentState == BS_HOVERED || mCurrentState == BS_PRESSED) {
		for (std::size_t i = mButtonComponents.size() - 4; i < mButtonComponents.size() - 1; ++i) {
			target.draw(*mButtonComponents[i], states);
		}
	}
	target.draw(*mButtonComponents.back(), states);
}

void GUI_Button::setState(ButtonState newState)
{
	if (newState == mCurrentState) {
		return;
	}
	//mButtonComponents
	//Draw order:	1. Background (9 sprites) 0-8
	//				2. Outline (8 sprites) 9-16
	//				3. Shadow (3 sprites, only sometimes drawn) 17-19
	//				4. Text (1 text) 20
	//States:
	// NORMAL:		Background	Base
	//				Outline		Dark
	//				Shadow		not drawn
	// HOVER:		Background	Bright
	//				Outline		Base
	//				Shadow		Darkest
	// PRESSED:		Background	Base
	//				Outline		Darkest
	//				Shadow		Bright
	// DISABLED		Background	Dark
	//				Outline		Darkest
	//				Shadow		not drawn
	mCurrentState = newState;
	switch (newState) {
		case BS_NORMAL:
			for (std::size_t i = 0; i < 9; ++i) {
				((sf::Sprite *)mButtonComponents[i])->setColor(mBaseColor);
			}
			for (std::size_t i = 9; i < 17; ++i) {
				((sf::Sprite *)mButtonComponents[i])->setColor(mDarkColor);
			}
			break;
		case BS_HOVERED:
			for (std::size_t i = 0; i < 9; ++i) {
				((sf::Sprite *)mButtonComponents[i])->setColor(mBrightColor);
			}
			for (std::size_t i = 9; i < 17; ++i) {
				((sf::Sprite *)mButtonComponents[i])->setColor(mBaseColor);
			}
			for (std::size_t i = 17; i < 20; ++i) {
				((sf::Sprite *)mButtonComponents[i])->setColor(mDarkestColor);
			}
			break;
		case BS_PRESSED:
			for (std::size_t i = 0; i < 9; ++i) {
				((sf::Sprite *)mButtonComponents[i])->setColor(mBaseColor);
			}
			for (std::size_t i = 9; i < 17; ++i) {
				((sf::Sprite *)mButtonComponents[i])->setColor(mDarkestColor);
			}
			for (std::size_t i = 17; i < 20; ++i) {
				((sf::Sprite *)mButtonComponents[i])->setColor(mBrightColor);
			}
			break;
		case BS_DISABLED:
			for (std::size_t i = 0; i < 9; ++i) {
				((sf::Sprite *)mButtonComponents[i])->setColor(mDarkColor);
			}
			for (std::size_t i = 9; i < 17; ++i) {
				((sf::Sprite *)mButtonComponents[i])->setColor(mDarkestColor);
			}
			break;
	}
}
