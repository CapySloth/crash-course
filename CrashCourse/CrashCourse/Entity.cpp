#include "Entity.h"

const sf::Color	Entity::msDefaultColor = { 255, 255, 255, 255 };// white

Entity::Entity(float x, float y, float w, float h, sf::Color color)
	: mRect()
	, mColor()
{
	mRect.left = x;
	mRect.top = y;
	mRect.width = w;
	mRect.height = h;
	mColor = color;// struct bitwise copy
}

sf::Vector2f Entity::Center() const
{
	sf::Vector2f p;
	p.x = Left() + Width() / 2;
	p.y = Top() + Height() / 2;
	return p;
}

sf::IntRect Entity::BoundingBox() const {
	return mRect;
}

void Entity::SetCenter(int x, int y)
{
	SetTop(x - Width() / 2);
	SetLeft(y - Height() / 2);
}

void Entity::Move(sf::Vector2f vel)
{
	mRect.left += vel.x;
	mRect.top += vel.y;
}

void Entity::Update(const sf::Uint8* keys)
{

}

void Entity::Draw(sf::RenderWindow & window) const
{
	sf::RectangleShape entity;
	entity.setFillColor(mColor);
	entity.setSize(sf::Vector2f(mRect.width, mRect.height));
	entity.setPosition(sf::Vector2f(mRect.left, mRect.top));
	entity.setOutlineColor(sf::Color::Black);
	entity.setOutlineThickness(1);
	// set new color for drawing
	window.draw(entity);
	//SDL_SetRenderDrawColor(renderer, mColor.r, mColor.g, mColor.b, mColor.a);

	// draw the player sprite using the selected color
	//SDL_RenderFillRect(renderer, &mRect);
}


bool Entity::CheckCollision(sf::IntRect a, sf::IntRect b)
{
	//The sides of the rectangles
	int leftA, leftB;
	int rightA, rightB;
	int topA, topB;
	int bottomA, bottomB;

	//Calculate the sides of rect A
	leftA = a.left;
	rightA = a.left; + a.width;
	topA = a.top;
	bottomA = a.top + a.height;

	//Calculate the sides of rect B
	leftB = b.left;
	rightB = b.left + b.width;
	topB = b.top;
	bottomB = b.top + b.height;

	//If any of the sides from A are outside of B
	if (bottomA <= topB)
	{
		return false;
	}

	if (topA >= bottomB)
	{
		return false;
	}

	if (rightA <= leftB)
	{
		return false;
	}

	if (leftA >= rightB)
	{
		return false;
	}

	return true;
}