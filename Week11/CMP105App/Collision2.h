#pragma once
#include "CannonBall.h"
#include <iostream>

// Collision Class
// Provides default functions for testing collision detection. Functions for standard axis aligned bounding box, and bounding circle.
// @author Paul Robertson 


// Static class provide collision detection functions.
class Collision2 : public CannonBall
{
public:

	// Check AABB for collision. Returns true if collision occurs.
	static bool checkBoundingBox(GameObject* sp1, GameObject* sp2);
	// Check collision with box and point. Returns true if collision occurs.
	static bool checkBoundingBoxAABB_AABB(GameObject* s1, sf::Vector2i s2);
	// Check bounding circle collision. Returns true if collision occurs.
	static bool checkBoundingSphere(GameObject* sp1, GameObject* sp2);

	// Does the tank radii collide with the outter box
	bool tankRadiiCollisionArr[3][3];

	// Check if cannonBall colides with map
	bool cannonBallMapCollision(CannonBall cannonball);


	// 1st collision check, what corner boxes does the radii of the tank touch, reference diagram in notes
	// Parameters are the squared difference between tank position and respected wall
	void radiiCollision(double left, double right, double top, double bot, bool arr[3][3], double radii);

	// 2nd collision check, does
	bool checkBoundingBoxAABB_OBB(GameObject s1, double rotate, double xPos, double yPos, int xBlock, int yBlock, double tankWidth, double tankHeight, sf::Vector2f tankPos);

	void colisionResponse(int test[]);

	//rotation shite
	double findRotation0_90(double rotation);

	//void playerCannonBallCollision( CannonBall cannonBall);
	// Orientated Bounding Boxes (OBB). s1 = OBB, s2 = AABB
	//bool checkOrientatedBoundingBoxes(GameObject* s1, GameObject* s2);
};