#pragma once
#include <Box2D\Box2D.h>

#define TIME_BETWEEN_JUMPS 100

class ContactListener : public b2ContactListener
{

private : 
	

public : 
		 ContactListener::ContactListener();
		 void BeginContact(b2Contact* contact);
		 void EndContact(b2Contact* contact);

		// float getJumpTimer();
};