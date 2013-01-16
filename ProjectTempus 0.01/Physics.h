#pragma once
#include <Box2D\Box2D.h>
#include "World.h"

#define SCALE 30.0
#define MAX_SPEED 20.0
#define X_ACCEL 500.0
#define JUMP_SPEED 25.0
#define GRAVITY 72.8


class Physics
{
	private :
        float32 timeStep;
        int32 velocityIterations;
        int32 positionIterations;

	public:
		Physics();
		static b2Body* createRectBody(b2World* world, float x, float y, float w, float h, bool dyn);
		static b2Fixture* addRectFixture(b2Body* body, float x, float y, float w, float h);
		static void setFilterData(b2Body* body, int catBits, int maskBits, int groupBits);

		void init();
		void update(World *world);

};
