#pragma once

//#include "Object.h"
//#include "Player.h"

class cApp;
class cPlayer;

class cPlayerState
{
public:
	//virtual ~cPlayerState(){}
	//virtual void enter(cPlayer *player, cPlayerState* previousState) {}
	virtual void update(cApp *app, cPlayer *p, float time) {}
	//virtual void exit(cPlayer *player) {}
	
protected:
	//cPlayerState(){}
	bool m_secondCall;

};