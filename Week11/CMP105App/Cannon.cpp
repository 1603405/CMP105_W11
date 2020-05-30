#include "Cannon.h"


// Defalt constructor
Cannon::Cannon()
{
	wait.setFrameSpeed(animationSpeed);
	wait.addFrame(sf::IntRect(0, 0, 40, 90));
	currentAnimation = &wait;
	setTextureRect(currentAnimation->getCurrentFrame());

}

// Defalt deconstructor
Cannon::~Cannon()
{

}

// handle user input
void Cannon::handleInput(float dt)
{

}

// Update game objects
void Cannon::updatePlayer(float dt, double mouseX, double mouseY, Tank playerTankBase)
{
	setPosition(playerTankBase.getPosition());
	setRotation(getAngle(mouseX, mouseY, playerTankBase.getPosition().x, playerTankBase.getPosition().y));
}

// Update game objects
void Cannon::updateEnemy(float dt, Tank playerTankBase)
{
	setRotation(getAngle(playerTankBase.getPosition().x, playerTankBase.getPosition().y, getPosition().x, getPosition().y));
}

// Tank draw
void Cannon::draw(sf::RenderWindow* window)
{
	window->draw(*this);		//"*this" is a pointer to the object that preceds the member function (draw())
	//window->draw(hitBox);
}