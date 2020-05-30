#include "MapSet.h"


MapSet::MapSet()
{
	// Loads and stores the spritesheet containing all the tiles required to build the level/section
	tileMap1.loadTexture("gfx/basicBoxes.png");
	tileMap2.loadTexture("gfx/basicBoxes.png");

	GameObject tile;
	std::vector<GameObject> tiles;
	for (int i = 0; i < 3; i++)
	{
		tile.setSize(sf::Vector2f(*tileSize, *tileSize));
		tile.setCollisionBox(0, 0, *tileSize, *tileSize);
		tile.setCollider(true);
		tiles.push_back(tile);
	}
	tiles[0].setCollider(false);
	tiles[0].setTextureRect(sf::IntRect(0, 0, 48, 48));
	tiles[1].setTextureRect(sf::IntRect(48, 0, 48, 48));
	tiles[2].setTextureRect(sf::IntRect(96, 0, 48, 48));

	//Map 1
	tileMap1.setTileSet(tiles);
	// Map dimensions
	sf::Vector2u mapSize1(20, 15);
	// build map
	std::vector<int> map1 = {
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


	tileMap1.setTileMap(map1, mapSize1);
	tileMap1.setPosition(sf::Vector2f(0, 0));
	tileMap1.buildLevel();




/*
	//Level 2
	tileMap2.setTileSet(tiles);
	// Map dimensions
	sf::Vector2u mapSize2(10, 6);
	// build map
	std::vector<int> map2 = {
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 1, 3, 0, 0, 0, 0, 0,
	1, 2, 3, 4, 6, 1, 2, 3, 0, 0,
	4, 5, 6, 0, 0, 4, 5, 6, 0, 0
	};
	tileMap2.setTileMap(map2, mapSize2);
	tileMap2.setPosition(sf::Vector2f(200, 200));
	tileMap2.buildLevel();
*/
}


// Uses window pointer to render level/section. Tile by Tile.
void MapSet::renderMap1(sf::RenderWindow* window)
{
	tileMap1.render(window);
}
