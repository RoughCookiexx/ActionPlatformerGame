#include "SpriteManager.h"
#include <iostream>
#include <fstream>
#include "Game.h"
#include "SFML\System.hpp"
#include "AssetManager.h"
#include "World.h"
#include "TestBot.h"
#include "Bot.h"


SpriteManager::SpriteManager()
{

}

void SpriteManager::init(b2World *world)
{
	// Read the setup file and load all the sprites:
	addSpritesFromFile( "data/SpriteMap.txt", world);

	createTimeBullet(world);
	groundBody = Physics::createRectBody(world, 0, 600, 30000, 100, false);

	//createTestBot(world);
}

void SpriteManager::createTestBot(b2World *world)
{
	
	int framesInAction[] = {1};

	SpriteSheetData data;
	data.drawHeight = 50;
	data.drawWidth = 50;
	data.framesInAction = framesInAction;
	data.numOfActions = 1;
	data.timeBetweenFrames = 1;
	data.type = BADGUY;
	
			sf::Texture *texture = new sf::Texture();
			texture->loadFromFile("images/TestBot.png");

			b2Body *body = Physics::createRectBody(world, 10, 0, 50, 50, true);
				body->SetFixedRotation(true);

	AnimatedSprite *sprite = new AnimatedSprite(data, *texture, body);
	TestBot *testBot = new TestBot(sprite);

	addSprite(sprite);
}

// This will be gone soon.
void SpriteManager::createTimeBullet(b2World *world)
{
	b2Vec2 *offset = new b2Vec2(0,0);
	SpriteSheetData *data = new SpriteSheetData();
			data->numOfActions = 1;
			data->framesInAction = new int[1];
			data->framesInAction[0] = 10;
			data->drawHeight = 15;
			data->drawWidth = 15;
			data->type = NEUTRAL;
			data->timeBetweenFrames = 1/16;

	b2Body *body = Physics::createRectBody(world, 200, 200, 15, 15, true);
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

				// x position:
			string xStr;
			getline(spriteSheetFile, xStr);
			int x = stoi(xStr);

				// x position:
			string yStr;
			getline(spriteSheetFile, yStr);
			int y = stoi(yStr);


				// Then Width:
			string widthStr; 
			getline(spriteSheetFile, widthStr);
			int width = stoi(widthStr);

				// ..Height:
			string heightStr;
			getline(spriteSheetFile, heightStr);
			int height = stoi(heightStr);

				// Next is the number of actions:
			string numOfActionsStr = "";
			getline(spriteSheetFile, numOfActionsStr);
			int numOfActions = stoi(numOfActionsStr);
			
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
			SpriteSheetData *spriteSheetData = new SpriteSheetData();
			spriteSheetData->numOfActions = numOfActions;
			spriteSheetData->framesInAction = numOfFrames;
			spriteSheetData->drawWidth = width;
			spriteSheetData->drawHeight = height;
			spriteSheetData->timeBetweenFrames = (1.0/fps);
			
			if(spriteType == "BADGUY")
			{
				spriteSheetData->type = BADGUY;
			}

				// Make a physics body:
			b2Body *body = Physics::createRectBody(world, x, y, width, height, true);

				// Create Sprite and apply texture:
			AnimatedSprite *sprite = new AnimatedSprite(*spriteSheetData, *texture, body);		

			
				body->SetFixedRotation(true);
				// This is where we retrieve the player sprite for the asset manager:
			if(spriteType == "PLAYER")
			{
				player = sprite;

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
	else if(sprite->spriteSheetData.type == BADGUY)
	{
		badguySprites.push_back(sprite);
		Bot *bot = new TestBot(sprite);
		World *world = AssetManager::getAssetManager()->getWorld();
			world->addBot(bot);
	}
}


void SpriteManager::drawSprites(sf::RenderWindow *window)
{

	// Draw all of the neutralSprites:
	for(unsigned int i=0; i < neutralSprites.size(); i++)
	{
			neutralSprites.at(i)->update();
			window->draw( ((sf::Sprite)(*(neutralSprites.at(i)))) );
	}

	// Draw all of the bad guys:
	for(unsigned int i=0; i < badguySprites.size(); i++)
	{
			badguySprites.at(i)->update(); // Update the sprite graphics
			window->draw( ((sf::Sprite)(*(badguySprites.at(i)))) );
	}

	// Draw the player:
	player->update();
	window->draw( ((sf::Sprite)(*(player))) ); 


}
