#pragma once

#include "Entity.h"
#include "EntityState.h"

class cEntityFlylingChargeState : public cEntityState
{	
public:

	cEntityFlylingChargeState();
	~cEntityFlylingChargeState();

	virtual void update(cApp *app, cEntity *entity, float time);

private:
	//cEntity *m_parent;

};