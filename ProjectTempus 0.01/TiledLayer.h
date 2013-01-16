#include <vector>
#include "Physics.h"
#include "Tokenizer.h"
#include "SFML\Graphics.hpp"

#pragma once


struct Tile
{
	int x, y;
	b2Body *body;
	sf::Sprite *sprite;
};

using namespace std;

class TiledLayer
{
	private:
		int tileHeight, tileWidth;
		vector<Tile> tiles;

	public:
		TiledLayer(b2World *world, int widthOfTile, int heightOfTile);
		void LoadTiledLayerFromFile(string fileName, b2World *world);
		void draw(sf::RenderWindow *window);

};