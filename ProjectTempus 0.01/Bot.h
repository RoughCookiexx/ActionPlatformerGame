#include "AnimatedSprite.h"

#pragma once

enum BotState { PATROL, CHASE, ATTACK, RUN } ;

class Bot
{

public : 
	Bot(AnimatedSprite *sprite, BotState state = PATROL);
	void Update();
	//AnimateSprite* getSprite() { return sprite; }

private : 

	void Think();
	void Act();

protected: 
	AnimatedSprite *sprite;
	BotState state;

	virtual void Patrol() = 0;
	virtual void Chase() = 0;
	virtual void Attack() = 0;
	virtual void Run() = 0;
	virtual void PatrolThink() = 0;
	virtual void ChaseThink() = 0;
	virtual void AttackThink() = 0;
	virtual void RunThink() = 0;
};