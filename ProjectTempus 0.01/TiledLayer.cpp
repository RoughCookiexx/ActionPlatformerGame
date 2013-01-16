#include "TiledLayer.h"

#include <iostream>
#include <fstream>

TiledLayer::TiledLayer(b2World *world, int widthOfTile, int heightOfTile)
{
	tileWidth = widthOfTile;
	tileHeight = heightOfTile;

	LoadTiledLayerFromFile("data/LevelOneMap.csv", world);
}


void TiledLayer::LoadTiledLayerFromFile(string fileName, b2World *world)
{
	ifstream tiledLayerFile;
	tiledLayerFile.open(fileName);

	int lineNumber = 0;
	
			sf::Texture *texture = new sf::Texture();
			texture->loadFromFile("images/tile.png");


	if (tiledLayerFile.is_open()) {
		while (!tiledLayerFile.eof()) {



			string line;			
			getline(tiledLayerFile, line);
			
			if(!line.empty())
			{
				Tokenizer *t = new Tokenizer();
				vector<string> tileStrings = t->Split(line, ',');

				for(int i = 0; i < tileStrings.size(); i++)
				{
					int tileID = stoi(tileStrings.at(i));

					switch(tileID)
					{
						case 1:
							Tile tile;
								tile.x = i * tileWidth;
								tile.y = lineNumber * tileHeight;

							sf::Sprite *sprite = new sf::Sprite();
								sprite->setTexture(*texture);
								sprite->setPosition(tile.x, tile.y);
							tile.sprite = sprite;
				
							tile.body = Physics::createRectBody(world, 
								tile.x, tile.y, 
								tileWidth, tileHeight, 
								false);

							tiles.push_back(tile);
							break;
					
						//default: ;
					}
				}

			}
			lineNumber++;
		}
	}
}

void TiledLayer::draw(sf::RenderWindow *window)
{
	for(int i = 0; i < tiles.size(); i++)
	{
		int x = tiles.at(i).body->GetPosition().x * SCALE;
		int y = tiles.at(i).body->GetPosition().y * SCALE;
		tiles.at(i).sprite->setPosition(x, y);
			window->draw( (sf::Sprite)*tiles.at(i).sprite ) ;
	}
}