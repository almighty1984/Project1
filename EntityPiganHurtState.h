#pragma once

#include "Entity.h"
#include "EntityState.h"

class cEntityPiganHurtState : public cEntityState
{	
public:

	cEntityPiganHurtState();
	~cEntityPiganHurtState();

	virtual void update(cApp *app, cEntity *entity, float time);

private:

	//unsigned short m_hideTimer;
	float m_oldVelocityX, m_oldForceXPlayerX, m_oldForceYPlayerX,	m_oldForceXPlayerY, m_oldForceYPlayerY;
	bool m_secondCall;	
};