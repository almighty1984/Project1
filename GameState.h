#pragma once
#include <string>
#include "Level.h"

class cApp;

struct sStartInfo {
	std::string start;
	std::string state;
	bool facingLeft;
	bool startUnlocked;
	float velocityX;

	sStartInfo() : facingLeft(false), startUnlocked(false), velocityX(0.0f) {
		start.clear();
		state.clear();
	}
};

class cGameState {
public:
	virtual ~cGameState() {}

	virtual void enter(cApp* app, cGameState* previousState) {};
	virtual void exit(cApp* app) {};
	virtual void init(std::string levelPath, sStartInfo startInfo) {};
	virtual void update(cApp* app, float time) {};
	virtual void render(cApp* app) {};

	virtual void keyDown(cApp* app, int keyDown) { keysHeld[keyDown] = true; };
	virtual void keyUp(cApp* app, int keyUp) { keysHeld[keyUp] = false; };

	virtual void joystickButtonDown(cApp* app, int joystickButtonDown) { joyButtonsHeld[joystickButtonDown] = true; };
	virtual void joystickButtonUp(cApp* app, int joystickButtonUp) { joyButtonsHeld[joystickButtonUp] = false; };
	virtual void joyMovedX(float joyMovedX) { m_joyMovedX = joyMovedX; };
	virtual void joyMovedY(float joyMovedY) { m_joyMovedY = joyMovedY; };

	virtual void mouseButtonDown(cApp* app, int mouseButtonDown) { mouseButtonsHeld[mouseButtonDown] = true; };
	virtual void mouseButtonUp(cApp* app, int mouseButtonUp) { mouseButtonsHeld[mouseButtonUp] = false; };

	virtual void setMouseX(int mouseX) { m_mouseX = mouseX; };
	virtual void setMouseY(int mouseY) { m_mouseY = mouseY; };

	virtual void setHasMouseMoved(bool hasMouseMoved) { m_hasMouseMoved = hasMouseMoved; };

	void initWeather(cApp* app, cLevel* level);
	void stopWeather();
	void updateWeather(cApp* app, cLevel* level, float time);
	bool calculateWeather(unsigned short numerator, unsigned short denominator);

	bool getIsPressingUp()		const;	void setIsPressingUp(bool isPressingUp);
	bool getIsPressingDown()	const;	void setIsPressingDown(bool isPressingDown);
	bool getIsPressingLeft()	const;	void setIsPressingLeft(bool isPressingLeft);
	bool getIsPressingRight()	const;	void setIsPressingRight(bool isPressingRight);

protected:
	cGameState();
	cLevel* m_levelPtr;

	float m_statusBarOffsetX;
	float m_widescreenOffset;

	unsigned short m_prevFps;
	unsigned short m_numUpdateCalls;

	bool keysHeld[323];
	bool joyButtonsHeld[323];
	bool mouseButtonsHeld[323];

	char m_alphabet[52];

	float m_timerState;

	bool m_hasMouseMoved;
	int m_mouseX, m_mouseY;
	float m_joyMovedX, m_joyMovedY;
	float m_joyMovedCooldown;

	bool m_secondCall;

	bool m_doFadeColorDown, m_doFadeColorUp;
	float m_screenColor;

	float m_weatherColor;
	bool m_doDarkenWeather, m_doLightenWeather;
	bool m_doUseWeather;
	bool m_doChangeColorWithWeather;	
};