#include "TestBot.h"
#include "AssetManager.h"

TestBot::TestBot(AnimatedSprite *sprite) : Bot(sprite)
{
	player = AssetManager::getAssetManager()->getPlayer();
	homePoint = sprite->getBody()->GetPosition().x * SCALE;
}

void TestBot::Patrol()
{
	b2Body *body = sprite->getBody();
	float x = body->GetPosition().x * SCALE;
	float dx = x - homePoint;

		if(body->GetLinearVelocity().x < 0)
		{
			if(dx > -200)
				body->ApplyForce(b2Vec2(-40,-100), body->GetPosition());
			else 
				body->ApplyForce(b2Vec2(60,-100), body->GetPosition());

		}
		else
		{
			if(dx < 200)
				body->ApplyForce(b2Vec2(40,-100), body->GetPosition());
			else 
				body->ApplyForce(b2Vec2(-60,-100), body->GetPosition());
		}
	
}

void TestBot::Chase() {};
	void TestBot::Attack() {};
	void TestBot::Run() {};

void TestBot::PatrolThink()
{

}
	void TestBot::ChaseThink()  {};
	void TestBot::AttackThink() {};
	void TestBot::RunThink()  {};