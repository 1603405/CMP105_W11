#pragma once
#include "Tank.h"

class Cannon : public Tank
{
public:
	// Defalt constructor
	Cannon();

	// Defalt deconstructor
	~Cannon();

	// Cannon draw
	void draw(sf::RenderWindow* window);

	// Player cannon update
	void updatePlayer(float dt, double mouseX, double mouseY, Tank playerTankBase);

	// Player cannon update
	void updateEnemy(float dt, Tank playerTankBase);

	// Cannon handleInput
	void handleInput(float dt);

	// TurningRate * dt
	int turningRate = 75;

protected:
	

	Animation wait;
};

