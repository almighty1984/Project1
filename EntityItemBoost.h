#pragma once

#include "Entity.h"
#include "Particle.h"

class cEntityItemBoost : public cEntity
{
public:

	cEntityItemBoost();
	~cEntityItemBoost();

	virtual void update(cApp *app, float time);

private:
	bool m_secondCall;
};