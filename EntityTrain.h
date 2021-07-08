#pragma once

#include "Entity.h"
#include "Particle.h"

class cEntityTrain : public cEntity
{
public:
	cEntityTrain();
	~cEntityTrain();
	//virtual void hurt(cBaseObject *hurter, float amount);
	virtual void update(cApp *app, float time);

private:
	bool m_secondCall;
};