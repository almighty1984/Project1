#include "Player.h"
#include "InputManager.h"
#include "SoundBufferManager.h"
#include "SoundsManager.h"
#include "SavesManager.h"
#include "RenderingManager.h"

#include "PlayerState.h"
#include "PlayerGrassState.h"
#include "PlayerSwingState.h"
#include "PlayerWaterState.h"
#include "PlayerShopState.h"
//#include "PlayerDeathState.h"

#include "ParticleSense.h"
#include "ParticleSenseAbove.h"

#include "MusicManager.h"

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

cPlayer::cPlayer() :	m_morphObject(nullptr), m_state(nullptr),
						m_currentLevel(""), m_nextLevel(""), m_collidedItemType(""),
						m_doPlayMusic0(false), m_doPlayMusic1(false),
						m_hasDoubleJump(false), m_hasCollidedItem(false), m_hasCollidedSave(false), m_hasWrittenSave(false), m_hasHover(false), m_hasJumped(false), m_hasSprint(false), m_hasWhirl(false),
						m_inLevelChangeArea(false), m_isInMap(false), m_isInShop(false),
						m_isNearShop(false), m_isNearSign(false), m_isNearDoor(false),
						m_isMeleeing(false), m_isCrawling(false), m_isDigging(false), m_isDropping(false), m_isDownThrusting(false), m_isDucking(false), m_isDuckAttacking(false), m_isHovering(false), m_isInSwing(false), m_isOpening(false), m_isShooting(false), m_isSkidding(false), m_isSliding(false), m_isSlidingWall(false), m_isThrustingForward(false), m_isTimerStopped(false),
						m_lockMelee(false), m_lockHover(false), m_lockJump(false), m_lockShoot(false), m_lockThrow(false), m_lockThrustForward(false), m_lockWall(false),
						m_isPressingDownThrust(false), m_isPressingWallJump(false),
						m_secondCall(false),
						m_doStartUnlocked(false),
						m_useJumpLock(false), m_useHoverLock(false),

						m_vitalityMeterValue(64),
						m_staminaMeterValue(64),
						m_numJumps(0),
						m_shopItemNumber(0),

						m_downThrustDuration(0.0f), m_downThrustDurationValue(0.0f),
						m_downThrustDelay(0.0f), m_downThrustDelayValue(0.0f),
						m_downThrustCooldown(0.0f), m_downThrustCooldownValue(0.0f),

						m_jumpForce(0.0f), m_jumpTimeToHold(0.0f),
						m_jumpTime(0.0f), m_jumpTimeHeld(0.0f),
						m_sprintValue(0.0f),						
						m_timeSinceHitGround(0.0f),
						m_timePressingUp(0.0f), m_timePressingDown(0.0f),
						m_timerTextBox(0.0f),
						m_timerMelee(0.0f), m_timeLimitMelee(0.0f),
						m_timerDig(0.0f), m_delayDig(0.0f),
						m_timerDrop(0.0f),
						m_timerFastMovement(0.0f),
						m_timerSave(0.0f),
						m_timerSkidJump(0.0f),
						m_timerState(0.0f),
						m_timerShoot(0.0f), m_timeLimitShoot(0.0f),
						m_timerBoost(0.0f), m_timeLimitBoost(0.0f),
						m_timerOpen(0.0f),
						m_timerSlide(0.0f),
						m_timerSlideWall(0.0f),
						m_timerThrustForward(0.0f),
						m_strength(0.0f),
						m_vitality(0.0f),
						m_stamina(0.0f), m_staminaCounter(0.0f),
						m_wallJumpTimer(0.0f), m_wallJumpDelay(0.0f),
						m_wallJumpForceX(0.0f), m_wallJumpForceY(0.0f) {
	std::cout << "Player()\n";
	for (unsigned char i = 0; i < 4; ++i) {
		m_isInDoor[i] = false;
		m_isInSign[i] = false;
	}
	for (unsigned short i = 0; i < 322; ++i) {
		keysHeld[i] = false;
	}
	for (unsigned short i = 0; i < 322; ++i) {
		mouseButtonsHeld[i] = false;
	}
	m_type = "player";
}
cPlayer::~cPlayer() {
	if (m_state != nullptr) {
		delete m_state;
		m_state = nullptr;
	}
}


void cPlayer::loadConfig(std::string fileName) {
	std::ifstream dataFile(fileName.c_str());

	// Verify the data file was opened; exit if not.
	if (!dataFile) {
		std::cout << "Error:  Cannot open file " << fileName << "\n";
		//exit( 1 );
	}

	std::istringstream iStr(std::ios_base::out);
	char buf[80] = { 0 };
	std::string firstField;
	std::string secondField;
	std::string data;
	std::string data2;
	std::string data3;

	while (!dataFile.eof()) {
		dataFile.getline(buf, sizeof(buf));

		iStr.str(std::string(buf));
		iStr >> firstField;
		iStr.clear();
		iStr.str("");

		if (firstField == "Config") {
			while (dataFile.peek() != '}') {
				dataFile.getline(buf, sizeof(buf));

				iStr.str(std::string(buf));
				iStr >> firstField >> secondField >> data;
				iStr.clear();
				iStr.str("");

				if (firstField == "hasDoubleJump") {
					if (data == "true") {
						m_hasDoubleJump = true;
					} else {
						m_hasDoubleJump = false;
					}
				} else if (firstField == "timeLimitAttack") {
					m_timeLimitMelee = (float)atof(data.c_str());
				} else if (firstField == "timeLimitThrow") {
					m_timeLimitThrow = (float)atof(data.c_str());
				} else if (firstField == "timeLimitShoot") {
					m_timeLimitShoot = (float)atof(data.c_str());
				} else if (firstField == "timeLimitBoost") {
					m_timeLimitBoost = (float)atof(data.c_str());
				} else if (firstField == "timeToBeDead") {
					m_timeToBeDead = (float)atof(data.c_str());
				} else if (firstField == "timeToBeIdle") {
					m_timeToBeIdle = (float)atof(data.c_str());
				} else if (firstField == "wallJumpForceX") {
					m_wallJumpForceX = (float)atof(data.c_str());
				} else if (firstField == "wallJumpForceY") {
					m_wallJumpForceY = (float)atof(data.c_str());
				} else if (firstField == "wallJumpDelay") {
					m_wallJumpDelay = (float)atof(data.c_str());
				} else if (firstField == "downThrustCooldown") {
					m_downThrustCooldown = (float)atof(data.c_str());
					m_downThrustCooldownValue = m_downThrustCooldown;
				} else if (firstField == "downThrustDuration") {
					m_downThrustDuration = (float)atof(data.c_str());
				} else if (firstField == "downThrustDelay") {
					m_downThrustDelay = (float)atof(data.c_str());
				} else if (firstField == "diggingDelay") {
					m_delayDig = (float)atof(data.c_str());
				} else if (firstField == "hurtAgainDelay") {
					m_hurtAgainDelay = (float)atof(data.c_str());
				}
			}
		} else if (firstField == "StaminaCost") {
			while (dataFile.peek() != '}') {
				dataFile.getline(buf, sizeof(buf));

				iStr.str(std::string(buf));
				iStr >> firstField >> secondField >> data;
				iStr.clear();
				iStr.str("");

				m_staminaCost[firstField] = (float)atof(data.c_str());
			}
		}

		else if (firstField == "Movement") {
			while (dataFile.peek() != '}') {
				dataFile.getline(buf, sizeof(buf));

				iStr.str(std::string(buf));
				iStr >> firstField >> secondField >> data;
				iStr.clear();
				iStr.str("");

				if (firstField == "fallVelocity") {
					m_fallVelocity = (float)atof(data.c_str());
					m_startFallVelocity = m_fallVelocity;
				} else if (firstField == "fallAcc") {
					m_fallAcc = (float)atof(data.c_str());
				} else if (firstField == "jumpForce") {
					m_jumpForce = (float)atof(data.c_str());
				} else if (firstField == "jumpTimeToHold") {
					m_jumpTimeToHold = (float)atof(data.c_str());
				} else if (firstField == "moveVelocity") {
					m_moveVelocity = (float)atof(data.c_str());
					m_startMoveVelocity = m_moveVelocity;
				} else if (firstField == "moveAcc") {
					m_moveAcc = (float)atof(data.c_str());
					m_startMoveAcc = m_moveAcc;
				} else if (firstField == "moveDec") {
					m_moveDec = (float)atof(data.c_str());
					m_startMoveDec = m_moveDec;
				} else if (firstField == "sprintValue") {
					m_sprintValue = (float)atof(data.c_str());
				}
			}
		} else if (firstField == "Collision") {
			while (dataFile.peek() != '}') {
				dataFile.getline(buf, sizeof(buf));

				iStr.str(std::string(buf));
				iStr >> firstField >> secondField >> data;
				iStr.clear();
				iStr.str("");

				bool isTrue = false;
				if (data == "true" || data == "True" || data == "TRUE") {
					isTrue = true;
				}

				if (firstField == "isSolid") {
					if (isTrue) {
						m_isSolidEntityX = m_isSolidEntityY = true;
						m_isSolidPlayerX = m_isSolidPlayerY = true;
						m_isSolidLevelX = m_isSolidLevelY = true;
					} else {
						m_isSolidEntityX = m_isSolidEntityY = false;
						m_isSolidPlayerX = m_isSolidPlayerY = false;
						m_isSolidLevelX = m_isSolidLevelY = false;
					}
				} else if (firstField == "isSolidX") {
					if (isTrue) {
						m_isSolidEntityX = m_isSolidPlayerX = m_isSolidLevelX = true;
					} else {
						m_isSolidEntityX = m_isSolidPlayerX = m_isSolidLevelX = false;
					}
				} else if (firstField == "isSolidY") {
					if (isTrue) {
						m_isSolidEntityY = m_isSolidPlayerY = m_isSolidLevelY = true;
					} else {
						m_isSolidEntityY = m_isSolidPlayerY = m_isSolidLevelY = false;
					}
				} else if (firstField == "subtractLeft") {
					if (data.at(0) == '-') {
						data.erase(data.begin(), data.begin() + 1);
						m_subtractLeft = -atoi(data.c_str());
					} else {
						m_subtractLeft = atoi(data.c_str());
					}
					m_startSubtractLeft = m_subtractLeft;
				} else if (firstField == "subtractRight") {
					if (data.at(0) == '-') {
						data.erase(data.begin(), data.begin() + 1);
						m_subtractRight = -atoi(data.c_str());
					} else {
						m_subtractRight = atoi(data.c_str());
					}
					m_startSubtractRight = m_subtractRight;
				} else if (firstField == "subtractUp") {
					if (data.at(0) == '-') {
						data.erase(data.begin(), data.begin() + 1);
						m_subtractUp = -atoi(data.c_str());
					} else {
						m_subtractUp = atoi(data.c_str());
					}
					m_startSubtractUp = m_subtractUp;
				} else if (firstField == "subtractDown") {
					if (data.at(0) == '-') {
						data.erase(data.begin(), data.begin() + 1);
						m_subtractDown = -atoi(data.c_str());
					} else {
						m_subtractDown = atoi(data.c_str());
					}
					m_startSubtractDown = m_subtractDown;
				}
			}
		} else if (firstField == "Image") {
			while (dataFile.peek() != '}') {
				dataFile.getline(buf, sizeof(buf));

				iStr.str(std::string(buf));
				iStr >> firstField >> secondField >> data;
				iStr.clear();
				iStr.str("");

				if (firstField == "path") {
					setImagePath(data);
				} else if (firstField == "width") {
					m_width = atoi(data.c_str());
				} else if (firstField == "height") {
					m_height = atoi(data.c_str());
				}
			}
		} else if (firstField == "Animation" || firstField == "Anim") {
			while (dataFile.peek() != '}') {
				dataFile.getline(buf, sizeof(buf));

				iStr.str(std::string(buf));
				iStr >> firstField >> secondField >> data >> data2 >> data3;
				iStr.clear();
				iStr.str("");
				if (firstField == "numFrames") {
					m_numAnimFrames = atoi(data.c_str());
				} else {
					createAnim(firstField, atoi(data.c_str()), (float)atof(data2.c_str()), atoi(data3.c_str()));
				}

			}
		} else if (firstField == "Shader") {
			//m_doUseShader = true;
			while (dataFile.peek() != '}') {
				dataFile.getline(buf, sizeof(buf));

				iStr.str(std::string(buf));
				iStr >> firstField >> secondField >> data >> data2 >> data3;
				iStr.clear();
				iStr.str("");

				if (firstField == "path") {
					m_pathShader = data;
					m_shader.load(data, "Fragment");
					//m_sfShader.loadFromFile(m_pathShader, sf::Shader::Type::Fragment);
				}
			}
		}
	}
	dataFile.close();
}

void cPlayer::setState(cPlayerState* state) {
	if (m_state != nullptr) {
		delete m_state;
		m_state = nullptr;
	}
	m_state = state;
}

void cPlayer::update(cApp* app, float time) {
	//std::cout << m_timerState << "\n";
	if (!m_secondCall) {
		m_secondCall = true;
		m_hasHover = cSavesManager::getHasHover();
		m_hasSprint = cSavesManager::getHasSprint();
		m_hasWhirl = cSavesManager::getHasWhirl();

		m_useJumpLock = app->getUseJumpLock();
		m_useHoverLock = app->getUseHoverLock();
	}

	if (m_isCarrying) {
		if (m_carriedObject != nullptr) {
			if (!m_carriedObject->getIsCarried() || m_carriedObject->getCarrier() != this) {
				m_isCarrying = false;
				m_carriedObject = nullptr;
			}
		}
	}


	if (m_hasCollidedSave) {
		save(app);
		m_hasCollidedSave = false;
	}
	if (m_hasWrittenSave) {
		//std::cout << m_timerSave << "\n";
		if (m_timerSave <= 0) {
			m_hasWrittenSave = false;
		} else {
			--m_timerSave;
		}
	}

	if (m_timerOpen > 0.0f/* && !(getAnimTag() == eAnimTag::open && m_tileOffsetX == m_width*m_numAnimFrames - m_width)*/) {
		m_timerOpen -= time;
		m_isLockedOpen = true;
		m_isOpening = true;
		//setAnim(eAnimTag::open);
	} else {
		m_timerOpen = 0.0f;
		m_isOpening = false;
		if (!getIsPressingUp()) {
			m_isLockedOpen = false;
		}
	}

	if (!m_isDead) {
		if (!getIsPressingMelee()) {
			m_lockMelee = false;
		}
	}

	if (!getIsPressingJump()) {
		if (m_isOnGround || m_isOnLedge) {
			m_lockJump = false;
		} else {
			m_lockHover = false;
		}
	}

	if (getIsPressingUp()) {
		m_timePressingUp += time;
	} else {
		m_timePressingUp = 0.0f;
	}

	if (getIsPressingDown()) {
		m_timePressingDown += time;
		if (m_isInSlope) {
			m_isSlopeSliding = true;
		}
	} else {
		m_timePressingDown = 0.0f;
	}

	if (!getIsPressingShoot()) {
		m_lockShoot = false;
	}

	/*if (m_velocityX == 0.0f) {
		m_isSlopeSliding = false;
	}*/
	//std::cout << m_isInSlope << "\n";
	if (m_isInSlope) {
		m_isOnGround = true;
		/*if (m_velocityY >= m_fallVelocity / 2) {
			m_isInSlope = false;
		}*/
		if (m_isSlopeSliding) {
			m_velocityY += 2.0f;
		}
	}	
		
	// Mostly needed when running off a slope ledge, to prevent running in the air
	if (m_velocityY >= 4.0f) {
		m_belowObject = nullptr;
		m_isOnGround = false;
		m_isInSlope = false;
	}
	//std::cout << m_velocityY << "\n";	

	/*if (!m_isMeleeing) {
		m_isLockedMove = false;
	}*/	

	if (m_isOnGround && m_isLockedMove) {
		if (m_velocityX < 0.0f) {
			m_velocityX += (m_moveDec * 2.0f);
		} else if (m_velocityX > 0.0f) {
			m_velocityX -= (m_moveDec * 2.0f);
		}		
		//m_velocityX = 0.0f;
	}

	//std::cout << m_isInSlope << " " << m_isSlopeSliding << "\n";

	//std::cout << "cPlayer::update " << m_isLockedMove << "\n";
	if (m_isLockedMove && m_isOnGround) {
		setIsPressingLeft(false);
		setIsPressingRight(false);
	}

	if (m_timerSkidJump > 0.0f) {
		std::cout << m_timerSkidJump << "\n";
		m_timerSkidJump -= time;
		m_isSkidding = true;
		m_moveDec = m_startMoveDec * 0.25f;
	} else {
		m_timerSkidJump = 0.0f;
		m_isSkidding = false;
	}

	if (m_isSliding) {
		setIsPressingLeft(false);
		setIsPressingRight(false);
		m_timePressingDown = 0.0f;
		m_staminaMeterValue -= (int)(1.0f / m_stamina);
		m_moveDec = m_startMoveDec * 0.25f;
		//setAnim(eAnimTag::jump);
		if (m_timerSlide <= 0.0f) {
			m_tileOffsetX = 0.0f;
		}
		std::cout << "cPlayer::update sliding " << m_timerSlide << "\n";
		m_timerSlide += time;

		if (m_velocityX > -m_startMoveVelocity * 0.5f && m_velocityX < m_startMoveVelocity * 0.5f) {
			setAnim(eAnimTag::duck);
			m_tileOffsetX = (float)(m_numAnimFrames * m_width - m_width);
			//m_velocityX = 0.0f;
			m_isSliding = false;
			m_timerSlide = 0.0f;
			//m_movedVelocityX = 0.0f;
		}
	}
	if (!m_isSkidding && !m_isSliding) {
		m_moveDec = m_startMoveDec;
	}
	if (m_isSlidingWall) {
		m_timerSlideWall += time;
		if (getAnimTag() != eAnimTag::wall) {
			m_isSlidingWall = false;
			m_timerSlideWall = 0.0f;
		}
	}
	//std::cout << m_isOnGround << "\n";

	if (m_isDropping) {
		//std::cout << "Player::update " << m_timerDrop << "\n";
		m_timerDrop += time;
		if (getAnimTag() != eAnimTag::duck) {
			setTileOffsetX(0.0f);
			setAnim(eAnimTag::duck);
			setAnimSpeed(getAnimSpeed() * 2.0f);
		}
		if (m_timerDrop > 15.0f) {
			m_timerDrop = 0.0f;
			m_isDropping = false;
		}
	}

	// Decrease height from top if ducking, crawling or sliding
	if (!m_isInWater && !m_isInWaterJump) {
		if (getAnimTag() == eAnimTag::slide || getAnimTag() == eAnimTag::duck || getAnimTag() == eAnimTag::crawl || m_isDucking || m_isCrawling) {
			m_subtractUp = m_height - 16;
		} else {
			m_subtractUp = m_startSubtractUp;
		}
	}

	if (m_velocityY > m_fallAcc && !m_isInSlope) {
		m_isOnGround = false;
	}

	if (getAnimTag() == eAnimTag::wall) {
		m_fallVelocity = m_startFallVelocity * 0.75f;
	} else {
		m_fallVelocity = m_startFallVelocity;
	}

	if (m_delayCollisionLevel > 0.0f) {
		m_isSolidLevelY = false;
		m_delayCollisionLevel -= time;
		m_velocityX = 0.0f;
	} else {
		m_delayCollisionLevel = 0.0f;
		m_isSolidLevelY = true;
	}
	if (m_delayCollisionEntity > 0.0f) {
		m_isSolidEntityY = false;
		m_delayCollisionEntity -= time;
	} else {
		m_delayCollisionEntity = 0.0f;
		m_isSolidEntityY = true;
	}

	if (m_isInSwing) {
		m_isHidden = true;
		if (m_morphObject != nullptr) {
			m_morphObject->setIsHidden(false);
		}
	}

	if (m_isIdle) {
		//std::cout << m_timeBeingIdle << "\n";
		m_timeBeingIdle += time;
	} else {
		m_timeBeingIdle = 0.0f;
	}

	if (m_joyMovedCooldownX > 0.0f) {
		m_joyMovedCooldownX -= time;
	} else {
		m_joyMovedCooldownX = 0.0f;
	}
	if (m_joyMovedCooldownY > 0.0f) {
		m_joyMovedCooldownY -= time;
	} else {
		m_joyMovedCooldownY = 0.0f;
	}

	if (m_isInWater || (getIsPressingJump() && !getIsPressingDown()) && !getIsDead()) {
		m_isSlopeSliding = false;
	}

	if (m_velocityY < 0.0f) {
		m_isOnGround = false;
		m_isInSlope = false;
	}
	m_staminaCounter += /*(m_stamina*0.5f)**/time * 1.0f;
	if (m_staminaCounter > 1.0f || m_staminaCounter < -1.0f) {
		m_staminaMeterValue += (int)m_staminaCounter;
		m_staminaCounter = 0.0f;
	}
	if (m_staminaMeterValue <= 0) {
		m_staminaMeterValue = 0;
	}
	if (m_staminaMeterValue >= 64) {
		m_staminaMeterValue = 64;
	}

	if (m_isDead) {
		m_timeBeingDead += time;
	} else {
		m_timeBeingAlive += time;
	}

	// Player death
	if (m_vitalityMeterValue <= 0) {
		m_vitalityMeterValue = 0;
		m_tileOffsetX = 0.0f;
		m_velocityX = 0.0f;
		m_movedVelocityX = 0.0f;
		setAnim(eAnimTag::death);
		if (!m_isDead) {
			m_isDead = true;
			m_isRiding = false;

			cSoundsManager::play(eSoundTag::fluganHurt1);
			//cMusicManager::stopMusic0();
			//app->sleep(500);
			app->setWeatherColor(0.0f);

		}

		/*m_velocityX = 0.0f;
		m_velocityY = 0.0f;*/

		//setState(new cPlayerDeathState);

		// Super Mario Bros style death
		if (m_timeBeingDead > 0.0f && m_timeBeingDead <= 40.0f) {
			m_velocityY = 0.0f;
			m_movedVelocityY = 0.0f;
		} else if (m_timeBeingDead > 40.0f && m_timeBeingDead < 45.0f) {
			//m_isRiding = false;
			m_velocityY = -5.0f;
			//m_velocityX = 0.0f;
		}
	}

	//std::cout << "cPlayer::update" << (int)m_vitalityMeterValue << "\n";

	if (m_vitalityMeterValue >= 64) {
		m_vitalityMeterValue = 64;
	}
	m_numHealth = (float)m_vitalityMeterValue;

	//std::cout << m_isNearWallLeft << " " << m_isNearWallRight << "\n";	

	if (m_hurtAgainDelayValue > 0.0f) {
		m_isHurting = true;
		m_hurtAgainDelayValue -= time;
		m_doUseShader = true;
	} else {
		m_isHurting = false;
		m_hurtAgainDelayValue = 0.0f;
		m_doUseShader = false;
		//std::cout << m_hurtAgainDelayValue << "\n";
	}
	//std::cout << m_x << "\n";
	if (m_hasCollidedItem) {
		cSavesManager::setHasHover(m_hasHover);
		cSavesManager::setHasSprint(m_hasSprint);
		cSavesManager::setHasWhirl(m_hasWhirl);

		if (m_timerTextBox < 0.0f) {
			m_hasCollidedItem = false;
			m_timerTextBox = 0;
		} else {
			m_timerTextBox -= time;
		}
	}

	// Stop at very small velocity
	if (!getIsPressingLeft() && !getIsPressingRight() && !getIsPressingJump() && !m_isSkidding && !m_isSliding && !m_hasJumped && !m_isRiding) {
		/*if (m_isOnGround && !m_isCrawling && !m_isDucking && !m_isDropping && m_isIdle && !m_isOpening && getAnimTag() != eAnimTag::idle) {
			if (m_aboveObject == nullptr || (m_aboveObject != nullptr && m_aboveObject->getIsEntity())) {
				setAnim(eAnimTag::idle);				
			}
		}*/

		m_isIdle = true;
		m_isCrawling = false;
		m_isDucking = false;


		//if (!m_isRiding) {
		if (m_velocityX > -m_moveAcc && m_velocityX < m_moveAcc) {
			m_velocityX = 0.0f;
			m_isSliding = false;
			//m_movedVelocityX = 0.0f;
		}
		//}		
	} else {
		m_isIdle = false;
	}



	if (m_isLocked) {
		//m_velocityX = 0.0f;
		//m_velocityY = 0.0f;
		m_tileOffsetX = 0.0f;
		m_tileOffsetY = 0.0f;
	} else {
		if (m_state != nullptr) {
			//std::cout << "cPlayer::update " << m_moveAcc << " " << m_startMoveAcc << "\n";
			m_state->update(app, this, time);
		}
	}
	
	/*if (m_velocityY > 0.0f) {
		m_isOnGround = false;
	}*/
	//std::cout << m_timeSinceHitGround << "\n";

	if (m_timeSinceHitGround > 4.0f) {
		m_numJumps = 0;
	}
	// Deceleration when we are on ground
	if ((m_isOnGround || m_isInSlope) /*&& m_velocityY >= 0.0f && m_velocityY <= getFallAcc()*/) {
		m_timeSinceHitGround += time;
		
		if (!getIsPressingRight() && m_velocityX >= m_moveDec) {
			m_velocityX -= m_moveDec;
		}
		if (!getIsPressingLeft() && m_velocityX <= -m_moveDec) {
			m_velocityX += m_moveDec;
		}

		//if (!getIsPressingLeft() && !getIsPressingRight()) {
			if (m_velocityX < m_moveDec && m_velocityX > -m_moveDec) {
				m_velocityX = 0.0f;
				m_isSkidding = false;
				m_isSliding = false;
				if (!m_isMeleeing && !m_isCrawling && !m_isDucking && !m_isDropping && !m_isOpening && !m_isSliding && !m_isSlopeSliding) {
					
					if (!getIsPressingUp() && !getIsPressingDown()) {
						setAnim(eAnimTag::idle);
					}
					m_isIdle = true;
				}
			}
		//}
	}
	//if (m_leftObject != nullptr) {
	//	if (m_leftObject->getAboveObject() != nullptr) {
	//		std::cout << m_leftObject->getAboveObject()->getType() << "\n";
	//	}/* else {
	//		std::cout << m_leftObject->getType() << "\n";
	//	}*/

	//}
	//if (m_rightObject != nullptr) {
	//	if (m_rightObject->getAboveObject() != nullptr) {
	//		std::cout << m_rightObject->getAboveObject()->getType() << "\n";
	//	}/* else {
	//		std::cout << m_rightObject->getType() << "\n";
	//	}*/

	//}


	if (!m_isInWater) {
		setTimerSense(getTimerSense() + time);
	}
	if (getTimerSense() > 1.0f && m_attachedLevel != nullptr && !m_isDead) {
		//m_isNearWallLeft = false;
		//m_isNearWallRight = false;
		setTimerSense(0.0f);

		if (getDoSpawnSenses()) {
			spawnSenses();
		}
		
	}
	

	m_senseCollidedLeft ? m_isNearWallLeft = true : m_isNearWallLeft = false;
	m_senseCollidedRight ? m_isNearWallRight = true : m_isNearWallRight = false;

	if (m_senseCollidedLeft || m_senseCollidedRight || m_senseCollidedAbove/* && m_velocityX < 0.2f && m_velocityX > -0.2f && !m_isOnGround*/) {
		if (m_senseCollidedAbove && (m_isOnGround || m_isInSlope) && !m_isSlopeSliding && !m_isSliding) {
			if (m_isIdle) {
				if (m_isCarrying) {
					setAnim(eAnimTag::idle);
				} else {
					if (m_aboveObject != nullptr && m_aboveObject->getType() == "clip_crawl") {
						m_tileOffsetX = (float)(m_width * m_numAnimFrames - m_width);
						setAnim(eAnimTag::duck);
						m_isDucking = true;
					}
				}
			}
		}
		//clearSense();
	} else {
		/*if (!m_isPressingDown) {
			m_isCrawling = false;
		}*/
		/*if (!getIsPressingDown() && !getIsPressingLeft() && !getIsPressingRight() &&
			!m_senseCollidedAbove && m_isIdle && m_isOnGround &&
			!m_isMeleeing && !m_isCrawling && !m_isHovering &&	!m_hasJumped &&
			m_velocityX < m_moveAcc && m_velocityX > -m_moveAcc) {
			setAnim(eAnimTag::idle);
		}*/
		/*if (m_velocityX < -1.0f) {
			m_isNearWallRight = false;
		}
		if (m_velocityX > 1.0f) {
			m_isNearWallLeft = false;
		}*/
		//clearSense();
	}

	//std::cout << "cPlayer::update" << "\n";
	m_previousX = m_x;
	m_previousY = m_y;

	//	//std::cout << cGlobals::get().m_quadNode.getNodeAt( m_levelX+app->getViewWidth()/2, m_levelY+app->getViewHeight()/2).id << " " << cGlobals::get().m_quadNode.getNodeAt( m_levelX+app->getViewWidth()/2, m_levelY+app->getViewHeight()/2).level << "\n";

	m_x += (m_velocityX + m_movedVelocityX)/**time*/;
	m_y += (m_velocityY + m_movedVelocityY)/**time*/;

	//std::cout << m_levelX << " " << m_levelY << "\n";

	if (m_attachedLevel != nullptr) {
		m_levelX = m_startX + (m_x - m_startX) + m_attachedLevel->getX();
		m_levelY = m_startY + (m_y - m_startY) + m_attachedLevel->getY();
	}
	//std::cout << m_velocityX << "\n";	

	if (m_isInWaterJump) {
		m_tileOffsetX = 0.0f;
		m_isAnim = false;
	} else {
		m_isAnim = true;
	}

	if (m_isSlopeSliding) {
		setAnim(eAnimTag::fall);
	}


	// Update animation		
	if (m_isAnim && m_animTime >= 10.0f) {
		m_tileOffsetX += m_width;
		if (m_tileOffsetX >= (m_width * m_numAnimFrames - m_width)) {
			m_hasJumpedHigh = false;
			if (m_currentLoops < m_numAnimLoops && m_numAnimLoops != 0) {
				//m_tileOffsetX = 0;
				m_tileOffsetX = (float)(m_width * m_numAnimFrames - m_width);
				m_currentLoops += 1;
			} else if (m_numAnimLoops == 0) {
				m_tileOffsetX = 0.0f;
				m_currentLoops = 0;
			}
		}
		m_animTime = 0.0f;
	} else {
		m_animTime += m_animSpeed;
	}

	if (m_tileOffsetX >= (m_width * m_numAnimFrames) - m_width) {
		m_tileOffsetX = (float)(m_width * m_numAnimFrames - m_width);
	}
	if (m_tileOffsetX <= 0.0f || m_animSpeed == 0.0f) {
		m_tileOffsetX = 0.0f;
	}
	//std::cout << "cPlayer m_doStartUnlocked = " << m_doStartUnlocked << "\n";

	setTimerSenseClear(getTimerSenseClear() + time);
	if (getTimerSenseClear() > 1.0f && !m_isDead) {
		setTimerSenseClear(0.0f);

		if (getDoSpawnSenses()) {
			clearSenseAbove();
			if (m_velocityX + m_movedVelocityX > 0.0f) {
				clearSenseLeft();
				/*if (m_leftObject == nullptr) {
					clearSenseAbove();
				}*/
			}
			if (m_velocityX + m_movedVelocityX < 0.0f) {
				clearSenseRight();
				/*if (m_rightObject == nullptr) {
					clearSenseAbove();
				}*/
			}
			clearSenses();
		}
		for (unsigned char i = 0; i < 4; ++i) {
			m_isInSign[i] = false;
		}
		m_isNearSign = false;
		m_isNearShop = false;
	}
	


	// Limit movement speed
	float moveVelocity = m_moveVelocity;
	if (m_isCrawling) {
		moveVelocity *= 0.5f;
		m_timePressingDown = 0.0f;
	} else if (getIsPressingSprint() || !m_isOnGround) {
		moveVelocity *= m_sprintValue;
	}
	if (m_isFacingLeft && m_velocityX < -moveVelocity) {
		//std::cout << "cPlayer::update Limited to " << -moveVelocity << "\n";
		m_velocityX = -moveVelocity;
	} else if (!getIsFacingLeft() && m_velocityX > moveVelocity) {
		//std::cout << "cPlayer::update Limited to " << moveVelocity << "\n";
		m_velocityX = moveVelocity;
	}

	if (m_velocityY < -m_fallVelocity) {
		m_velocityY = -m_fallVelocity;
	} else if (m_velocityY > m_fallVelocity) {
		m_velocityY = m_fallVelocity;
	}

	
}