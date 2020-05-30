#pragma once
#include "Collision2.h"

	// Check AABB for collision. Returns true if collision occurs.
	bool Collision2::checkBoundingBox(GameObject* s1, GameObject* s2)
	{
		if (s1->getCollisionBox().left + s1->getCollisionBox().width < s2->getCollisionBox().left)
			return false;
		if (s1->getCollisionBox().left > s2->getCollisionBox().left + s2->getCollisionBox().width)
			return false;
		if (s1->getCollisionBox().top + s1->getCollisionBox().height < s2->getCollisionBox().top)
			return false;
		if (s1->getCollisionBox().top > s2->getCollisionBox().top + s2->getCollisionBox().height)
			return false;

		return true;
	}

	// Check for bounding box collision with a point/vector2 rather than two boxes.
	bool Collision2::checkBoundingBoxAABB_AABB(GameObject* s1, sf::Vector2i s2)
	{
		if (s1->getCollisionBox().left + s1->getCollisionBox().width < s2.x)
		{
			return false;
		}
		if (s1->getCollisionBox().left > s2.x)
		{
			return false;
		}
		if (s1->getCollisionBox().top + s1->getCollisionBox().height < s2.y)
			return false;
		if (s1->getCollisionBox().top > s2.y)
			return false;

		return true;
	}

	// Check bounding circle collision. Returns true if collision occurs.
	bool Collision2::checkBoundingSphere(GameObject* s1, GameObject* s2)
	{
		// Get radius and centre of sprites.
		float radius1 = s1->getSize().x / 2;
		float radius2 = s2->getSize().x / 2;
		float xpos1 = s1->getPosition().x + radius1;
		float xpos2 = s2->getPosition().x + radius2;
		float ypos1 = s1->getPosition().y + radius1;
		float ypos2 = s2->getPosition().y + radius2;

		if (pow(xpos2 - xpos1, 2) + pow(ypos2 - ypos1, 2) < pow(radius1 + radius2, 2))
		{
			return true;
		}
		return false;
	}


	bool Collision2::checkBoundingBoxAABB_OBB(GameObject s1, double rotate, double xPos, double yPos, int xBlock, int yBlock, double tankWidth, double tankHeight, sf::Vector2f tankPos)
	{
		// Set the position of the block to the proper coordinates reguarding the top left block the tank is occupying as 0, 0.
		s1.setPosition(sf::Vector2f(xBlock, yBlock));



		//AABB dimenstions
		double tankMaxXAABB = xPos + tankWidth;
		double tankMinXAABB = xPos - tankWidth;
		double tankMaxYAABB = yPos + tankHeight;
		double tankMinYAABB = yPos - tankHeight;

		double blockMinXAABB = yBlock;
		double blockMaxXAABB = yBlock + 100.0;
		double blockMinYAABB = xBlock;
		double blockMaxYAABB = xBlock + 100.0;


		double originX = (-xBlock + yPos);
		double originY = (-yBlock + xPos);

		// Set origin has to be done first
		//s1.setOrigin(originX, originY);
		//s1.setPosition(tankPos);
		//s1.setRotation(findRotation0_90(rotate));


		//OBB dimensions
		double tankMinXOBB = xPos + 50;
		double tankMaxXOBB = xPos - 50;
		double tankMinYOBB = yPos + 50;
		double tankMaxYOBB = yPos - 50;


		double blockMinXOBB = s1.getGlobalBounds().left;
		double blockMaxXOBB = blockMinXOBB + s1.getGlobalBounds().width;
		double blockMinYOBB = s1.getGlobalBounds().top;
		double blockMaxYOBB = blockMinYOBB - s1.getGlobalBounds().height;

		return true;
	}

	void Collision2::colisionResponse(int test[])
	{


	}

	//This function will return the negative rotation of an object, converting it to a value between 0-90. e.g. 95 = 5, 190 = 10...
	double Collision2::findRotation0_90(double rotation)
	{

		if (rotation > 315 || rotation < 45)
		{
			return rotation;
		}
		else if (rotation >= 45 && rotation < 135)
		{
			return (rotation - 90);
		}
		else if (rotation >= 135 && rotation < 225)
		{
			return (rotation - 180);
		}
		else if (rotation >= 225 && rotation < 315)
		{
			return (rotation - 270);
		}
	}


	//void Collision2::playerCannonBallCollision(CannonBall cannonBall)
	//{	
	//	for (int i = 0; i < 3; i++)
	//	{
	//		for (int j = 0; j < 3; j++)
	//		{
	//			if(cannonBall.blockLocationArr[i][j] && mapBlock[(i + cannonBall.blockX - 1)][(j + cannonBall.blockY - 1)])
	//			{
	//				std::cout << "hit" << std::endl;
	//			}

	//		}
	//	}
	//}



	// 1st collision check, what corner boxes does the radii of the tank touch, reference diagram in notes
	// Parameters are the squared difference between tank position and respected wall
	void Collision2::radiiCollision(double left, double right, double top, double bot, bool arr[3][3], double radii)
	{

		if ((left) < radii)				// Does tank collide with block [][]
		{
			arr[1][0] = 1;
		}
		if ((right) < radii)				// Does tank collide with block [][]
		{
			arr[1][2] = 1;
		}
		if ((top) < radii)				// Does tank collide with block [][]
		{
			arr[0][1] = 1;
		}
		if ((bot) < radii)				// Does tank collide with block [][]
		{
			arr[2][1] = 1;
		}
		if ((left + top) < radii)		// Does tank collide with block [][]
		{
			arr[0][0] = 1;
		}
		if ((right + top) < radii)		// Does tank collide with block [][]
		{
			arr[0][2] = 1;
		}
		if ((left + bot) < radii)		// Does tank collide with block [][]
		{
			arr[2][0] = 1;
		}
		if ((right + bot) < radii)		// Does tank collide with block [][]
		{
			arr[2][2] = 1;
		}
		//std::cout << "left: " << (int)left << "	Right: " << (int)right << "	Top: " << (int)top << "	bottom: " << (int)bot << std::endl;
		//std::cout << "left Top: " << (int)left+top << "	Right Top: " << (int)right+top << "Left	bot: " << (int)left + bot << "	Right Bot: " << (int)bot+right << std::endl;
	}


	// Check if cannonBall colides with map
	bool Collision2::cannonBallMapCollision(CannonBall cannonball)
	{
		int blockX = (int)(cannonball.getPosition().x / 100);
		int blockY = (int)(cannonball.getPosition().y / 100);

		double CannonBallminX = ((double)cannonball.getPosition().x - 15);
		double CannonBallmaxX = ((double)cannonball.getPosition().x + 15);
		double CannonBallminY = ((double)cannonball.getPosition().y - 15);
		double CannonBallmaxY = ((double)cannonball.getPosition().y + 15);
			


		for (int k = -1; k < 2; k++)
		{
			for (int j = -1; j < 2; j++)
			{
				//system("CLS");
				//std::cout << cannonball.blockX << "   " << cannonball.blockY << std::endl;

				// Do not check tankRadiiCollision[1][1] as this is the imaginary block the tank is on 
				if (k != 0 || j  != 1)
				{

					// Is there anything occupying the blocks that the tank radii is colliding with. If so chek OBB_AABB
					if (mapBlock[(blockY)+k][(blockX + j)])
						//if (mapBlock[(cannonball.blockY)][( cannonball.blockX)])
					{
						int mapObjectminX = ((j + blockX) * 100);
						int mapObjectMaxX = (mapObjectminX + 100);
						int mapObjectminY = ((k + blockY) * 100);
						int mapObjectMaxY = (mapObjectminY + 100);




						// AABB Collision checks
						if (CannonBallmaxX < mapObjectminX)
						{
							//return 0;
						}
						else if (CannonBallminX > mapObjectMaxX)
						{
							//return 0;
						}
						else if (CannonBallmaxY < mapObjectminY)
						{
							//return 0;
						}
						else if (CannonBallminY > mapObjectMaxY)
						{
							//return 0;
						}
						else
						{
							return 1;
						}

						//// AABB Collision checks
						//if (CannonBallmaxX < mapObjectminX)
						//{std::cout << "0 ";}
						//else if (CannonBallminX > mapObjectMaxX)
						//{std::cout << "0 ";}
						//else if (CannonBallmaxY < mapObjectminY)
						//{std::cout << "0 ";}
						//else if (CannonBallminY > mapObjectMaxY)
						//{std::cout << "0 ";}
						//else
						//{std::cout << "1 ";}
						//std::cout << CannonBallminY << "    " << mapObjectMaxY  << std::endl;
						//std::cout <<  mapObjectminY << "    " << CannonBallmaxY;

						//std::cout << mapObjectminX << "    " << CannonBallmaxX << std::endl;
						//std::cout << CannonBallminX << "    " << mapObjectMaxX << std::endl;

					}
					//else
					//{ std::cout << "0" ;}

				}

			}
			//std::cout << std::endl;

		}
		//std::cout << CannonBallminX << "    " << CannonBallmaxX;
		//sssstd::cout << std::endl;

		//system("CLS");
		return false;
	}