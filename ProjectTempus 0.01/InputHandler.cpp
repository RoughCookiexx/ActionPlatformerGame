#include "InputHandler.h"
#include "ContactListener.h"
#include "AssetManager.h"

InputHandler::InputHandler()
{

}

void InputHandler::handleInput(World *world, Graphics *graphics)
{

	AssetManager *assetManager = AssetManager::getAssetManager();
	AnimatedSprite *player = assetManager->getPlayer();
			b2Body *body = player->getBody();
			b2Vec2 velocity = body->GetLinearVelocity();




	// PLAYER MOVEMENT:
		//	=============================================
			
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		body->SetTransform(b2Vec2(300/SCALE,300/SCALE), 0);
	}
	// GO RIGHT
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
			player->setAction(1);
			if(player->getFacing() != RIGHT)
			{
				player->setFacing(RIGHT);
				player->scale(-1.0, 1.0);
			}
			
			double xVel = body->GetLinearVelocity().x;
			if(xVel < MAX_SPEED)
			{
				if(xVel < 0)
					body->ApplyForce(b2Vec2(2*(X_ACCEL), 0.0f), body->GetPosition());
				else
					body->ApplyForce(b2Vec2((X_ACCEL), 0.0f), body->GetPosition());
			}
	}

	// GO LEFT
	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
			player->setAction(1);
			if(player->getFacing() != LEFT)
			{
				player->setFacing(LEFT);
				player->scale(-1.0, 1.0);
			}

			double xVel = body->GetLinearVelocity().x;
			if(xVel > MAX_SPEED*-1)
			{
				if(xVel > 0)
					body->ApplyForce(b2Vec2(2*(X_ACCEL*-1), 0.0f), body->GetPosition());
				else
					body->ApplyForce(b2Vec2((X_ACCEL*-1), 0.0f), body->GetPosition());
			}
	}

	// DON'T GO
	else
	{
		player->setAction(0);
	}
		//	=============================================




	// ******** JUMP **********
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		ContactListener *contactListener = world->getContactListener();

		// this checks to see if your feet are on the ground.
/*		if(contactListener->getNumFootContacts() > 0 
			&& contactListener->getJumpTimer() == 0)
		{
			body->SetLinearVelocity(b2Vec2(velocity.x, velocity.y - JUMP_SPEED));
			contactListener->startJumpTimer();
		}*/
	}



	// ******** FIRE WEAPON **********
	if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
	{
		b2Vec2 clickPoint = *(new b2Vec2());
		clickPoint.x = sf::Mouse::getPosition(*(graphics->getWindow())).x;
		clickPoint.y = sf::Mouse::getPosition(*(graphics->getWindow())).y;

		assetManager->getTimeBullet()->Fire(clickPoint);
	}
}