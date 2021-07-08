#pragma once

#include "Entity.h"
#include "EntityState.h"

class cEntityGrodorrAttackState : public cEntityState
{
public:

	cEntityGrodorrAttackState();
	~cEntityGrodorrAttackState();

	virtual void update(cApp *app, cEntity *entity, float time);

private:

};