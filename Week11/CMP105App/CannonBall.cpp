#include "CannonBall.h"

// Defalt constructor
CannonBall::CannonBall()
{
	wait.setFrameSpeed(animationSpeed);
	wait.addFrame(sf::IntRect(0, 0, 10, 10));
	currentAnimation = &wait;
	setTextureRect(currentAnimation->getCurrentFrame());
}

// Defalt deconstructor
CannonBall::~CannonBall()
{}

// CannonBall draw
void CannonBall::draw(sf::RenderWindow* window)
{
	
	window->draw(*this);

}


// CannonBall updateEnemy
void CannonBall::updateEnemyCannonBall(float dt, Cannon enemyCannon)
{

	if ((int)enemyCannonBallTimer.getElapsedTime().asSeconds() == 2 && !isAlive())
	{
		enemyCannonBallTimer.restart();

		setRotation(enemyCannon.getRotation());
		calVelocity(cannonBallVelocity);
		setPosition((enemyCannon.getPosition().x + 70 * (velocityX / cannonBallVelocity)),
					(enemyCannon.getPosition().y + 70 * (velocityY / cannonBallVelocity)));
		setAlive(1);
		
		
	}
	if (isAlive())
	{
		move(sf::Vector2f(velocityX, velocityY) * dt);
	}
}

// CannonBall handleInputPlayer
void CannonBall::playerInputandUpdateCannonBall(float dt, Input* input, Cannon playerCannon)
{
	//std::cout << playerCannonBallTimer.getElapsedTime().asSeconds() << std::endl;

	if (input->isKeyDown(sf::Keyboard::Space) && !isAlive() && (int)playerCannonBallTimer.getElapsedTime().asSeconds() > 2 )
	{
		setRotation(playerCannon.getRotation());
		calVelocity(cannonBallVelocity);
		setPosition((playerCannon.getPosition().x + 70*(velocityX / cannonBallVelocity)), 
					(playerCannon.getPosition().y + 70*(velocityY / cannonBallVelocity)));

		// Reset playerCannonBallTimer
		playerCannonBallTimer.restart();

		setAlive(1);

	}
	if (isAlive())
	{
		move(sf::Vector2f(velocityX, velocityY) * dt);

	}

	if (input->isKeyDown(sf::Keyboard::LShift))
	{
		setAlive(0);
	}
}


