#pragma once

#include "Entity.h"
#include "EntityState.h"

class cEntityFlylingBounceState : public cEntityState
{	
public:

	cEntityFlylingBounceState();
	~cEntityFlylingBounceState();

	virtual void update(cApp *app, cEntity *entity, float time);

private:
	float m_startPosX, m_startPosY;

};