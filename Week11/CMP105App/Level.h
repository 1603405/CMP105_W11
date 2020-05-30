#pragma once

#include <SFML/Graphics.hpp>
#include "Framework/Input.h"
#include "Framework/AudioManager.h"
#include "Framework/GameState.h"
#include "Cannon.h"
#include <string>
#include <iostream>
#include "Tank.h"
#include "MapSet.h"
#include "Framework/Collision.h"
#include "CannonBall.h"
#include "Collision2.h"


class Level{
public:
	Level(sf::RenderWindow* hwnd, Input* in, GameState* gs, AudioManager* aud);
	~Level();
	
	void handleInput(float dt, Input* in);
	void update(float dt);
	void render();
	
	// Returns angle between two points 
	double getAngle(double x1, double y1, double x2, double y2);

	// Returns distance between two points 
	double getDifference(double x1, double y1, double x2, double y2);



	private:
	// Default functions for rendering to the screen.
	void beginDraw();
	void endDraw();

	// Default variables for level class.
	sf::RenderWindow* window;
	Input* input;
	GameState* gameState;
	AudioManager* audio;

	// Overall wall tank collision function
	void playerTankWallCollision(Tank tank, bool  mapArr[15][20], bool radiiBlockArr[3][3]);
	
	// Created actors
	Tank playerTankBase;
	Cannon playerTankCannon;
	CannonBall playerCannonBall[3];
	
	Cannon enemyTankCannon[3];
	CannonBall enemyCannonBall[3][3];

	//Textures
	sf::Texture texturePlayerTank;
	sf::Texture texturePlayerTankCannon;
	sf::Texture textureCannonBall;

	sf::Clock timeKeep;



	// Player attack rate and noOfCannonBalls
	//int playerFireRate = 3;
	int noOfPlayerCannonBalls = 1;

	// No of Enemies, cannon balls and their attack rate  
	int noOfEnemies = 1;
	int noOfEnemyCannonBalls = 1;

	// Map Stuff
	MapSet mapSet;	//mapSet instance to simply access MapSet variables

	// Collision Stuff
	// Instance of collision
	Collision2 collision2;

	// This will act as an imagenary object, if the tank radii overlaps with one of the 8 surrounding blocks and that block has a physical object
	// this GameObject instance will be positioned into place
	GameObject collisionBox;

	// blockArr is a bool array that will be true if the blockArr[x][y] surrounding the tank pos blockArr[1][1] is collding with tank radii.
	bool blockArr[3][3] = {0, 0, 0,		0, 0, 0,	0, 0, 0 };

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

};