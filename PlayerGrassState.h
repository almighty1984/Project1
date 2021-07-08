#pragma once

#include "PlayerState.h"
#include "Player.h"

class cPlayerGrassState : public cPlayerState
{	
public:

	cPlayerGrassState();
	~cPlayerGrassState();

	virtual void update(cApp *app, cPlayer *p, float time);
	
private:

	float m_thrustX, m_thrustY;
};