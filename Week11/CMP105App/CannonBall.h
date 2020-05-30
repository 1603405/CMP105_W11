#pragma once
#include "Framework/GameObject.h"
#include "Cannon.h"
#include <iostream>
 
class CannonBall : public Tank
{
public:
	// Defalt constructor
	CannonBall();

	// Defalt deconstructor
	~CannonBall();

	// CannonBall draw
	void draw(sf::RenderWindow* window);


	// CannonBall updateEnemy
	void updateEnemyCannonBall(float dt, Cannon enemyCannon);

	// CannonBall handleInputPlayer
	void playerInputandUpdateCannonBall(float dt, Input* input, Cannon playerCannon);

;
	double cannonBallVelocity = 50;

	sf::Clock playerCannonBallTimer;
	sf::Clock enemyCannonBallTimer;





protected:
	
	Animation wait;
};

