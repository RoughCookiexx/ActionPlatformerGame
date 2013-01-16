#include "SpriteManager.h"
#include <iostream>
#include <fstream>
#include "Game.h"
#include "SFML\System.hpp"
#include "AssetManager.h"
#include "World.h"


SpriteManager::SpriteManager()
{

}

void SpriteManager::init(b2World *world)
{
	// Read the setup file and load all the sprites:
	addSpritesFromFile( "data/SpriteMap.txt", world);

	createTimeBullet(world);
	groundBody = Physics::createRectBody(world, 0, 600, 30000, 100, false);
}

void SpriteManager::createTimeBullet(b2World *world)
{
	b2Vec2 *offset = new b2Vec2(0,0);
	SpriteSheetData *data = new SpriteSheetData();
			data->numOfActions = 1;
			data->framesInAction = new int[1];
			data->framesInAction[0] = 10;
			data->drawHeight = 50;
			data->drawWidth = 50;
			data->type = NEUTRAL;
			data->timeBetweenFrames = 1/16;

	b2Body *body = Physics::createRectBody(world, 200, 200, 50, 50, true);
	sf::Texture *texture = new sf::Texture();
	texture->loadFromFile("images/testimage.png");

	AnimatedSprite* timeBulletSprite = new AnimatedSprite(*data, *texture, body);

	timeBullet = new Projectile(timeBulletSprite, player, *offset);

	// Add the sprite to the sprite list so it gets drawn:
	addSprite(timeBullet->getSprite());

	// Add the time bullet to the asset manager so it's easier to find later:
	AssetManager::getAssetManager()->setTimeBullet(timeBullet);

}

//	THIS IS LONG AND UGLY. READ THROUGH THIS AND SEE IF THERE'S A BETTER WAY. 
// should be in a separate "FileLoader" class I think.
void SpriteManager::addSpritesFromFile(string fileString, b2World *world)
{
	ifstream spriteSheetFile;
	spriteSheetFile.open(fileString);

	if (spriteSheetFile.is_open()) {
		while (!spriteSheetFile.eof()) {
			
				// First line is the file name for the Sprite Sheet:
			string SSFileName = "";
			getline(spriteSheetFile, SSFileName);

				// Then the type of sprite:
			string spriteType = "";
			getline(spriteSheetFile, spriteType);

				// Next is the number of actions:
			string numOfActionsStr = "";
			getline(spriteSheetFile, numOfActionsStr);
			int numOfActions = stoi(numOfActionsStr);

				// Then Width:
			string widthStr; 
			getline(spriteSheetFile, widthStr);
			int width = stoi(widthStr);

				// ..Height:
			string heightStr;
			getline(spriteSheetFile, heightStr);
			int height = stoi(heightStr);

				// Then a number of integers each representing number of frames per action:
			string numOfFramesStr;
			getline(spriteSheetFile, numOfFramesStr);
				// Split this line by the commas:
			Tokenizer *t = new Tokenizer();
			vector<string> numOfFramesVec = t->Split(numOfFramesStr, ',');
				// Turn the strings into integers:
			int *numOfFrames = new int[numOfActions];
			for(int i = 0; i < numOfActions; i++)
			{
				numOfFrames[i] = stoi(numOfFramesVec.at(i));
			}

				// How often should we change frames?
			string fpsStr;
			getline(spriteSheetFile, fpsStr);
			int fps = stoi(fpsStr);

				// Load Texture file:
			sf::Texture *texture = new sf::Texture();
			texture->loadFromFile(SSFileName);
			//if(!texture->create(width, height))
			//	printf("");

				// Create sprite sheet data:
			SpriteSheetData spriteSheetData;
			spriteSheetData.numOfActions = numOfActions;
			spriteSheetData.framesInAction = numOfFrames;
			spriteSheetData.drawWidth = width;
			spriteSheetData.drawHeight = height;
			spriteSheetData.timeBetweenFrames = (1.0/fps);

				// Make a physics body:
			b2Body *body = Physics::createRectBody(world, 300, 0, width, height, true);

				// Create Sprite and apply texture:
			AnimatedSprite *sprite = new AnimatedSprite(spriteSheetData, *texture, body);		


				// This is where we retrieve the player sprite for the asset manager:
			if(spriteType == "PLAYER")
			{
				player = sprite; 
				body->SetFixedRotation(true);
				//body->SetGravityScale(0);

				// This is used to see if the player is touching the ground to see if they can jump
				player->setFootSensor(Physics::addRectFixture(body, 2, 2,
					body->GetPosition().x + width/2, 
					body->GetPosition().y + height+1));
				player->getFootSensor()->SetUserData((void*)3);

				//Physics::setFilterData(body, 0x0004, 0x0002, 0x0008);

				AssetManager::getAssetManager()->setPlayer(player);
			}

				// Add the Sprite:
			addSprite(sprite);
			
			getline(spriteSheetFile, SSFileName);	// Just throw away the line - It's white space.
		}
	}
	spriteSheetFile.close();
	
}


void SpriteManager::addSprite(AnimatedSprite* sprite)
{
	if(sprite->spriteSheetData.type == PLAYER)
		player = sprite;
	else if(sprite->spriteSheetData.type == NEUTRAL)
		neutralSprites.push_back(sprite);
}


void SpriteManager::drawSprites(sf::RenderWindow *window)
{

	player->update();
	window->draw( ((sf::Sprite)(*(player))) ); 
	float xPos = groundBody->GetPosition().x;
	float yPos = groundBody->GetPosition().y;
	float xPos1 = player->getBody()->GetPosition().x;
	float yPos1 = player->getBody()->GetPosition().y;

	for(unsigned int i=0; i < neutralSprites.size(); i++)
	{
			neutralSprites.at(i)->update();
			window->draw( ((sf::Sprite)(*(neutralSprites.at(0)))) );
	}


}
