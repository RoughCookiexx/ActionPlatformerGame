#include "Bot.h"

#pragma once

class TestBot : public Bot
{

public : 
	TestBot(AnimatedSprite *sprite);

protected :
	void Patrol();
	void Chase();
	void Attack();
	void Run();
	void PatrolThink();
	void ChaseThink();
	void AttackThink();
	void RunThink();

private: 
	int homePoint;
	AnimatedSprite *player;
};