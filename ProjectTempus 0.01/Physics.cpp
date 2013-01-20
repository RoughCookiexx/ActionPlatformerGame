#include "stdafx.h"
#include "Physics.h"
#include "World.h"
#include "ContactListener.h"
#include <Box2D\Box2D.h>


Physics::Physics()
{
	// Initialize some b2d variables:
	timeStep = 1.0f / 60.0f;
	velocityIterations = 40;
    positionIterations = 40;
}

void Physics::init()
{

}

void Physics::update(World *world)
{
	// Tell b2d to update:
	world->getB2World()->Step(timeStep, 
								velocityIterations, 
								positionIterations);

	// Draw the world:
	//world->getB2World()->DrawDebugData();
}


// Add a fixture to an existing body:
b2Fixture* Physics::addRectFixture(b2Body* body, float x, float y, float w, float h)
{
	b2Fixture *fixture;
      b2PolygonShape *shape = new b2PolygonShape();
      shape->SetAsBox((w/2)/SCALE
		  , (h/2)/SCALE
		  , b2Vec2(x/SCALE
		  , y/SCALE
		  ), 0.0f);
      b2FixtureDef *def = new b2FixtureDef();
      def->shape = shape;
      def->density = 0.3;
	  def->isSensor = true;
	 fixture = body->CreateFixture(def);
	 return fixture;
}

// This simplifies adding a rectangular body to the world:
b2Body* Physics::createRectBody(b2World* world, float x, float y, float w, float h, bool dyn=false)
{
			b2BodyDef *def = new b2BodyDef();
			def->position.x = (x + w/2) / SCALE;
			def->position.y = (y + h/2) / SCALE ;
			if(dyn)
				def->type = b2_dynamicBody;
			b2Body *body = world->CreateBody(def);
			b2PolygonShape *shape = new b2PolygonShape();
			shape->SetAsBox((w/2)/SCALE,
				(h/2)/SCALE);

			b2FixtureDef *fixtureDef = new b2FixtureDef();
			fixtureDef->density = 1.0f;
			fixtureDef->shape = shape;
			fixtureDef->friction = 0.1;

			body->CreateFixture(fixtureDef);

			return body;
}


// This will set the filter data for the first fixture in a body.
// This will need to be changed or I will need something else if I use bodies with multiple fixtures.
void Physics::setFilterData(b2Body* body, int catBits, int maskBits)
{
	b2Filter *filter = new b2Filter();
	filter->categoryBits = catBits;
	filter->maskBits = maskBits;
	//filter->groupIndex = groupBits;

	b2Fixture* fixture = body->GetFixtureList();
	fixture->SetFilterData(*filter);
}