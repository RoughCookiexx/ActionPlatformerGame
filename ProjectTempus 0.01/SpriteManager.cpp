#include "SpriteManager.h"
#include <iostream>
#include <sstream>
#include "Game.h"
#include "SFML\System.hpp"
#include "AssetManager.h"
#include "World.h"
#include "TestBot.h"
#include "Bot.h"
#include "DataLoader.h"

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

// Adds sprites from a file. derr
void SpriteManager::addSpritesFromFile(string fileString, b2World *world)
{
	std::vector<ItemInfo*> spriteInfoList;
	spriteInfoList = DataLoader::MapFileInfo(fileString);
	for(int i = 0; i < spriteInfoList.size(); i++)
	{

		// Get the info from the file:
		ItemInfo *spriteInfo = spriteInfoList.at(i);
			string textureStr = spriteInfo->sMap["Texture"];
			string typeStr = spriteInfo->sMap["Type"];
			int height = spriteInfo->iMap["Height"];
			int width = spriteInfo->iMap["Width"];
			int x = spriteInfo->iMap["X"];
			int y = spriteInfo->iMap["Y"];
			float fps = (1.0/spriteInfo->iMap["FPS"]);
			int numActions = spriteInfo->iMap["NumActions"];

		// Set up the sprite sheet data with the info taken from the file:
		SpriteSheetData *ssData = new SpriteSheetData();
			ssData->drawHeight = height;
			ssData->drawWidth = width;
			ssData->numOfActions = numActions;
			ssData->timeBetweenFrames = fps;

		// This loop adds the number of frames in each action to the SpriteSheet data:
			ssData->framesInAction = new int[numActions];
		for(int i = 0; i < numActions; i++)
		{
			std::stringstream ss;
			string framesStr = "FramesAction";
			ss << (i+1);
			framesStr += ss.str();
			ssData->framesInAction[i] = spriteInfo->iMap[framesStr];
		}

		// Now set the sprite type:
		if(typeStr == "PLAYER")	{ ssData->type = PLAYER; }
			else if (typeStr == "BADGUY") { ssData->type = BADGUY; }
			else if (typeStr == "NEUTRAL") { ssData->type = NEUTRAL; }
			else if (typeStr == "GOOD_BULLET") { ssData->type = GOOD_BULLET; }
			else if (typeStr == "BAD_BULLET") { ssData->type = BAD_BULLET; }

		// Make a physics body:
		b2Body *body = Physics::createRectBody(world, x, y, width, height, true);
				body->SetFixedRotation(true);
		
		// Load Texture file:
		sf::Texture *texture = new sf::Texture();
		texture->loadFromFile(textureStr);
		
		// Create Sprite and apply texture:
		AnimatedSprite *sprite = new AnimatedSprite(*ssData, *texture, body);	

		// This is used to see if the player is touching the ground to see if they can jump
	/*	sprite->setFootSensor(Physics::addRectFixture(body, 2, 2,
					body->GetPosition().x + width/2, 
					body->GetPosition().y + height+1));
				sprite->getFootSensor()->SetUserData((void*)3); */
		
		// Add the Sprite:
		addSprite(sprite);
	}

	/*
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
	*/
	
}




void SpriteManager::addSprite(AnimatedSprite* sprite)
{
	if(sprite->spriteSheetData.type == PLAYER)
	{
		player = sprite;
		AssetManager::getAssetManager()->setPlayer(player); // hackity hack.
		b2Body *body = player->getBody();
		float width = player->getTextureRect().width;
		float height = player->getTextureRect().height;
				player->setFootSensor(Physics::addRectFixture(body, 2, 2,
					body->GetPosition().x + width/2, 
					body->GetPosition().y + height+1));
				player->getFootSensor()->SetUserData((void*)3);
	}
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
