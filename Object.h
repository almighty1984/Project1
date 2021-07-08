#pragma once

#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "Anim.h"

#include "App.h"
#include "BaseObject.h"

class cObject : public cBaseObject {
public:
	cObject();
	cObject(const cObject& other);
	cObject& operator =(const cObject& other);
	virtual ~cObject();
	
	virtual void loadConfig(std::string fileName);

	virtual void die(cBaseObject* killer);
	virtual void live();
	virtual void hit(float positionX, float positionY);
	virtual void hurt(cBaseObject* hurter, float amount);

	virtual	void setX(float positionX);
	virtual void setY(float positionY);

	virtual void setIsLocked(bool isLocked);

	float getTimeBeingIdle() const { return m_timeBeingIdle; }	void setTimeBeingIdle(float timeBeingIdle) { m_timeBeingIdle = timeBeingIdle; };
	bool getHasMoved() { return m_hasMoved; };	

	virtual void update(float time);

	void keyDown(int keyDown) { keysHeld[keyDown] = true; };
	void keyUp(int keyUp) { keysHeld[keyUp] = false; };
	void joyButtonDown(int joyButtonDown) { joyButtonsHeld[joyButtonDown] = true; };
	void joyButtonUp(int joyButtonUp) { joyButtonsHeld[joyButtonUp] = false; };
	void setJoyMovedX(float joyMovedX) { m_joyMovedX = joyMovedX; }; float getJoyMovedX() { return m_joyMovedX; };
	void setJoyMovedY(float joyMovedY) { m_joyMovedY = joyMovedY; }; float getJoyMovedY() { return m_joyMovedY; };
	void setJoyMovedCooldownX(float joyMovedCooldownX) { m_joyMovedCooldownX = joyMovedCooldownX; }; float getJoyMovedCooldownX() { return m_joyMovedCooldownX; };
	void setJoyMovedCooldownY(float joyMovedCooldownY) { m_joyMovedCooldownY = joyMovedCooldownY; }; float getJoyMovedCooldownY() { return m_joyMovedCooldownY; };
	void mouseButtonDown(int mouseButtonDown) { mouseButtonsHeld[mouseButtonDown] = true; };
	void mouseButtonUp(int mouseButtonUp) { mouseButtonsHeld[mouseButtonUp] = false; };

	const std::string getPathShader() { return m_pathShader; };

	bool getDoUseGravity() const { return m_doUseGravity; }		void setDoUseGravity(bool doUseGravity) { m_doUseGravity = doUseGravity; };
	bool getDoUseShader() const { return m_doUseShader; }		void setDoUseShader(bool doUseShader) { m_doUseShader = doUseShader; };

	bool getIsKeyHeld(unsigned short key) { return keysHeld[key]; }; void setIsKeyHeld(unsigned short key, bool value) { keysHeld[key] = value; };

	
	bool joyButtonsHeld[323];
	bool mouseButtonsHeld[323];		

	std::vector<cObject*> m_connectedObjects;
	void setDontChangeAnimation(bool dontChangeAnimation);

	bool getIsLockedMove()	const { return m_isLockedMove; };	void setIsLockedMove(bool isLockedMove) { m_isLockedMove = isLockedMove; };
	bool getIsLockedOpen()	const { return m_isLockedOpen; };	void setIsLockedOpen(bool isLockedOpen) { m_isLockedOpen = isLockedOpen; };
protected:
	bool keysHeld[323];
	float m_joyMovedX, m_joyMovedY;
	float m_joyMovedCooldownX, m_joyMovedCooldownY;	

	//unsigned short m_nodeId, m_nodeLevel;
	
	
	bool m_hasMoved;

	bool m_doUseGravity;
	bool m_doUseShader;

	std::string m_pathShader;
	

	bool m_dontChangeAnimation;

	bool m_isLockedMove, m_isLockedOpen;
};