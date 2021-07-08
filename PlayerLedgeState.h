#pragma once

#include "PlayerState.h"
#include "Player.h"

class cPlayerLedgeState : public cPlayerState {
public:

	cPlayerLedgeState();
	~cPlayerLedgeState();

	virtual void update(cApp* app, cPlayer* p, float time);

private:
	float m_timerClimb, m_timerSideStep;
	bool m_doChangeState;

	cBaseObject* m_ledge;
};