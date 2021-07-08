#pragma once

#include "Entity.h"
#include "EntityState.h"

class cEntityGrevertIdleState : public cEntityState
{
public:

	cEntityGrevertIdleState();
	~cEntityGrevertIdleState();

	virtual void update(cApp *app, cEntity *entity, float time);
private:	
	float m_timerDelayAttack;
	unsigned short m_timeToDelayAttack;
};
