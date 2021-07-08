#pragma once

#include "Entity.h"
#include "EntityState.h"

class cEntityTrainIdleState : public cEntityState
{
public:

	cEntityTrainIdleState();
	~cEntityTrainIdleState();

	virtual void update(cApp *app, cEntity *entity, float time);
private:
	float m_switchDirectionDelay;
};