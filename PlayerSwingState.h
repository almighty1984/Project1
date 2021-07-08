#pragma once

#include "PlayerState.h"
#include "Player.h"

class cPlayerSwingState : public cPlayerState
{	
public:
	cPlayerSwingState();
	//~cPlayerSwingState();
	virtual void update(cApp *app, cPlayer *p, float time);
private:
};