#pragma once

#include "stdafx.h"
#include "World.h"
#include "AssetManager.h"
#include <Box2D\Box2D.h>
#include "Physics.h"
#include <SFML\Graphics.hpp>

World::World()
{
	// Create the world.
	b2Vec2 gravity(0.0f, GRAVITY);
	world = new b2World(gravity);

	// This is used right now to check when the player touches the ground.. I think.
	contactListener = new ContactListener();
	world->SetContactListener(contactListener);

	// These are used to keep track of where the veiwport should be pointing to:
	xOffset = 0;
	yOffset = 0;

	// Load a test level for now.
	loadTestLevel();
}


void World::init()
{
	AssetManager::getAssetManager()->setWorld(this);
}

void World::loadTestLevel()
{
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
	
}



