#pragma once

#include "Entity.h"
#include "EntityState.h"

class cEntityPiganBackState : public cEntityState {
public:

	cEntityPiganBackState();
	~cEntityPiganBackState();

	virtual void update(cApp* app, cEntity* entity, float time);

private:

};