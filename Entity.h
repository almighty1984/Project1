#pragma once

#include "Object.h"
#include "EntityState.h"

#include <SFML/Audio.hpp>

class cPlayer;

class cEntity : public cObject {

public:
	
	cEntity();
	virtual ~cEntity();

	void attachPlayer(cPlayer *player) { m_attachedPlayer = player; };

	void setNumber(unsigned short number) { m_number = number; }; unsigned short getNumber() { return m_number; };

	void addPathNumber(unsigned short pathNumber);
	
	void loadConfig(std::string fileName);
	
	virtual	void setX(float positionX);
	virtual void setY(float positionY);

	virtual bool collisionCheckX(cBaseObject* object);			virtual bool collisionCheckY(cBaseObject* object);
	//virtual void collisionReactionX(cBaseObject* object);		virtual void collisionReactionY(cBaseObject* object);
	//virtual bool collisionCheckSlopeX(cBaseObject* object);		virtual bool collisionCheckSlopeY(cBaseObject* object);
	//virtual void collisionReactionSlopeX(cBaseObject* object) {};	virtual void collisionReactionSlopeY(cBaseObject* object) {};

	virtual void die(cBaseObject *killer);
	virtual void hurt(cBaseObject *hurter, float amount);
	//virtual void stun(unsigned short duration);
	
	virtual void setColor(unsigned char r, unsigned char g, unsigned char b);
		
	bool getIsCharging() const { return m_isCharging; };	void setIsCharging(bool isCharging) { m_isCharging = isCharging; };
	bool getIsAttacking() const { return m_isAttacking; };	void setIsAttacking(bool isAttacking) { m_isAttacking = isAttacking; };
	bool getIsStunned() const { return m_isStunned; };		void setIsStunned(bool isStunned) { m_isStunned = isStunned; };

	std::string getSoundIdle() const { return m_soundIdle; };		void setSoundIdle(std::string soundIdle) { m_soundIdle = soundIdle; };
	std::string getSoundAttack() const { return m_soundAttack; };	void setSoundAttack(std::string soundAttack) { m_soundAttack = soundAttack; };

	virtual void update(cApp *app, float time) ;

	virtual void setState(cEntityState* state);

	cPlayer *getAttachedPlayer() { return m_attachedPlayer; };
	cLevel *getAttachedLevel() { return m_attachedLevel; };

	
	void setIsHiddenMeterHealth(bool isHidden) { m_meterHealth.setIsHidden(isHidden); m_meterHealthBackground.setIsHidden(isHidden); };

	float getStartHealth() const { return m_startHealth; };

	unsigned short getPathNumber(unsigned short i);
	int getNumPathNumbers();

	void setNextObject(unsigned short nextObject) { m_nextObject = nextObject; }; unsigned short getNextObject() { return m_nextObject; };
	void setI(short num) { i = num; }; short getI() { return i; };
	
	cEntityState* m_state;
protected:	
	bool m_isCharging;
	bool m_isAttacking;
	bool m_isStunned;
		
	unsigned short m_nextObject, m_number;
	short i;

	float m_jumpForce;
	float m_startHealth;	
	float m_slopeOffsetX;
	float m_startDelay;

	std::string m_soundIdle, m_soundAttack;

	//sAnim m_animWalk, m_animRun, m_animJump, m_animFall, m_animHover, m_animAttack, m_animBounce, m_animStunned, m_animHide;
	
	std::vector<unsigned short> m_pathNumbers;
	cPlayer *m_attachedPlayer;	
	cObject m_meterHealth, m_meterHealthBackground;	
};