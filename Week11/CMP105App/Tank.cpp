#include "Tank.h"

// Defalt constructor
Tank::Tank()
{
	// Animation speed
	wait.setFrameSpeed(animationSpeed);
	forward.setFrameSpeed(animationSpeed);
	back.setFrameSpeed(animationSpeed);
	left.setFrameSpeed(animationSpeed);
	right.setFrameSpeed(animationSpeed);
	forwardLeft.setFrameSpeed(animationSpeed);
	forwardRight.setFrameSpeed(animationSpeed);
	backLeft.setFrameSpeed(animationSpeed);
	backRight.setFrameSpeed(animationSpeed);

	// Add frames for wait
	wait.addFrame(sf::IntRect(0, 0, 147, 164));

	// The same spritesheet tiles are used for forward and backwards motion
	// Add frames for forward motion
	for (int i = 0; i < 2646; i += 147)
	{
		forward.addFrame(sf::IntRect(i, 164, 147, 164));
		forwardLeft.addFrame(sf::IntRect(i, 328, 147, 164));
		forwardRight.addFrame(sf::IntRect(i, 492, 147, 164));
		left.addFrame(sf::IntRect(i, 656, 147, 164));
	}
	// Add frames for backwards motion
	for (int i = 2499; i > 0; i -= 147)
	{
		back.addFrame(sf::IntRect(i, 164, 147, 164));
		backLeft.addFrame(sf::IntRect(i, 328, 147, 164));
		backRight.addFrame(sf::IntRect(i, 492, 147, 164));
		right.addFrame(sf::IntRect(i, 656, 147, 164));
	}

	currentAnimation = &wait;
	setTextureRect(currentAnimation->getCurrentFrame());

	hitRadii.setRadius(70.71);
	hitRadii.setFillColor(sf::Color::Transparent);
	hitRadii.setOutlineThickness(1.f);
	hitRadii.setOutlineColor(sf::Color::Magenta);


	safeRotation = getRotation();
}

// Defalt deconstructor
Tank::~Tank()
{

}

// Tank draw
void Tank::draw(sf::RenderWindow* window)
{
	window->draw(*this);		//"*this" is a pointer to the object that preceds the member function (draw())
	window->draw(hitRadii);
}

// Tank update
void Tank::update(float dt)
{
	calVelocity(tankVelocity);
	hitRadii.setPosition((getPosition().x - 70.71), (getPosition().y - 70.71));
}

// Tank handleInput
void Tank::handleInput(float dt, Input* in)
{
	animation(dt, in);
	motion(dt, in);
}

// Velocity X Y calculations
void Tank::calVelocity(int velocity)
{
	// Which quadrent is playerTankBaseis facing
	if (getRotation() >= 0 && getRotation() < 90)
	{
		// Still couldn't figure out if there is a function that returned values in degrees
		velocityX = sin(getRotation() * (3.14 / 180)) * velocity;
		velocityY = -cos(getRotation() * (3.14 / 180)) * velocity;
	}
	else if (getRotation() >= 90 && getRotation() < 180)
	{
		velocityX = cos(((double)getRotation() - 90) * (3.14 / 180)) * velocity;
		velocityY = sin(((double)getRotation()-90) * (3.14 / 180)) * velocity;
	}
	else if (getRotation() >= 180 && getRotation() < 270)
	{
		velocityX = -sin(((double)getRotation() - 180) * (3.14 / 180)) * velocity;
		velocityY = cos(((double)getRotation() - 180) * (3.14 / 180)) * velocity;
	}
	else if (getRotation() >= 270 && getRotation() < 360)
	{
		velocityX = -cos(((double)getRotation() - 270) * (3.14 / 180)) * velocity;
		velocityY = -sin(((double)getRotation() - 270) * (3.14 / 180)) * velocity;
	}
}

void Tank::motion(float dt, Input* input)
{
	if (input->isKeyDown(sf::Keyboard::W))
	{
		// Moves tank forward
		move(sf::Vector2f(velocityX, velocityY) * dt);
	}
	if (input->isKeyDown(sf::Keyboard::S))
	{
		// Moves tank backwards
		move(sf::Vector2f(-velocityX, -velocityY) * dt);
	}
	if (input->isKeyDown(sf::Keyboard::D))
	{
		//Rotate right
		rotate(turningRate * dt);
	}
	if (input->isKeyDown(sf::Keyboard::A))
	{
		//Rotate left
		rotate(-turningRate * dt);
	}
}

void Tank::animation(float dt, Input* input)
{
	currentAnimation->animate(dt);
	setTextureRect(currentAnimation->getCurrentFrame());

	// Only forward
	if (input->isKeyDown(sf::Keyboard::W) && !input->isKeyDown(sf::Keyboard::A) && !input->isKeyDown(sf::Keyboard::D))
	{currentAnimation = &forward;
	setTextureRect(currentAnimation->getCurrentFrame());}
	
	// Only back
	else if (input->isKeyDown(sf::Keyboard::S) && !input->isKeyDown(sf::Keyboard::A) && !input->isKeyDown(sf::Keyboard::D))
	{currentAnimation = &back;
	setTextureRect(currentAnimation->getCurrentFrame());}

	// Only left
	else if (input->isKeyDown(sf::Keyboard::A) && !input->isKeyDown(sf::Keyboard::W) && !input->isKeyDown(sf::Keyboard::S))
	{currentAnimation = &left;
	setTextureRect(currentAnimation->getCurrentFrame());}
	
	// Only right
	else if (input->isKeyDown(sf::Keyboard::D)&& !input->isKeyDown(sf::Keyboard::W) && !input->isKeyDown(sf::Keyboard::S))
	{currentAnimation = &right;
	setTextureRect(currentAnimation->getCurrentFrame());}
	
	// Forward left
	else if (input->isKeyDown(sf::Keyboard::W) && input->isKeyDown(sf::Keyboard::A))
	{currentAnimation = &forwardLeft;
	setTextureRect(currentAnimation->getCurrentFrame());}

	// Forward right
	else if (input->isKeyDown(sf::Keyboard::W) && input->isKeyDown(sf::Keyboard::D))
	{currentAnimation = &forwardRight;
	setTextureRect(currentAnimation->getCurrentFrame());}

	// Back left
	else if (input->isKeyDown(sf::Keyboard::S) && input->isKeyDown(sf::Keyboard::A))
	{currentAnimation = &backRight;
	setTextureRect(currentAnimation->getCurrentFrame());}

	// Back right
	else if (input->isKeyDown(sf::Keyboard::S) && input->isKeyDown(sf::Keyboard::D))
	{currentAnimation = &backLeft;
	setTextureRect(currentAnimation->getCurrentFrame());}
	
	// Wait if nothing is pressed
	else
	{currentAnimation = &wait;
	setTextureRect(currentAnimation->getCurrentFrame());} 

	/*
	// Reset input associated variables
	forward	= 0;
	back	= 0;
	Left	= 0;
	right	= 0;


	// Set associated variables
	// Forward and back
	if (input->isKeyDown(sf::Keyboard::W))		// Is W being pressed
	{	
		if (input->isKeyDown(sf::Keyboard::S))	// Is W and S being pressed
		{ } // Do nothing		

		else
		{	
			keyCount++;			// Incrament number of arroy key being pressed wihtout interuption
			forward = true;		// Set forward movement to true
		}	
	}
	else if (input->isKeyDown(sf::Keyboard::S))
	{
		keyCount++;				// Incrament number of arroy key being pressed wihtout interuption
		back = true;			// Set back movement to true
	}

	// Left and right
	if (input->isKeyDown(sf::Keyboard::D))		// Is D being pressed
	{
		if (input->isKeyDown(sf::Keyboard::A))	// Is D and A being pressed
		{ } // Do nothing		

		else
		{
			keyCount++;			// Incrament number of arroy key being pressed wihtout interuption
			right = true;		// Set forward movement to true
		}
	}
	else if (input->isKeyDown(sf::Keyboard::A))
	{
		keyCount++;				// Incrament number of arroy key being pressed wihtout interuption
		left = true;			// Set back movement to true
	}


	*/

}

// Calculate and return angle between the positive Y axes and the displacement of the point1 -> point2 
double Tank::getAngle(double x1, double y1, double x2, double y2)
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
	else if (diffX == 0 && diffY > 0)
	{
		return 180;
	}
	else if (diffX == 0 && diffY < 0)
	{
		return 0;
	}
	else if (diffY == 0 && diffX > 0)
	{
		return 90;
	}
	else // if (diffY== 0 && diffX < 0) One less check
	{
		return 270;
	}
}


void Tank::radiiCollisionReset(bool arr[3][3])
{
	for (int a = 0; a < 3; a++)
	{
		for (int b = 0; b < 3; b++)
		{
			arr[a][b] = 0;
		}
	}
}
