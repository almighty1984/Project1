#pragma once

#include <string>
#include <SFML/Graphics.hpp>

#include "Sprite.h"
#include "Shader.h"

#include "Anim.h"

class cLevel;

//#include "Level.h"

//class cObject;

class cBaseObject {
public:
	cBaseObject();
	cBaseObject(const cBaseObject& other);
	cBaseObject& operator=(const cBaseObject& other);
	virtual ~cBaseObject();

	virtual void setVelocityFromSlope(float vectorX, float vectorY);

	cSprite* getSprite() { return &m_sprite; };
	cShader* getShader() { return &m_shader; };
	cLevel* getAttachedLevel()		const { return m_attachedLevel; }	void attachLevel(cLevel* level) { m_attachedLevel = level; };
	cBaseObject* getParent()		const { return m_parent; }			void attachParent(cBaseObject* parent) { m_parent = parent; };
	cBaseObject* getCarrier()		const { return m_carrier; }			void setCarrier(cBaseObject* carrier) { m_carrier = carrier; };
	cBaseObject* getAboveObject()	const { return m_aboveObject; }		void setAboveObject(cBaseObject* aboveObject) { m_aboveObject = aboveObject; };
	cBaseObject* getBelowObject()	const { return m_belowObject; }		void setBelowObject(cBaseObject* belowObject) { m_belowObject = belowObject; };
	cBaseObject* getLeftObject()	const { return m_leftObject; }		void setLeftObject(cBaseObject* leftObject) { m_leftObject = leftObject; };
	cBaseObject* getRightObject()	const { return m_rightObject; }		void setRightObject(cBaseObject* rightObject) { m_rightObject = rightObject; };
	cBaseObject* getCarriedObject()	const { return m_carriedObject; }	void setCarriedObject(cBaseObject* object) { m_carriedObject = object; };
	cBaseObject* getThrownObject()	const { return m_thrownObject; }	void setThrownObject(cBaseObject* object) { m_thrownObject = object; };

	virtual bool collisionCheckX(cBaseObject* object);				virtual bool collisionCheckY(cBaseObject* object);
	virtual bool collisionCheckSlopeX(cBaseObject* object);			virtual bool collisionCheckSlopeY(cBaseObject* object);
	virtual void collisionReactionX(cBaseObject* object) {}			virtual void collisionReactionY(cBaseObject* object) {};
	virtual void collisionReactionSlopeX(cBaseObject* object);		virtual void collisionReactionSlopeY(cBaseObject* object);	
	float getDelayCollisionLevel()	const { return m_delayCollisionLevel; }		void setDelayCollisionLevel(float delayCollisionLevel) { m_delayCollisionLevel = delayCollisionLevel; };
	float getDelayCollisionEntity()	const { return m_delayCollisionEntity; }	void setDelayCollisionEntity(float delayCollisionEntity) { m_delayCollisionEntity = delayCollisionEntity; };

	unsigned char getColor(char element) const; virtual void setColor(unsigned char r, unsigned char g, unsigned char b);

	virtual void die(cBaseObject* killer) {};
	virtual void live() {};
	virtual void hit(float positionX, float positionY) {};
	virtual void hurt(cBaseObject* hurter, float amount) {};
	virtual void hitGround(cBaseObject* object) {};

	bool getIsHurting()				const { return m_isHurting; }			void setIsHurting(bool isHurting) { m_isHurting = isHurting; };
	float getHurtAgainDelay()		const { return m_hurtAgainDelay; }		void setHurtAgainDelay(float hurtAgainDelay) { m_hurtAgainDelay = hurtAgainDelay; };
	float getHurtAgainDelayValue()	const { return m_hurtAgainDelayValue; }	void setHurtAgainDelayValue(float hurtAgainDelayValue) { m_hurtAgainDelayValue = hurtAgainDelayValue; };

	float getTimerSense()			const { return m_timerSense; }			void setTimerSense(float timerSense) { m_timerSense = timerSense; };
	float getTimerSenseClear()		const { return m_timerSenseClear; }		void setTimerSenseClear(float timerSenseClear) { m_timerSenseClear = timerSenseClear; };
	bool getSenseCollidedLeft()		const { return m_senseCollidedLeft; }	void setSenseCollidedLeft(bool senseCollidedLeft) { m_senseCollidedLeft = senseCollidedLeft; };
	bool getSenseCollidedRight()	const { return m_senseCollidedRight; }	void setSenseCollidedRight(bool senseCollidedRight) { m_senseCollidedRight = senseCollidedRight; };
	bool getSenseCollidedAbove()	const { return m_senseCollidedAbove; }	void setSenseCollidedAbove(bool senseCollidedAbove) { m_senseCollidedAbove = senseCollidedAbove; };

	void senseCollidedLeft(cBaseObject* object);
	void senseCollidedRight(cBaseObject* object);
	void senseCollidedAbove(cBaseObject* object);
	void senseCollidedBelow(cBaseObject* object);
	void clearSenses();
	void clearSenseAbove();
	void clearSenseBelow();
	void clearSenseLeft();
	void clearSenseRight();
	virtual void spawnSenses() {};
	bool getDoSpawnSenses() { return m_doSpawnSenses; }		void setDoSpawnSenses(bool doSpawnSenses) { m_doSpawnSenses = doSpawnSenses; };

	virtual void update(float time);

	virtual void loadConfig(std::string fileName);

	int getOffsetX() const { return m_offsetX; }	void setOffsetX(int offsetX) { m_offsetX = offsetX; };
	int getOffsetY() const { return m_offsetY; }	void setOffsetY(int offsetY) { m_offsetY = offsetY; };

	bool getIsFacingLeft()	const { return m_isFacingLeft; }				void setIsFacingLeft(bool isFacingLeft) { m_isFacingLeft = isFacingLeft; };
	bool getIsUpsideDown()	const { return m_isUpsideDown; }				void setIsUpsideDown(bool isUpsideDown) { m_isUpsideDown = isUpsideDown; };
	bool getIsUpdatedEveryFrame() const { return m_isUpdatedEveryFrame; }	void setIsUpdatedEveryFrame(bool isUpdatedEveryFrame) { m_isUpdatedEveryFrame = isUpdatedEveryFrame; };
	bool getIsUsingFloatPosition() const { return m_isUsingFloatPosition; }	void setIsUsingFloatPosition(bool isUsingFloatPosition) { m_isUsingFloatPosition = isUsingFloatPosition; };

	std::string getImagePath() const { return m_imagePath; }	virtual void setImagePath(std::string imagePath);
	unsigned short getWidth()		const { return m_width; }	void setWidth(unsigned short width) { m_width = width; }
	unsigned short getHeight()	const { return m_height; }		void setHeight(unsigned short height) { m_height = height; }

	float getDamage()		const { return m_damage; }		void setDamage(float damage) { m_damage = damage; }

	double getDirection()		const { return m_direction; }	void setDirection(double direction) { m_direction = direction; }
	unsigned short getRadius()	const { return m_radius; }		void setRadius(unsigned short radius) { m_radius = radius; }
	float getRotation()			const { return m_rotation; }	void setRotation(float rotation);
	void setOrigin(float positionX, float y);
	void rotate(float angle);

	float getSpriteOffsetX() const { return m_spriteOffsetX; }	void setSpriteOffsetX(float spriteOffsetX) { m_spriteOffsetX = spriteOffsetX; }
	float getSpriteOffsetY() const { return m_spriteOffsetY; }	void setSpriteOffsetY(float spriteOffsetY) { m_spriteOffsetY = spriteOffsetY; }

	float getX()		const { return m_x; }		void setX(float positionX) { m_x = positionX; }
	float getY()		const { return m_y; }		void setY(float positionY) { m_y = positionY; }
	float getLevelX()	const { return m_levelX; }	void setLevelX(float levelX) { m_levelX = levelX; }
	float getLevelY()	const { return m_levelY; }	void setLevelY(float levelY) { m_levelY = levelY; }

	float getPreviousX() const { return m_previousX; }
	float getPreviousY() const { return m_previousY; }

	float getTop()		const { return (m_y + m_subtractUp); }
	float getBottom()	const { return (m_y + m_height - m_subtractDown); }
	float getLeft()		const { return (m_x + m_subtractLeft); }
	float getRight()	const { return (m_x + m_width - m_subtractRight); }
	float getMiddleX()	const { return (m_x + m_width * 0.5f); }
	float getMiddleY()	const { return (m_y + m_height * 0.5f); }

	float getVelocityX() const { return m_velocityX; }	void setVelocityX(float velocityX) { m_velocityX = velocityX; }
	float getVelocityY() const { return m_velocityY; }	void setVelocityY(float velocityY) { m_velocityY = velocityY; }

	void addVelocityX(float velocityX) { m_velocityX += velocityX; }
	void addVelocityY(float velocityY) { m_velocityY += velocityY; }

	float getFallVelocity() const { return m_fallVelocity; }	void setFallVelocity(float fallVelocity) { m_fallVelocity = fallVelocity; }
	float getFallAcc() const { return m_fallAcc; }				void setFallAcc(float fallAcc) { m_fallAcc = fallAcc; }
	float getMoveVelocity() const { return m_moveVelocity; }	void setMoveVelocity(float moveVelocity) { m_moveVelocity = moveVelocity; }
	float getMoveAcc() const { return m_moveAcc; }				void setMoveAcc(float moveAcc) { m_moveAcc = moveAcc; }
	float getMoveDec() const { return m_moveDec; }				void setMoveDec(float moveDec) { m_moveDec = moveDec; }
	float getMovedVelocityX() const { return m_movedVelocityX; }	void setMovedVelocityX(float movedVelocityX) { m_movedVelocityX = movedVelocityX; }
	float getMovedVelocityY() const { return m_movedVelocityY; }	void setMovedVelocityY(float movedVelocityY) { m_movedVelocityX = movedVelocityY; }

	float getTileOffsetX() const { return m_tileOffsetX; }					void setTileOffsetX(float tileOffsetX) { m_tileOffsetX = tileOffsetX; }
	float getTileOffsetY() const { return m_tileOffsetY; }					void setTileOffsetY(float tileOffsetY) { m_tileOffsetY = tileOffsetY; }
	float getPreviousTileOffsetX() const { return m_previousTileOffsetX; }	void setPreviousTileOffsetX(float previousTileOffsetX) { m_previousTileOffsetX = previousTileOffsetX; }
	float getPreviousTileOffsetY() const { return m_previousTileOffsetY; }	void setPreviousTileOffsetY(float previousTileOffsetY) { m_previousTileOffsetY = previousTileOffsetY; }

	int getTile()				const { return m_tile; }	void setTile(int tile) { m_tile = tile; }
	unsigned char getLayer()	const { return m_layer; }	void setLayer(unsigned char layer) { m_layer = layer; }
	std::string getType()		const { return m_type; }	void setType(std::string type) { m_type = type; }

	float getStartX()			const { return m_startX; }			void setStartX(float startX) { m_startX = startX; }
	float getStartY()			const { return m_startY; }			void setStartY(float startY) { m_startY = startY; }
	float getOldStartX()		const { return m_oldStartX; }		void setOldStartX(float oldStartX) { m_oldStartX = oldStartX; }
	float getOldStartY()		const { return m_oldStartY; }		void setOldStartY(float oldStartY) { m_oldStartY = oldStartY; }
	float getStartVelocityX()	const { return m_startVelocityX; }	void setStartVelocityX(float startVelocityX) { m_startVelocityX = startVelocityX; }
	float getStartVelocityY()	const { return m_startVelocityY; }	void setStartVelocityY(float startVelocityY) { m_startVelocityY = startVelocityY; }
	float getStartMoveVelocity()	const { return m_startMoveVelocity; }	void setStartMoveVelocity(float startMoveVelocity) { m_startMoveVelocity = startMoveVelocity; }
	float getStartMoveAcc()		const { return m_startMoveAcc; }		void setStartMoveAcc(float startMoveAcc) { m_startMoveAcc = startMoveAcc; }
	float getStartMoveDec()		const { return m_startMoveDec; }		void setStartMoveDec(float startMoveDec) { m_startMoveDec = startMoveDec; }

	bool getDoRemove()			const { return m_doRemove; }		void setDoRemove(bool doRemove) { m_doRemove = doRemove; }
	bool getDoRotate()			const { return m_doRotate; }		void setDoRotate(bool doRotate) { m_doRotate = doRotate; }
	bool getDontFlipSprite()	const { return m_dontFlipSprite; }	void setDontFlipSprite(bool dontFlipSprite) { m_dontFlipSprite = dontFlipSprite; }

	bool getIsInWater()			const { return m_isInWater; }		void setIsInWater(bool isInWater) { m_isInWater = isInWater; }
	bool getIsInWaterJump()		const { return m_isInWaterJump; }	void setIsInWaterJump(bool isInWaterJump) { m_isInWaterJump = isInWaterJump; }

	bool getIsRideable()		 const { return m_isRideable; }	void setIsRideable(bool isRideable) { m_isRideable = isRideable; };
	bool getIsRiding()			const { return m_isRiding; }		void setIsRiding(bool isRiding) { m_isRiding = isRiding; }

	bool getIsSolidX()	const { return m_isSolidEntityX || m_isSolidPlayerX || m_isSolidLevelX; }		void setIsSolidX(bool isSolidX) { m_isSolidEntityX = m_isSolidPlayerX = m_isSolidLevelX = isSolidX; };
	bool getIsSolidY()	const { return m_isSolidEntityY || m_isSolidPlayerY || m_isSolidLevelY; }		void setIsSolidY(bool isSolidY) { m_isSolidEntityY = m_isSolidPlayerY = m_isSolidLevelY = isSolidY; };
	bool getIsSolid()	const { return m_isSolidEntityX || m_isSolidPlayerX || m_isSolidLevelX || m_isSolidEntityY || m_isSolidPlayerY || m_isSolidLevelY;}	void setIsSolid(bool isSolid) { m_isSolidEntityX = m_isSolidPlayerX = m_isSolidLevelX = m_isSolidEntityY = m_isSolidPlayerY = m_isSolidLevelY = isSolid; };

	bool getIsSolidEntityX()	const { return m_isSolidEntityX; }						void setIsSolidEntityX(bool isSolidEntityX) { m_isSolidEntityX = isSolidEntityX; };
	bool getIsSolidEntityY()	const { return m_isSolidEntityY; }						void setIsSolidEntityY(bool isSolidEntityY) { m_isSolidEntityY = isSolidEntityY; };
	bool getIsSolidEntity()		const { return m_isSolidEntityX && m_isSolidEntityY; }	void setIsSolidEntity(bool isSolidEntity) { m_isSolidEntityX = isSolidEntity; m_isSolidEntityY = isSolidEntity; };
	bool getIsSolidPlayerX()	const { return m_isSolidPlayerX; }						void setIsSolidPlayerX(bool isSolidPlayerX) { m_isSolidPlayerX = isSolidPlayerX; };
	bool getIsSolidPlayerY()	const { return m_isSolidPlayerY; }						void setIsSolidPlayerY(bool isSolidPlayerY) { m_isSolidPlayerY = isSolidPlayerY; };
	bool getIsSolidPlayer()		const { return m_isSolidPlayerX && m_isSolidPlayerY; }	void setIsSolidPlayer(bool isSolidPlayer) { m_isSolidPlayerX = isSolidPlayer; m_isSolidPlayerY = isSolidPlayer; };
	bool getIsSolidLevelX()		const { return m_isSolidLevelX; }						void setIsSolidLevelX(bool isSolidLevelX) { m_isSolidLevelX = isSolidLevelX; };
	bool getIsSolidLevelY()		const { return m_isSolidLevelY; }						void setIsSolidLevelY(bool isSolidLevelY) { m_isSolidLevelY = isSolidLevelY; };
	bool getIsSolidLevel()		const { return m_isSolidLevelX && m_isSolidLevelY; }	void setIsSolidLevel(bool isSolidLevel) { m_isSolidLevelX = isSolidLevel; m_isSolidLevelY = isSolidLevel; };
	bool getIsAnim()		const { return m_isAnim; }		void setIsAnim(bool isAnim) { m_isAnim = isAnim; }
	bool getIsIdle()			const { return m_isIdle; }			void setIsIdle(bool isIdle) { m_isIdle = isIdle; }
	bool getIsInSlope()			const { return m_isInSlope; }		void setIsInSlope(bool isInSlope) { m_isInSlope = isInSlope; }
	bool getIsSlopeSliding()	const { return m_isSlopeSliding; }	void setIsSlopeSliding(bool isSlopeSliding) { m_isSlopeSliding = isSlopeSliding; }
	bool getIsCarried()			const { return m_isCarried; }		void setIsCarried(bool isCarried) { m_isCarried = isCarried; }
	bool getIsCarrying()		const { return m_isCarrying; }		void setIsCarrying(bool isCarrying) { m_isCarrying = isCarrying; }
	bool getIsCircle()			const { return m_isCircle; }		void setIsCircle(bool isCircle) { m_isCircle = isCircle; }
	bool getIsDead()			const { return m_isDead; }			void setIsDead(bool isDead) { m_isDead = isDead; }
	bool getIsEntity()			const { return m_isEntity; }		void setIsEntity(bool isEntity) { m_isEntity = isEntity; }
	bool getIsHidden()			const { return m_isHidden; }		void setIsHidden(bool isHidden) { m_isHidden = isHidden; }
	bool getIsLight()			const { return m_isLight; }			void setIsLight(bool isLight) { m_isLight = isLight; }
	bool getIsLocked()			const { return m_isLocked; }		virtual void setIsLocked(bool isLocked) { m_isLocked = isLocked; }
	bool getIsNearWallLeft()	const { return m_isNearWallLeft; }	void setIsNearWallLeft(bool isNearWallLeft) { m_isNearWallLeft = isNearWallLeft; }
	bool getIsNearWallRight()	const { return m_isNearWallRight; }	void setIsNearWallRight(bool isNearWallRight) { m_isNearWallRight = isNearWallRight; }
	bool getIsOnBack()			const { return m_isOnBack; }		void setIsOnBack(bool isOnBack) { m_isOnBack = isOnBack; }
	bool getIsOnGround()		const { return m_isOnGround; }		void setIsOnGround(bool isOnGround) { m_isOnGround = isOnGround; }
	bool getIsOnLedge()			const { return m_isOnLedge; }		void setIsOnLedge(bool isOnLedge) { m_isOnLedge = isOnLedge; };
	bool getIsSlope()			const { return m_isSlope; }			void setIsSlope(bool isSlope) { m_isSlope = isSlope; }
	bool getIsStatic()			const { return m_isStatic; }		void setIsStatic(bool isStatic) { m_isStatic = isStatic; }
	bool getIsThrown()			const { return m_isThrown; }		void setIsThrown(bool isThrown) { m_isThrown = isThrown; }

	bool getIsThrowing()		const { return m_isThrowing; }		void setIsThrowing(bool isThrowing) { m_isThrowing = isThrowing; }
		
	short getSubtractUp()			const { return m_subtractUp; }		void setSubtractUp(short subtractUp) { m_subtractUp = subtractUp; }
	short getSubtractDown()			const { return m_subtractDown; }	void setSubtractDown(short subtractDown) { m_subtractDown = subtractDown; }
	short getSubtractLeft()			const { return m_subtractLeft; }	void setSubtractLeft(short subtractLeft) { m_subtractLeft = subtractLeft; }
	short getSubtractRight()		const { return m_subtractRight; }	void setSubtractRight(short subtractRight) { m_subtractRight = subtractRight; }
	short getStartSubtractUp()		const { return m_startSubtractUp; }
	short getStartSubtractDown()	const { return m_startSubtractDown; }
	short getStartSubtractLeft()	const { return m_startSubtractLeft; }
	short getStartSubtractRight()	const { return m_startSubtractRight; }	
	void resetCollisionBox();
			
	//sAnim getAnimCurrent()				const { return m_animCurrent; }			void setAnimCurrent(sAnim animCurrent) { m_animCurrent = animCurrent; }
	float getAnimSpeed()				const { return m_animSpeed; }			void setAnimSpeed(float animSpeed) { m_animSpeed = animSpeed; }
	float getAnimTime()					const { return m_animTime; }			void setAnimTime(float animTime) { m_animTime = animTime; }
	unsigned short getNumAnimLoops()	const { return m_numAnimLoops; }		void setNumAnimationLoops(unsigned short numAnimLoops) { m_numAnimLoops = numAnimLoops; }
	unsigned short getNumAnimFrames()	const { return m_numAnimFrames; }		void setNumFrames(unsigned short numAnimFrames) { m_numAnimFrames = numAnimFrames; }
	unsigned short getCurrentLoops()	const { return m_currentLoops; }		void setCurrentLoops(unsigned short currentLoops) { m_currentLoops = currentLoops; }
	
	//sf::Sprite* getSprite() { return &m_sfSprite; };
	//sf::Shader* getShader() { return &m_sfShader; };

	void setSpritePosition(float spritePositionX, float spritePositionY);
	void setSpriteRect(unsigned short x, unsigned short y, unsigned short width, unsigned short height);
	void setSpriteScale(float spriteScaleX, float spriteScaleY);	
	
	float getHurtSleepDelay() const { return m_hurtSleepDelay; }	void setHurtSleepDelay(float hurtSleepDelay) { m_hurtSleepDelay = hurtSleepDelay; };

	void createAnim(std::string id, unsigned short y, float speed, unsigned short loop);
	sAnim getAnim(eAnimTag animTag);
	eAnimTag getAnimTag() {	return m_animTag; }	void setAnim(eAnimTag animTag);

	float getNumHealth()		const { return m_numHealth; }		void setNumHealth(float numHealth) { m_numHealth = numHealth; }

	float getTimeBeingAlive()	const { return m_timeBeingAlive; }	void setTimeBeingAlive(float timeBeingAlive) { m_timeBeingAlive = timeBeingAlive; }
	float getTimeToBeAlive()	const { return m_timeToBeAlive; }	void setTimeToBeAlive(float timeToBeAlive) { m_timeToBeAlive = timeToBeAlive; }
	float getTimeBeingDead()	const { return m_timeBeingDead; }	void setTimeBeingDead(float timeBeingDead) { m_timeBeingDead = timeBeingDead; }
	float getTimeToBeDead()		const { return m_timeToBeDead; }	void setTimeToBeDead(float timeToBeDead) { m_timeToBeDead = timeToBeDead; }
	float getTimeBeingIdle()	const { return m_timeBeingIdle; }	void setTimeBeingIdle(float timeBeingIdle) { m_timeBeingIdle = timeBeingIdle; }
	float getTimeToBeIdle()		const { return m_timeToBeIdle; }	void setTimeToBeIdle(float timeToBeIdle) { m_timeToBeIdle = timeToBeIdle; }
	float getTimerThrow()		const { return m_timerThrow; }		void setTimerThrow(float timerThrow) { m_timerThrow = timerThrow; }
	float getTimeLimitThrow()	const { return m_timeLimitThrow; }	void setTimeLimitThrow(float timeLimitThrow) { m_timeLimitThrow = timeLimitThrow; }
	float getTimerState()		const { return m_timerState; }		void setTimerState(float timerState) { m_timerState = timerState; }

	virtual void throwCarried() {};
protected:
	cSprite m_sprite;
	cShader m_shader;
	cLevel* m_attachedLevel;
	cBaseObject* m_parent;
	cBaseObject* m_carrier;
	cBaseObject* m_carriedObject;
	cBaseObject* m_aboveObject;
	cBaseObject* m_belowObject;
	cBaseObject* m_leftObject;
	cBaseObject* m_rightObject;
	cBaseObject* m_thrownObject;
	cBaseObject* m_sensedObject;
	bool m_senseCollidedLeft, m_senseCollidedRight, m_senseCollidedAbove, m_senseCollidedBelow;

	float m_delayCollisionLevel, m_delayCollisionEntity;

	float m_timerSense, m_timerSenseClear;

	float m_lastTime;
	float m_x, m_y;
	float m_startX, m_startY, m_oldStartX, m_oldStartY;
	float m_startFallVelocity, m_startMoveAcc, m_startMoveDec, m_startMoveVelocity;
	float m_previousX, m_previousY;

	float m_velocityX, m_velocityY;
	float m_fallVelocity;
	float m_fallAcc;
	float m_moveVelocity, m_moveAcc, m_moveDec;
	float m_movedVelocityX, m_movedVelocityY;
	float m_startVelocityX, m_startVelocityY;
	float m_timerState;
	float m_timerThrow, m_timeLimitThrow;

	float m_numHealth;
	float m_timeBeingAlive, m_timeToBeAlive;
	float m_timeBeingDead, m_timeToBeDead;
	float m_timeBeingIdle, m_timeToBeIdle;

	bool m_isHurting;
	bool m_isNearWallLeft, m_isNearWallRight;
	float m_hurtAgainDelay, m_hurtAgainDelayValue;

	float m_damage;
	double m_direction;
	float m_rotation;
	float m_spriteOffsetX, m_spriteOffsetY;

	int m_tile;
	unsigned char m_layer;
	
	unsigned short m_width, m_height;
	
	int m_offsetX, m_offsetY;

	float m_slopeOffsetX;
	float m_tileOffsetX, m_tileOffsetY, m_previousTileOffsetX, m_previousTileOffsetY;
	float m_levelX, m_levelY;
	float m_previousLevelX, m_previousLevelY;
	
	std::string m_type;
	std::string m_imagePath;
	
	float m_hurtSleepDelay;
	
	/*bool m_startIsSolidX, m_startIsSolidY;
	bool m_dontChangeSolid;*/
	bool m_dontFlipSprite;
	bool m_doRotate, m_doRemove;
	bool m_doSpawnSenses;
	bool m_isAnim;
	bool m_isUsingFloatPosition;
	bool m_isInWater, m_isInWaterJump;
	bool m_isFacingLeft;
	bool m_isCarried, m_isCarrying;
	bool m_isCircle;
	bool m_isDead;
	bool m_isEntity;
	bool m_isHidden;
	bool m_isIdle;
	bool m_isInSlope, m_isSlopeSliding;
	bool m_isLight;
	bool m_isLocked;
	bool m_isRideable, m_isRiding;
	bool m_isSlope;
	bool m_isSolidEntityX, m_isSolidEntityY, m_isSolidPlayerX, m_isSolidPlayerY, m_isSolidLevelX, m_isSolidLevelY;
	bool m_isStatic;
	bool m_isThrown;
	bool m_isThrowing;
	bool m_isUpsideDown;
	bool m_isOnBack, m_isOnGround, m_isOnLedge;	

	bool m_isUpdatedEveryFrame;
	
	// Collision config
	unsigned short m_radius;
	short m_subtractUp, m_subtractDown;
	short m_subtractLeft, m_subtractRight;
	short m_startSubtractUp, m_startSubtractDown;
	short m_startSubtractLeft, m_startSubtractRight;
					
	unsigned short m_numAnimFrames, m_currentLoops, m_numAnimLoops;
	float m_animTime, m_animSpeed;
	//sAnim m_animCurrent;
	//std::map<std::string, sAnim> m_anims;

	eAnimTag m_animTag;

	std::map<eAnimTag, sAnim> m_anims;
};