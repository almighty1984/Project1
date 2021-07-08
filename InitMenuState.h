#pragma once

#include "GameState.h"

class cInitMenuState : public cGameState
{
public:	
	cInitMenuState();
	~cInitMenuState();
	virtual void exit(cApp *app);
	virtual void enter(cApp *app, cGameState *previousState);
	virtual void update(cApp *app, float time);
	//virtual void render(const cApp *app) const;
	
private:

};
