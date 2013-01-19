#pragma once

#include "stdafx.h"
#include "World.h"
#include "AssetManager.h"
#include <Box2D\Box2D.h>
#include "Physics.h"
#include <SFML\Graphics.hpp>
#include "BackgroundTexture.h"

World::World()
{
	// Create the world.
	b2Vec2 gravity(0.0, GRAVITY);
	world = new b2World(gravity);

	// This will handle the collisions between objects in the world.
	contactListener = new ContactListener();
	world->SetContactListener(contactListener);

	// These are used to keep track of where the veiwport should be pointing to:
	xOffset = 0;
	yOffset = 0;

	// Load a test level for now.
	loadTestLevel();

	// Hacky hacky:
	AssetManager::getAssetManager()->setWorld(this);
}


void World::init()
{
}

void World::loadTestLevel()
{
	string filename = "images/testBG2.png";
	backgroundTextures.push_back(new BackgroundTexture(filename, 0.2));
	filename = "images/testBG.png";
	backgroundTextures.push_back(new BackgroundTexture(filename, 0.6));
	filename = "images/testBG1.png";
	backgroundTextures.push_back(new BackgroundTexture(filename, 1.0));
	//Physics::createRectBody(world, -100, 200, 10000000, 100, false);
	//Physics::createRectBody(world, -100, 300, 10000000, 100, false);
	//Physics::createRectBody(world, -100, 500, 10000000, 100, false);
	//Physics::createRectBody(world, -100, 1000, 10000000, 100, false);
	//Physics::createRectBody(world, 10000, 1500, 10000, 100, false);
	//Physics::createRectBody(world, 20000, 1900, 10000, 100, false);
	//Physics::createRectBody(world, 30000, 5000, 10000, 100, false);
	//Physics::createRectBody(world, 400, 0, 100, 100, true);


	//Physics::createRectBody(world, 10100, 0, 100, 900, false);


}


void World::update()
{
	for(unsigned int i = 0; i < backgroundTextures.size(); i++)
	{
		backgroundTextures.at(i)->Update();
	}
	for(unsigned int i = 0; i < bots.size(); i++)
	{
		bots.at(i)->Update();
	}

}

void World::drawWorld(sf::RenderWindow *window)
{
	for(unsigned int i = 0; i < backgroundTextures.size(); i++)
	{
		window->draw( ((sf::Sprite)(*(backgroundTextures.at(i)))) );
	}

}

