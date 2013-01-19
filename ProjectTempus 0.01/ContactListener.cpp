#include "ContactListener.h"
#include "SFML\System.hpp"

	ContactListener::ContactListener() : b2ContactListener()
	{
		ContactListener::numFootContacts = 0;
		jumpTimer = 0;
	}

	void ContactListener::BeginContact(b2Contact* contact) {

          //check if fixture A was the foot sensor
          void* fixtureUserData = contact->GetFixtureA()->GetUserData();
          if ( (int)fixtureUserData == 3 )
               numFootContacts++;
          //check if fixture B was the foot sensor
          fixtureUserData = contact->GetFixtureB()->GetUserData();
          if ( (int)fixtureUserData == 3 )
              numFootContacts++;
      }
  
      void ContactListener::EndContact(b2Contact* contact) {

          //check if fixture A was the foot sensor
          void* fixtureUserData = contact->GetFixtureA()->GetUserData();
          if ( (int)fixtureUserData == 3 )
              numFootContacts--;
		  else if( (int)fixtureUserData == 0 )
			  ;//ignore
          //check if fixture B was the foot sensor
          fixtureUserData = contact->GetFixtureB()->GetUserData();
          if ( (int)fixtureUserData == 3 )
              numFootContacts--;
		  else if( (int)fixtureUserData == 0 )
			  ;//ignore
      }

	  float ContactListener::getJumpTimer()
	  {
		  if ((TIME_BETWEEN_JUMPS + jumpTimer) < clock() )
			jumpTimer = 0;

		  return jumpTimer;
	  }