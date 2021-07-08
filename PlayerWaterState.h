#pragma once

#include "PlayerState.h"
#include "Player.h"

class cPlayerWaterState : public cPlayerState
{	
public:
	cPlayerWaterState();
	~cPlayerWaterState();

	//virtual void enter(cPlayer *player, cPlayerState* previousState);	
	virtual void update(cApp *app, cPlayer *p, float time);
	//virtual void exit(cPlayer *player);

private:

	float m_targetX, m_targetY;

};