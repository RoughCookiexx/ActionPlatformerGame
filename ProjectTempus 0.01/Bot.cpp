#include "Bot.h"

Bot::Bot(AnimatedSprite *sprite, BotState state)
{
	this->sprite = sprite;
	this->state = state;
}

void Bot::Update()
{
	Think();
	Act();
}

void Bot::Think()
{
	switch(state)
	{
		case PATROL:
			PatrolThink();
			break;
		case CHASE:
			ChaseThink();
			break;
		case ATTACK:
			AttackThink();
			break;
		case RUN:
			RunThink();
			break;
		default:
			break; //how?
	}
}

void Bot::Act()
{
	switch(state)
	{
		case PATROL:
			Patrol();
			break;
		case CHASE:
			Chase();
			break;
		case ATTACK:
			Attack();
			break;
		case RUN:
			Run();
			break;
		default:
			break; //how?
	}
}
