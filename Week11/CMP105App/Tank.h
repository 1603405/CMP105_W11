#pragma once
#include "Framework/GameObject.h"
#include "Framework/Animation.h"
#include <iostream>
#include "Framework/Collision.h"

class Tank : public GameObject
{
public:
	// Defalt constructor
	Tank();

	// Defalt deconstructor
	~Tank();

	// Tank draw
	void draw(sf::RenderWindow* window);

	// Tank update
	void update(float dt) override;		//question why this is overrided?

	// Tank handleInput
	void handleInput(float dt, Input* in);

	// Returns angle between two points 
	double getAngle(double x1, double y1, double x2, double y2);


	// Calculate the direction of motion
	int tankVelocity = 100;
	void calVelocity(int velocity);
	float velocityX = 0;
	float velocityY = 0;

	float safeRotation;
	 
	// Apply input to motion and animation
	void motion(float dt, Input* input);

	void animation(float dt, Input* input);
	float animationSpeed = .015f;

	// TurningRate * dt
	int turningRate = 75;


	// Position variables, map is 20 wide by 15 tall, BlockX and BlockY represent what block coordinated they are on
	int blockX;
	int blockY;

	// Variables represent the square of the difference between the side block
	double DiffLeft2;
	double DiffRight2;
	double DiffTop2;
	double DiffBot2;

	void radiiCollisionReset(bool arr[3][3]);
	bool blockLocationArr[3][3] = { 0, 0, 0,	0, 0, 0,	0, 0, 0, };




		// This array will hold a copy of the mapset list data. This use of an arry does not constrict the size of or iregularity
	// of a maps design as a much larger array e.g. 100x100 could be used only filling the associated blocks, allowing for different
	// configerations of maps .e.g 20*40, 60*80. However this will not be explored in this project because only a standard map sizes  
	// was needed. mapBlock[Game level][X block][Y block]
	bool mapBlock/*[levels]*/[15][20] = {
 1,	 1,	 1,	 1,	 1,	 1,	 1,	 1,	 1,	 1,	 1,	 1,	 1,	 1,	 1,	 1,	 1,	 1,	 1,	 1,
 1,	 0,	 0,	 0,	 0,	 0,	 0,	 0,	 0,	 0,	 0,	 0,	 0,	 0,	 0,	 0,	 0,	 0,	 0,	 1,
 1,	 0,	 0,	 0,	 0,	 0,	 0,	 0,	 0,	 0,	 0,	 0,	 0,	 0,	 0,	 0,	 0,	 0,	 0,	 1,
 1,	 0,	 0,	 0,	 0,	 0,	 0,	 0,	 0,	 1,	 0,	 0,	 0,	 0,	 0,	 0,	 0,	 0,	 0,	 1,
 1,	 0,	 0,	 0,	 0,	 1,	 0,	 0,	 0,	 1,	 0,	 0,	 0,	 0,	 0,	 0,	 0,	 0,	 0,	 1,
 1,	 0,	 0,	 0,	 0,	 0,	 0,	 0,	 0,	 1,	 0,	 0,	 0,	 0,	 0,	 0,	 0,	 0,	 0,	 1,
 1,	 0,	 0,	 0,	 0,	 0,	 0,	 0,	 0,	 1,	 0,	 0,	 0,	 0,	 0,	 0,	 0,	 0,	 0,	 1,
 1,	 0,	 0,	 0,	 0,	 0,	 0,	 0,	 0,	 1,	 0,	 0,	 0,	 0,	 0,	 0,	 0,	 0,	 0,	 1,
 1,	 0,	 0,	 0,	 0,	 0,	 0,	 0,	 0,	 0,	 0,	 0,	 0,	 0,	 0,	 0,	 0,	 0,	 0,	 1,
 1,	 0,	 0,	 0,	 0,	 0,	 0,	 0,	 0,	 0,	 0,	 0,	 0,	 0,	 0,	 0,	 0,	 0,	 0,	 1,
 1,	 0,	 0,	 0,	 0,	 0,	 0,	 0,	 0,	 0,	 0,	 0,	 0,	 0,	 0,	 0,	 0,	 0,	 0,	 1,
 1,	 0,	 0,	 0,	 0,	 0,	 0,	 0,	 0,	 0,	 0,	 0,	 0,	 0,	 0,	 0,	 0,	 0,	 0,	 1,
 1,	 0,	 0,	 0,	 0,	 0,	 0,	 0,	 0,	 0,	 0,	 0,	 0,	 0,	 0,	 0,	 0,	 0,	 0,	 1,
 1,	 0,	 0,	 0,	 0,	 0,	 0,	 0,	 0,	 0,	 0,	 0,	 0,	 0,	 0,	 0,	 0,	 0,	 0,	 1,
 1,	 1,	 1,	 1,	 1,	 1,	 1,	 1,	 1,	 1,	 1,	 1,	 1,	 1,	 1,	 1,	 1,	 1,	 1,	 1,
	};
protected:
	Animation wait;
	Animation forward;
	Animation back;
	Animation left;
	Animation right;
	Animation forwardLeft;
	Animation forwardRight;
	Animation backLeft;
	Animation backRight;
	Animation* currentAnimation;

	
	// HitBox
	sf::CircleShape hitRadii;	

};
