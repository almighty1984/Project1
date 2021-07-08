#pragma once

#include "Object.h"
#include "Particle.h"
#include "Entity.h"
#include <SFML/Audio.hpp>

#include "PlayerState.h"
//#include "PlayerGrassState.h"
//#include "PlayerWaterState.h"

#include "RenderingManager.h"

class cPlayer : public cObject {
public:
	
	cPlayer();
	~cPlayer();
	
	void setState(cPlayerState* state);
	virtual void spawnSenses();

	cBaseObject* getMorphObject() { return m_morphObject; };		void setMorphObject(cBaseObject* morphObject) { m_morphObject = morphObject; };

	std::string const& getNextLevel() { return m_nextLevel; };		void setNextLevel(std::string nextLevel) { m_nextLevel = nextLevel; };
	std::string const getCurrentLevel() { return m_currentLevel; };	void setCurrentLevel(std::string const currentLevel) { m_currentLevel = currentLevel; };

	float getStrength()			const { return m_strength; };		void setStrength(float strength) { m_strength = strength; };

	float getVitality()			const { return m_vitality; };		void setVitality(float vitality) { m_vitality = vitality; };
	float getStamina()			const { return m_stamina; };		void setStamina(float stamina) { m_stamina = stamina; };
	float getStaminaCounter()	const { return m_staminaCounter; };	void setStaminaCounter(float staminaCounter) { m_staminaCounter = staminaCounter; };

	char getVitalityMeterValue()	const { return m_vitalityMeterValue; };	void setVitalityMeterValue(unsigned char vitalityMeterValue) { m_vitalityMeterValue = vitalityMeterValue; };
	char getStaminaMeterValue()		const { return m_staminaMeterValue; };	void setStaminaMeterValue(unsigned char staminaMeterValue) { m_staminaMeterValue = staminaMeterValue; };

	//bool hasEnoughStamina(float value) { return ((int)(value / m_stamina) <= m_staminaMeterValue ? true : false); };

	bool hasEnoughStamina(std::string key) { return ((int)(m_staminaCost[key] / m_stamina) <= m_staminaMeterValue ? true : false); };

	void decreaseMeterStamina(std::string key) { hasEnoughStamina(key) ? m_staminaCounter -= (m_staminaCost[key] / m_stamina) : 0; };

	//void decreaseMeterStamina(float value) { hasEnoughStamina(value) ? m_staminaCounter -= (value / m_stamina) : 0; };
	
	virtual void update(cApp *app, float time);
	virtual void loadConfig(std::string fileName);
	virtual bool collisionCheckX(cBaseObject *object);			virtual bool collisionCheckY(cBaseObject *object);
	virtual void collisionReactionX(cBaseObject *object);		virtual void collisionReactionY(cBaseObject *object);
	virtual bool collisionCheckSlopeX(cBaseObject* object);		virtual bool collisionCheckSlopeY(cBaseObject* object);
	virtual void collisionReactionSlopeX(cBaseObject* object);	virtual void collisionReactionSlopeY(cBaseObject* object);
	bool collisionCheckEntityX(cEntity* entity);				bool collisionCheckEntityY(cEntity* entity);
	void collisionReactionEntityX(cEntity* entity);				void collisionReactionEntityY(cEntity* entity);	

	virtual void hurt(cBaseObject *hurter, float amount);
	
	void save(cApp *app);
	void jump();
	void jumpWall(cApp *app, float time);
	virtual void hitGround(cBaseObject *object);
	void slideWall(cBaseObject *object);
	void attackMelee(cApp *app, float time);
	void attackOpen(cApp *app, float time);
	//void attackThrow();
	void attackShoot();
	void digSand();	
	void throwCarried();	
	void dropCarried();

	bool getDoStartUnlocked() const { return m_doStartUnlocked; }	void setDoStartUnlocked(bool doStartUnlocked) { m_doStartUnlocked = doStartUnlocked; }
	bool getDoPlayMusic(unsigned char num) const { if (num == 1) { return m_doPlayMusic1; } else { return m_doPlayMusic0; }; }

	bool getHasHover()	const { return m_hasHover; }		void setHasHover(bool hasHover) { m_hasHover = hasHover; };
	bool getHasSprint()	const { return m_hasSprint; }		void setHasSprint(bool hasSprint) { m_hasSprint = hasSprint; };
	bool getHasWhirl()	const { return m_hasWhirl; }		void setHasWhirl(bool hasWhirl) { m_hasWhirl; };

	bool getHasCollidedItem()	const { return m_hasCollidedItem; }	void setHasCollidedItem(bool hasCollidedItem) { m_hasCollidedItem = hasCollidedItem; }
	bool getHasCollidedSave()	const { return m_hasCollidedSave; }	void setHasCollidedSave(bool hasCollidedSave) { m_hasCollidedSave = hasCollidedSave; }
	bool getHasJumpedHigh()		const { return m_hasJumpedHigh; }		void setHasJumpedHigh(bool hasJumpedHigh)			{ m_hasJumpedHigh = hasJumpedHigh; }
	bool getHasJumped()			const { return m_hasJumped; }			void setHasJumped(bool hasJumped)					{ m_hasJumped = hasJumped; }
		
	bool getIsInDoor(int number)	const { return m_isInDoor[number]; }	void setIsInDoor(int number, bool isIsInDoor) { m_isInDoor[number] = isIsInDoor; }
	bool getIsInMap()				const { return m_isInMap; }			void setIsInMap(bool isInMap) { m_isInMap = isInMap; }
	bool getIsInSign(int number)	const { return m_isInSign[number]; }	void setIsInSign(int number, bool inSign) { m_isInSign[number] = inSign; }
	bool getIsNearSign()			const { return m_isNearSign; }			void setIsNearSign(bool isNearSign) { m_isNearSign = isNearSign; }
	bool getIsNearDoor()			const { return m_isNearDoor; }			void setIsNearDoor(bool isNearDoor) { m_isNearDoor = isNearDoor; }
	bool getIsInShop()				const { return m_isInShop; }			void setIsInShop(bool isInShop) { m_isInShop = isInShop; }

	bool getIsMeleeing()			const { return m_isMeleeing; }		void setIsMeleeing(bool isMeleeing) { m_isMeleeing = isMeleeing; }
	bool getIsCrawling()			const { return m_isCrawling; }			void setIsCrawling(bool isCrawling) { m_isCrawling = isCrawling; }
	bool getIsDigging()				const { return m_isDigging; }			void setIsDigging(bool isDigging) { m_isDigging = isDigging; }
	bool getIsDropping()			const { return m_isDropping; }			void setIsDropping(bool isDropping) { m_isDropping = isDropping; }
	bool getIsDownThrusting()		const { return m_isDownThrusting; }	void setIsDownThrusting(bool isDownThrusting) { m_isDownThrusting = isDownThrusting; }
	bool getIsDucking()				const { return m_isDucking; }			void setIsDucking(bool isDucking) { m_isDucking = isDucking; }
	bool getIsDuckAttacking()		const { return m_isDuckAttacking; }	void setIsDuckAttacking(bool isDuckAttacking) { m_isDuckAttacking = isDuckAttacking; }
	bool getIsHovering()			const { return m_isHovering; }			void setIsHovering(bool isHovering) { m_isHovering = isHovering; }
	bool getIsInSwing()				const { return m_isInSwing; }			void setIsInSwing(bool isInSwing) { m_isInSwing = isInSwing; }
	bool getIsNearShop()			const { return m_isNearShop; }			void setIsNearShop(bool isNearShop) { m_isNearShop = isNearShop; }
	bool getIsOpening()				const { return m_isOpening; }			void setIsOpening(bool isOpening) { m_isOpening = isOpening; }
	
	bool getIsShooting()			const { return m_isShooting; }			void setIsShooting(bool isShooting) { m_isShooting = isShooting; }
	bool getIsSkidding()			const { return m_isSkidding; }			void setIsSkidding(bool isSkidding) { m_isSkidding = isSkidding; }
	bool getIsSliding()				const { return m_isSliding; }			void setIsSliding(bool isSliding) { m_isSliding = isSliding; }
	
	bool getIsThrustingForward()	const { return m_isThrustingForward; }	void setIsThrustingForward(bool isThrustingForward) { m_isThrustingForward = isThrustingForward; }
	bool getInLevelChangeArea()		const { return m_inLevelChangeArea; }	void setInLevelChangeArea(bool inLevelChangeArea) { m_inLevelChangeArea = inLevelChangeArea; }

	unsigned short getNumJumps() const { return m_numJumps; }	void setNumJumps(unsigned short numJumps) { m_numJumps = numJumps; }
	unsigned short getShopItemNumber()	const { return m_shopItemNumber; }	void setShopItemNumber(unsigned short shopItemNumber) { m_shopItemNumber = shopItemNumber; }	
	
	bool getIsTimerStopped() const { return m_isTimerStopped; }
		
	std::string const& getCollidedItemType() { return m_collidedItemType; }	

	bool getLockMelee()		const { return m_lockMelee; }			void setLockMelee(bool lockMelee)	{ m_lockMelee = lockMelee; }
	bool getLockHover()			const { return m_lockHover; }			void setLockHover(bool lockHover)	{ m_lockHover = lockHover; }
	bool getLockJump()			const { return m_lockJump; }			void setLockJump(bool lockJump)		{ m_lockJump = lockJump; }
	bool getLockShoot()			const { return m_lockShoot; }			void setLockShoot(bool lockShoot) { m_lockShoot = lockShoot; }
	bool getLockThrow()			const { return m_lockThrow; }			void setLockThrow(bool lockThrow)	{ m_lockThrow = lockThrow; }
	bool getLockThrustForward()	const { return m_lockThrustForward; }	void setLockThrustForward(bool lockThrustForward) { m_lockThrustForward = lockThrustForward; }
	bool getLockWall()			const { return m_lockWall; }			void setLockWall(bool lockWall)		{ m_lockWall = lockWall; }

	bool getUseHoverLock()	const { return m_useHoverLock; }		void setUseHoverLock(bool useHoverLock) { m_useHoverLock = useHoverLock; };
	
	float getDownThrustDelay()			const { return m_downThrustDelay; }			void setDownThrustDelay(float downThrustDelay)					{ m_downThrustDelay = downThrustDelay; };
	float getDownThrustDelayValue()		const { return m_downThrustDelayValue; }		void setDownThrustDelayValue(float downThrustDelayValue)		{ m_downThrustDelayValue = downThrustDelayValue; };
	float getDownThrustDuration()		const { return m_downThrustDuration; }		void setDownThrustDuration(float downThrustDuration)			{ m_downThrustDuration = downThrustDuration; };
	float getDownThrustDurationValue()	const { return m_downThrustDurationValue; }	void setDownThrustDurationValue(float downThrustDurationValue)	{ m_downThrustDurationValue = downThrustDurationValue; };
	float getDownThrustCooldown()		const { return m_downThrustCooldown; }			void setDownThrustCooldown(float downThrustCooldown)			{ m_downThrustCooldown = downThrustCooldown; };
	float getDownThrustCooldownValue()	const { return m_downThrustCooldownValue; }	void setDownThrustCooldownValue(float downThrustCooldownValue)	{ m_downThrustCooldownValue = downThrustCooldownValue; };

	float getDelayDig()			const { return m_delayDig; }		void setDelayDig(float delayDig)			{ m_delayDig = delayDig; };
	
	float getJumpTimeHeld()		const { return m_jumpTimeHeld; }	void setJumpTimeHeld(float jumpTimeHeld)	{ m_jumpTimeHeld = jumpTimeHeld; };
	float getJumpTimeToHold()	const { return m_jumpTimeToHold; }	void setJumpTimeToHold(float jumpTimeToHold){ m_jumpTimeToHold = jumpTimeToHold; };
	float getJumpForce()		const { return m_jumpForce; }		void setJumpForce(float jumpForce)			{ m_jumpForce = jumpForce; };
	float getJumpTime()			const { return m_jumpTime; }		void setJumpTime(float jumpTime)			{ m_jumpTime = jumpTime; };
	float getTimeSinceHitGround() const { return m_timeSinceHitGround; }		void setTimeSinceHitGround(float timeSinceHitGround) { m_timeSinceHitGround = timeSinceHitGround; }

	float getTimerMelee()			const { return m_timerMelee; }		void setTimerMelee(float timerAttack)			{ m_timerMelee = timerAttack; };
	float getTimeLimitMelee()		const { return m_timeLimitMelee; }	void setTimeLimitMelee(float timeLimitMelee)	{ m_timeLimitMelee = timeLimitMelee; };
	float getTimerDig()				const { return m_timerDig; }			void setTimerDig(float timerDig)				{ m_timerDig = timerDig; };
	float getTimerFastMovement()	const { return m_timerFastMovement; }	void setTimerFastMovement(float timerFastMovement) { m_timerFastMovement = timerFastMovement; };	
	float getTimerOpen()			const { return m_timerOpen; }			void setTimerOpen(float timerOpen)				{ m_timerOpen = timerOpen; };
	float getTimerShoot()			const { return m_timerShoot; }			void setTimerShoot(float timerShoot)			{ m_timerShoot = timerShoot; };
	float getTimeLimitShoot()		const { return m_timeLimitShoot; }		void setTimeLimitShoot(float timeLimitShoot)	{ m_timeLimitShoot = timeLimitShoot; };
	float getTimerSkidJump()		const { return m_timerSkidJump; }		void setTimerSkidJump(float timerSkidJump)		{ m_timerSkidJump = timerSkidJump; };
	float getTimerSlide()			const { return m_timerSlide; }		void setTimerSlide(float timerSlide)			{ m_timerSlide = timerSlide; };
	float getTimerSlideWall()		const { return m_timerSlideWall; }		void setTimerSlideWall(float timerSlideWall)	{ m_timerSlideWall = timerSlideWall; };
	float getTimerThrustForward()	const { return m_timerThrustForward; }	void setTimerThrustForward(float timerThrustForward) { m_timerThrustForward = timerThrustForward; };
		
	float getSprintValue()		const { return m_sprintValue; }		void setSprintValue(float sprintValue) { m_sprintValue = sprintValue; };

	float getTimePressingUp()		const { return m_timePressingUp; }		void setTimePressingUp(float timePressingUp) { m_timePressingUp = timePressingUp; }
	float getTimePressingDown()		const { return m_timePressingDown; }	void setTimePressingDown(float timePressingDown) { m_timePressingDown = timePressingDown; }
	bool getIsPressingUp()		const;	void setIsPressingUp(bool isPressingUp);
	bool getIsPressingDown()	const;	void setIsPressingDown(bool isPressingDown);
	bool getIsPressingLeft()	const;	void setIsPressingLeft(bool isPressingLeft);
	bool getIsPressingRight()	const;	void setIsPressingRight(bool isPressingRight);
	bool getIsPressingMelee()	const;	void setIsPressingMelee(bool isPressingMelee);
	bool getIsPressingJump()	const;	void setIsPressingJump(bool isPressingJump);
	bool getIsPressingSprint()	const;	void setIsPressingSprint(bool isPressingSprint);
	bool getIsPressingShoot()	const;	void setIsPressingShoot(bool isPressingShoot);
	bool getIsPressingThrow()	const;	void setIsPressingThrow(bool isPressingThrow);
	bool getIsPressingDownThrust()	const { return m_isPressingDownThrust; };	void setIsPressingDownThrust(bool isPressingDownThrust) { m_isPressingDownThrust = isPressingDownThrust; };
	bool getIsPressingWallJump()	const { return m_isPressingWallJump; };		void setIsPressingWallJump(bool isPressingWallJump) { m_isPressingWallJump = isPressingWallJump; };


private:
	cPlayerState* m_state;
	cBaseObject* m_morphObject;
	std::string m_currentLevel;
	std::string m_nextLevel;
	std::string m_collidedItemType;

	char m_vitalityMeterValue;
	char m_staminaMeterValue;

	bool m_secondCall;
	bool m_doPlayMusic0, m_doPlayMusic1;
	bool m_lockMelee, m_lockHover, m_lockJump, m_lockShoot, m_lockThrow, m_lockThrustForward, m_lockWall;
	bool m_hasDoubleJump, m_hasCollidedItem, m_hasCollidedSave, m_hasWrittenSave, m_hasHover, m_hasJumped, m_hasJumpedHigh, m_hasSprint, m_hasWhirl;
	bool m_isInDoor[4];	
	bool m_isInMap, m_isInShop;	
	bool m_isInSign[4];
	bool m_inLevelChangeArea;
	bool m_isMeleeing, m_isCrawling, m_isDigging, m_isDropping, m_isDownThrusting, m_isDucking, m_isDuckAttacking, m_isHovering, m_isInSwing, m_isOpening, m_isShooting, m_isSkidding, m_isSliding, m_isSlidingWall, m_isThrustingForward, m_isTimerStopped;
	bool m_isPressingDownThrust, m_isPressingWallJump;
	bool m_isNearShop, m_isNearSign, m_isNearDoor;	
	bool m_doStartUnlocked;
	bool m_useJumpLock, m_useHoverLock;
		
	unsigned short m_numJumps;
	unsigned short m_shopItemNumber;
	unsigned short m_startSubtractUp;
		
	float m_downThrustDuration, m_downThrustDurationValue;
	float m_downThrustDelay, m_downThrustDelayValue;
	float m_downThrustCooldown, m_downThrustCooldownValue;
	
	float m_jumpForce, m_jumpTimeToHold;
	float m_jumpTime, m_jumpTimeHeld;
	float m_sprintValue;	
	float m_timePressingUp, m_timePressingDown;
	float m_timeSinceHitGround;
	float m_timerDig, m_delayDig;
	float m_timerDrop;
	float m_timerFastMovement;
	float m_timerThrustForward;
	float m_timerTextBox;
	float m_timerMelee, m_timeLimitMelee;
	float m_timerSave;
	float m_timerSkidJump;
	float m_timerState;
	
	float m_timerShoot, m_timeLimitShoot;
	float m_timerBoost, m_timeLimitBoost;
	float m_timerOpen;
	float m_timerSlide, m_timerSlideWall;

	float m_strength;
	float m_vitality;
	float m_stamina, m_staminaCounter;
	float m_wallJumpTimer, m_wallJumpDelay;
	float m_wallJumpForceX, m_wallJumpForceY;

	std::map<std::string, float> m_staminaCost;
};