#pragma once
#include <SFML\Graphics.hpp>

class Cloud {
public:
	//Position
	float posX;
	float posY;

	float velX;
	float velY;

	float defaultVel;
	//Window in use
	int mScreenWidth;
	int mScreenHeight;

	//Contructs
	Cloud(sf::Texture *texture, int width, int height, sf::Uint8 alpha);
	//Deallocate
	~Cloud();

	void setSreenSize(int w, int y);
	void setVelocity(float x, float y);

	void CalculateTragectory(float delta, float mHeading);
	void Update(float delta);
	void Draw(sf::RenderWindow & window);

private:
	sf::Texture mTexture;
	//Visibilty
	sf::Uint8 mAlpha;
	//Dimensions
	float mWidth;
	float mHeight;
};