#pragma once

#include "PlayerState.h"
#include "Player.h"

class cPlayerMapState : public cPlayerState
{
public:

	cPlayerMapState();
	~cPlayerMapState();

	virtual void update(cApp *app, cPlayer *p, float time);
	
};