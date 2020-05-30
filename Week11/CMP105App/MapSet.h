#pragma once
#include "Framework/TileMap.h"
#include <iostream>

class MapSet : public TileMap
{
public:

	//Defalt Constructor
	MapSet();

	//TileMap object
	TileMap tileMap1;
	TileMap tileMap2;

	int* tileSize = new int(100);
	// Uses window pointer to render level/section. Tile by Tile.
	void renderMap1(sf::RenderWindow* window);

private:

};

