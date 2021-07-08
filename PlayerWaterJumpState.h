#pragma once

#include "PlayerState.h"
#include "Player.h"

class cPlayerWaterJumpState : public cPlayerState
{
public:

	cPlayerWaterJumpState();
	~cPlayerWaterJumpState();

	virtual void update(cApp *app, cPlayer *p, float time);

private:

};