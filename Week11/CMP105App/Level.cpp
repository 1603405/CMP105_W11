#include "Level.h"

Level::Level(sf::RenderWindow* hwnd, Input* in, GameState* gs, AudioManager* aud)
{
	window = hwnd;
	input = in;
	gameState = gs;
	audio = aud;

	//Textures
	texturePlayerTank.loadFromFile("gfx/SpriteSheet.png");
	texturePlayerTankCannon.loadFromFile("gfx/PlayerCannon.png");
	textureCannonBall.loadFromFile("gfx/CannonBall.png");

	// initialise game objects
	playerTankBase.setTexture(&texturePlayerTank);
	playerTankBase.setSize(sf::Vector2f(100, 100));
	playerTankBase.setPosition(440, 440);
	playerTankBase.setVelocity(100, 100);
	playerTankBase.setInput(input);
	playerTankBase.setOrigin(50, 50);
	playerTankBase.setRotation(0);
	playerTankBase.setAlive(1);

	playerTankCannon.setOrigin(20, 70);
	playerTankCannon.setPosition(playerTankBase.getPosition().x, playerTankBase.getPosition().y);
	playerTankCannon.setTexture(&texturePlayerTankCannon);
	playerTankCannon.setSize(sf::Vector2f(40, 90));

	collisionBox.setSize(sf::Vector2f(100, 100));
	collisionBox.setOrigin(0.f, 0.f);
	collisionBox.setFillColor(sf::Color::Black);

	// PlayerCannonBall


	for (int i = 0; i < noOfPlayerCannonBalls; i++)
	{
		playerCannonBall[i].setOrigin(15, 15);
		playerCannonBall[i].setPosition(playerTankBase.getPosition());
		playerCannonBall[i].setTexture(&textureCannonBall);
		playerCannonBall[i].setSize(sf::Vector2f(30, 30));
		playerCannonBall[i].setAlive(0);
	}

	for (int i = 0; i < noOfEnemies; i++)
	{			
		// enemyTankCannon
		enemyTankCannon[i].setOrigin(20, 70);
		enemyTankCannon[i].setPosition(850, 850);
		enemyTankCannon[i].setTexture(&texturePlayerTankCannon);
		enemyTankCannon[i].setSize(sf::Vector2f(40, 90));
		enemyTankCannon[i].setAlive(1);

		for (int j = 0; j < noOfEnemyCannonBalls; j++)
		{
			// EnemyCannonBall
			enemyCannonBall[i][j].setOrigin(15, 15);
			enemyCannonBall[i][j].setPosition(enemyTankCannon[i].getPosition());
			enemyCannonBall[i][j].setTexture(&textureCannonBall);
			enemyCannonBall[i][j].setSize(sf::Vector2f(30, 30));
			enemyCannonBall[i][j].setAlive(0);
		}
	}
	


	//Audio
	audio->addMusic("sfx/cantina.ogg", "cantina");

	//if ((enemyTankCannon[0].isAlive() || enemyTankCannon[0].isAlive() || enemyTankCannon[0].isAlive()) && playerTankBase.isAlive())
	//{// Are all enemy tanks dead or is player tank dead
	//}
	//else if (playerTankBase.isAlive())
	//{// Level won
	//}
	//else
	//{// Level failed 
	//}
}

Level::~Level()
{

}

// handle user input
void Level::handleInput(float dt, Input* in)
{

	// Level active determination, is playertank and at least one enemy tank alaive
	if (enemyTankCannon[0].isAlive())
	{
		// Update Player cannonBall
		for (int i = 0; i < noOfPlayerCannonBalls; i++)
		{playerCannonBall[i].playerInputandUpdateCannonBall(dt, in, playerTankCannon);}

	
		playerTankBase.handleInput(dt, in);

	}
}

// Update game objects
void Level::update(float dt)
{
	if (enemyTankCannon[0].isAlive())
	{
		//Update tankCannon direction and position
		playerTankCannon.updatePlayer(dt, input->getMouseX(), input->getMouseY(), playerTankBase);

		// Update playerTankBase and playerTankBasecollision
		playerTankBase.update(dt);
		playerTankWallCollision(playerTankBase, mapBlock, blockArr);

		for (int i = 0; i < noOfPlayerCannonBalls; i++)
		{
			// Update Player cannonBall
			//collision2.playerCannonBallCollision(playerCannonBall[i]);
			if (playerCannonBall[i].isAlive() && collision2.cannonBallMapCollision(playerCannonBall[i]))
			{playerCannonBall[i].setAlive(0);}
			 //std::cout<< collision2.cannonBallMapCollision(playerCannonBall[i]) << std::endl;

			//collision2.cannonBallMapCollision(playerCannonBall[i]);

			//{playerCannonBall[i].setAlive(false);}
			
		}

		// Update Enemy 
		for (int i = 0; i < noOfEnemies; i++)
		{
			// Update enemy cannon roation
			enemyTankCannon[i].updateEnemy(dt, playerTankBase);
			for (int j = 0; j < noOfEnemyCannonBalls; j++)
			{	// Update enemy cannon                                                                   
				enemyCannonBall[i][j].updateEnemyCannonBall(dt, enemyTankCannon[i]);
			}
		}


		
		


	}
}

// Render level
void Level::render()
{
	if (enemyTankCannon[0].isAlive())
	{

		beginDraw();
		// Level tileMap
		mapSet.tileMap1.render(window);

		// Player 
		playerTankBase.draw(window);		// Player with Tank collision box
		//window->draw(playerTankBase);		// Player without Tank collision box
		window->draw(playerTankCannon);		// Player Cannon

		for (int i = 0; i < noOfPlayerCannonBalls; i++)
		{
			if (playerCannonBall[i].isAlive())
			{
				playerCannonBall[i].draw(window);
			}
		}

		window->draw(collisionBox);			// Wall CollisionBox OOBB. This will help you if you are lost in the code. Lawd knows I am



		// Enemy
		for (int i = 0; i < noOfEnemies; i++)
		{
			if (enemyTankCannon[i].isAlive())		// If enemyTankCannon is alive draw it
			{window->draw(enemyTankCannon[i]);}

			for (int j = 0; j < noOfEnemyCannonBalls; j++)
			{
				if (enemyCannonBall[i][j].isAlive())// If enemyCannonBall is alive draw it
				{enemyCannonBall[i][j].draw(window);}
			}
		}
		endDraw();
	}
}

// Begins rendering to the back buffer. Background colour set to light blue.
void Level::beginDraw()
{
	window->clear(sf::Color(100, 149, 237));
}

// Ends rendering to the back buffer, and swaps buffer to the screen.
void Level::endDraw()
{
	window->display();
}



// Calculate and return angle between the positive Y axes and the displacement of the point1 -> point2
double Level::getAngle(double x1, double y1, double x2, double y2)
{

	double diffX, diffY;
	// (double) because of arethmatic overflow
	diffX = ((double)x1 - (double)x2);
	diffY = ((double)y1 - (double)y2);

	// Try not to divide by 0
	if (diffX != 0 && diffY != 0)
	{
		if (diffX > 0)
		{
			return ((atan(diffY / diffX) * (180 / 3.14)) + 90);
		}
		else
		{
			return ((atan(diffY / diffX) * (180 / 3.14)) + 270);
		}
	}
	// Incase you do try to divide by 0
	else if(diffX == 0 && diffY > 0)
	{return 180;}
	else if(diffX == 0 && diffY < 0)
	{return 0;}
	else if (diffY== 0 && diffX > 0)
	{return 90;}
	else // if (diffY== 0 && diffX < 0) One less check
	{return 270;}
}

double Level::getDifference(double x1, double y1, double x2, double y2)
{
	double diffX, diffY;
	// (double) because of arethmatic overflow
	diffX = ((double)x1 - (double)x2);
	diffY = ((double)y1 - (double)y2);

	// Please forgive me CPU for the sqrt
	return (sqrt((diffX * diffX) + (diffY * diffY)));
}


// PlayerTankWallCollision
void Level::playerTankWallCollision(Tank tank, bool  mapArr[15][20], bool radiiBlockArr[3][3])
{
	// Find the X and Y block positions of where the tank is
	int tankBlockX = (int)(tank.getPosition().x / 100);
	int tankBlockY = (int)(tank.getPosition().y / 100);

	//Find the (unasigned) difference between the within block corrdinates of the tank and the top, left, right and bottom of the block
	double tankDiffLeft = (double)tank.getPosition().x - ((double)tankBlockX * 100);
	double tankDiffRight = 100 - tankDiffLeft;
	double tankDiffTop = (double)tank.getPosition().y - ((double)tankBlockY * 100);
	double tankDiffBot = 100 - tankDiffTop;

	//Square these values once instead of squaring them in each if statement
	double tankDiffLeft2 = tankDiffLeft * tankDiffLeft;
	double tankDiffRight2 = tankDiffRight * tankDiffRight;
	double tankDiffTop2 = tankDiffTop * tankDiffTop;
	double tankDiffBot2 = tankDiffBot * tankDiffBot;

	// First collision check
	collision2.radiiCollision(tankDiffLeft2, tankDiffRight2, tankDiffTop2, tankDiffBot2, radiiBlockArr, 5000.00);
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			// Do not check tankRadiiCollision[1][1] as this is the imaginary block the tank is on 
			if (i != 1 || j != 1)
			{
				// Is there anything occupying the blocks that the tank radii is colliding with. If so chek OBB_AABB
				if (radiiBlockArr[i][j] && mapArr[(i + tankBlockY - 1)][(j + tankBlockX - 1)])
				{
					// i and j counters -1 * 100;
					// i2 represents the left and j2 represents the top coordinates of the collision box in relation to the  
					int i2 = (i - 1) * 100;
					int j2 = (j - 1) * 100;


					double originX = -j2 + tankDiffLeft;
					double originY = -i2 + tankDiffTop;

					// Set origin has to be done first
					collisionBox.setOrigin(originX, originY);
					collisionBox.setPosition(playerTankBase.getPosition());
					collisionBox.setRotation(-collision2.findRotation0_90(tank.getRotation()));

					
					//collisionBox.setRotation(tank.getRotation());


					// Values for AABB collision checks
					double tankMaxXAABB = tankDiffLeft + (tank.getGlobalBounds().width / 2);
					double tankMinXAABB = tankDiffLeft - (tank.getGlobalBounds().width / 2);
					double tankMaxYAABB = tankDiffTop + (tank.getGlobalBounds().height / 2);
					double tankMinYAABB = tankDiffTop - (tank.getGlobalBounds().height / 2);

					double blockMinXAABB = j2;
					double blockMaxXAABB = j2 + 100.0;
					double blockMinYAABB = i2;
					double blockMaxYAABB = i2 + 100.0;

					//OBB dimensions
					double tankMinXOBB = tank.getPosition().x - 50.0;
					double tankMaxXOBB = tank.getPosition().x + 50.0;
					double tankMinYOBB = tank.getPosition().y - 50.0;
					double tankMaxYOBB = tank.getPosition().y + 50.0;

					double blockMinXOBB = collisionBox.getGlobalBounds().left;
					double blockMaxXOBB = blockMinXOBB + collisionBox.getGlobalBounds().width;
					double blockMinYOBB = collisionBox.getGlobalBounds().top;
					double blockMaxYOBB = blockMinYOBB + collisionBox.getGlobalBounds().height;

					bool xFixPos = 0;
					bool yFixPos = 0;

					// AABB Collision checks
					if (tankMaxXAABB < blockMinXAABB)
					{//std::cout << "false ";}
					}else if (tankMinXAABB > blockMaxXAABB)
					{//std::cout << "false ";}
					}
					else if (tankMaxYAABB < blockMinYAABB)
					{//std::cout << "false ";}
					}else if (tankMinYAABB > blockMaxYAABB)
					{//std::cout << "false ";}
					// OBB collision checks
					}else if (tankMaxXOBB < blockMinXOBB)
					{//std::cout << "false ";}
					}else if (tankMinXOBB > blockMaxXOBB)
					{//std::cout << "false ";}
					}else if (tankMaxYOBB < blockMinYOBB)
					{//std::cout << "false ";}
					}else if (tankMinYOBB > blockMaxYOBB)
					{//std::cout << "false ";}
					}else
					{std::cout << "true ";
						
						// Is the tank colliding with object with current motion
						// Respond appropriatly, if coliding set rotation to previous safe rotation
						if (i -1)
						{
							if (i == 2 && playerTankBase.velocityY > 0 && input->isKeyDown(sf::Keyboard::W))
							{playerTankBase.velocityY = 0;}
							if (i == 2 && playerTankBase.velocityY < 0 && input->isKeyDown(sf::Keyboard::S))
							{playerTankBase.velocityY = 0;}
							if (i == 0 && playerTankBase.velocityY < 0 && input->isKeyDown(sf::Keyboard::W))
							{playerTankBase.velocityY = 0;}
							if (i == 0 && playerTankBase.velocityY > 0 && input->isKeyDown(sf::Keyboard::S))
							{playerTankBase.velocityY = 0;}
						
							playerTankBase.setRotation(playerTankBase.safeRotation);
						}
						if (j - 1)
						{
							if (j == 2 && playerTankBase.velocityX > 0 && input->isKeyDown(sf::Keyboard::W))
							{playerTankBase.velocityX = 0;}
							if (j == 2 && playerTankBase.velocityX < 0 && input->isKeyDown(sf::Keyboard::S))
							{playerTankBase.velocityX = 0;}
							if (j == 0 && playerTankBase.velocityX < 0 && input->isKeyDown(sf::Keyboard::W))
							{playerTankBase.velocityX = 0;}
							if (j == 0 && playerTankBase.velocityX > 0 && input->isKeyDown(sf::Keyboard::S))
							{playerTankBase.velocityX = 0;}

							playerTankBase.setRotation(playerTankBase.safeRotation);

						}
					}
					
					// Set current rotaiton as safe, previous if statment will revert any rotaiton is collision is true
					//playerTankBase.safeRotation = playerTankBase.getRotation();
					std::cout << std::endl;

				}
			}
		}
	}
	tank.radiiCollisionReset(radiiBlockArr);
	std::cout << tank.getRotation() << std::endl;
}


