#pragma once

#include "Entity.h"
#include "EntityState.h"

class cEntityFlylingHitState : public cEntityState
{	
public:

	cEntityFlylingHitState();
	cEntityFlylingHitState(float velX, float velY);
	~cEntityFlylingHitState();

	virtual void update(cApp *app, cEntity *entity, float time);

private:
	float m_velX, m_velY;
};