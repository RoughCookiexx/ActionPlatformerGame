#pragma once
#include <Box2D\Box2D.h>
#include <time.h>

#define TIME_BETWEEN_JUMPS 100

class ContactListener : public b2ContactListener
{

private : 
	
		 int numFootContacts;
		 float jumpTimer;

public : 
		 ContactListener::ContactListener();
		 void BeginContact(b2Contact* contact);
		 void EndContact(b2Contact* contact);

		 void startJumpTimer() { jumpTimer = (float)clock(); }
		 float getJumpTimer();
		 int getNumFootContacts() { return numFootContacts; }
};