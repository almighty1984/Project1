#include "Player.h"
#include "PlayerGrassState.h"
#include "PlayerLedgeState.h"
#include "PlayerSwingState.h"
#include "PlayerShopState.h"
#include "RenderingManager.h"
#include "SoundsManager.h"
#include "SavesManager.h"
#include <iostream>
#include "InputManager.h"

cPlayerGrassState::cPlayerGrassState() : m_thrustX(0.0f), m_thrustY(0.0f) {
	m_secondCall = false;
}

cPlayerGrassState::~cPlayerGrassState() {

}

void cPlayerGrassState::update(cApp* app, cPlayer* p, float time) {
	//std::cout << "cPlayerGrassState::update" << "\n";
	if (p == nullptr || app == nullptr || p->getIsInShop()) {
		return;
	}
	if (!m_secondCall) {
		m_secondCall = true;
		p->setIsOnLedge(false);
		p->setDoSpawnSenses(true);
		p->setTimerState(0.0f);
		p->setSpriteOffsetY(0.0f);
		p->resetCollisionBox();
		p->setIsHidden(false);
		p->setIsUpsideDown(false);
		p->setIsInSwing(false);
		p->setIsInWater(false);
		p->setIsInWaterJump(false);

		/*if (p->getImagePath().empty() || p->getImagePath() != "Data\\Players\\Images\\player_roten.png") {
			p->setImagePath("Data\\Players\\Images\\player_roten.png");
		}*/
		if (p->getMorphObject() != nullptr) {
			p->getMorphObject()->setIsHidden(true);
			p->getMorphObject()->update(0.0f);
		}
		app->setUseEventInput(false);
		std::cout << "In grass" << "\n";
	}

	//std::cout << "cPlayerGrassState::update "  << p->getMoveDec() << " " << p->getMoveAcc() << " " << p->getStartMoveAcc() << "\n";
	p->setTimerState(p->getTimerState() + time);

	if (p->getAnimTag() == eAnimTag::walk || p->getAnimTag() == eAnimTag::run/*p->getIsPressingLeft() || p->getIsPressingRight() && !p->getIsInMap() && p->getIsOnGround()*/) {
		/*if (!app->getIsWidescreen() && !p->m_inLevelChangeArea) {
			cRenderingManager::setIsViewLocked(false);
		}*/

		for (int i = 1; i < 10; i += 3) {
			if (p->getTileOffsetX() == (float)(p->getWidth() * i)/* && p->m_belowObject != nullptr*/) {
				//std::cout << p->m_tileOffsetX << " " << p->m_soundStepGrass.GetPlayingOffset() << "\n";
				//if(p->m_hasJumped == false/* && p->m_velocityY <= p->m_fallAcc && p->m_velocityY > -p->m_fallAcc && (p->getVelocityX() < -0.1f || p->getVelocityX() > 0.1f)*/) {
				if (!cSoundsManager::isPlaying(eSoundTag::swingDetach)) {
					cSoundsManager::stop(eSoundTag::stepGrass);
					cSoundsManager::play(eSoundTag::stepGrass);
				}
				//}
			}
		}
	}

	if (!p->getIsPressingJump() || p->getAnimTag() != eAnimTag::hover) {
		cSoundsManager::stop(eSoundTag::hover);
		p->setIsHovering(false);
	}

	if (p->getIsPressingUp() && !p->getIsInMap() && p->getJoyMovedCooldownY() == 0.0f) {
		//p->setIsPressingUp(false);
		p->setJoyMovedCooldownY(10.0f);


		


		if (p->getIsCarrying()) {
			if (!p->getIsLockedOpen()) {
				p->throwCarried();
				p->setIsLockedOpen(true);
			}
		} else {
			if (p->getIsOnGround()) {
				p->attackOpen(app, time);
				if (p->getIsNearShop() && !p->getIsInShop() && !p->getIsCarrying()) {
					std::cout << "In shop now" << "\n";
					p->setIsInShop(true);
					cSoundsManager::stop(eSoundTag::hitHead);
					cSoundsManager::play(eSoundTag::hitHead);
					p->setState(new cPlayerShopState);
					return;
				}
			} else {
				if (!p->getIsThrustingForward() && !p->getLockThrustForward() && !p->getIsCarrying() && !p->getIsThrowing() && p->getStaminaMeterValue() >= (int)(20.0f / p->getStamina())) {
					p->setIsThrustingForward(true);
					cSoundsManager::play(eSoundTag::fluganCharge);
					p->setAnim(eAnimTag::duck);
					p->setTileOffsetX(0.0f);
				}
			}
			if (p->getTimePressingUp() > 20.0f && p->getAnimTag() != eAnimTag::up) {
				p->setTileOffsetX(0.0f);
				p->setAnim(eAnimTag::up);
			}

		}		
	}

	if (p->getIsThrustingForward()) {
		p->setLockThrustForward(true);

		if (m_thrustX == 0.0f) {
			m_thrustX = p->getVelocityX();
			std::cout << m_thrustX << "\n";
		}
		if (m_thrustY == 0.0f) {
			m_thrustY = p->getVelocityY();
			std::cout << m_thrustY << "\n";
		}
		p->setVelocityX(0.0f);
		p->setVelocityY(0.0f);
		p->setMovedVelocityX(0.0f);
		p->setMovedVelocityY(0.0f);
		p->setTimerThrustForward(p->getTimerThrustForward() + time);
		std::cout << "p->getTimerThrustForward() " << p->getTimerThrustForward() << "\n";
		if (p->getTimerThrustForward() > 15.0f) {
			p->decreaseMeterStamina("downThrust");
			p->setTileOffsetX(0.0f);
			p->setAnim(eAnimTag::duckAttack);
			p->setIsThrustingForward(false);
			p->setTimerThrustForward(0.0f);
			p->setTimerFastMovement(15.0f);
			cSoundsManager::play(eSoundTag::jumpHigh);

			p->setVelocityX(m_thrustX * 2.0f);
			p->setVelocityY(m_thrustY * 2.0f);
			m_thrustX = 0.0f;
			m_thrustY = 0.0f;
		}
	}



	if (p->getIsPressingDown() && p->getIsCarrying() && !p->getIsInMap()) {
		if (!p->getIsPressingMelee()) {
			p->setIsLockedMove(false);
		}
		p->setIsPressingDown(false);
		//if (/*(p->getIsFacingLeft() && p->getLeftObject() == nullptr) || (!p->getIsFacingLeft() && p->getRightObject() == nullptr)*/
			/*||
			(p->getIsFacingLeft() && p->getLeftObject() != nullptr && p->getLeftObject()->getAboveObject() == nullptr)
			||
			(!p->getIsFacingLeft() && p->getRightObject() != nullptr && p->getRightObject()->getAboveObject() == nullptr)*//*) {*/
		p->dropCarried();
		p->setIsPressingDown(false);
		p->setDownThrustCooldownValue(20.0f);	// Prevent downthrust immediately after
	//}		
	}

	p->setMoveVelocity(p->getStartMoveVelocity());

	p->setIsDucking(false);
	if (p->getIsPressingDown() && !p->getIsDownThrusting() && !p->getIsDigging() && !p->getIsInMap() && !p->getIsInSlope()) {
		//p->setIsPressingDown(false);
		//p->setDoAnimateBackwards(false);

		// Not on ground
		if (p->getStaminaMeterValue() >= (int)(50.0f / p->getStamina()) && !p->getIsPressingDownThrust() && p->getDownThrustCooldownValue() >= p->getDownThrustCooldown() && !p->getIsInWater() && !p->getIsOnGround() && !p->getIsCarrying() && !p->getIsCrawling() && p->getDelayCollisionLevel() <= 0.0f/*velocityY > p->m_fallAcc*/
			&& !cSoundsManager::isPlaying(eSoundTag::splash)
			) {

			std::cout << p->getIsInSlope() << "\n";
			cSoundsManager::stop(eSoundTag::fluganCharge);
			cSoundsManager::play(eSoundTag::fluganCharge);
			p->setVelocityX(0.0f);
			p->setIsPressingDownThrust(true);
			p->setDownThrustDurationValue(0.0f);
			//p->m_isRiding = false;
			//p->m_belowObject = nullptr;
			//std::cout << p->getVelocityY() << "\n";
		} else {
			//p->setIsLockedMove(true);
			if (!p->getIsPressingMelee() && !p->getIsCrawling() && !p->getIsDucking() && !p->getIsSliding()) {
				//std::cout << "hello" << "\n";
				if (p->getAnimTag() != eAnimTag::duck) {
					if (p->getAnimTag() == eAnimTag::crawl) {
						p->setTileOffsetX((float)((p->getWidth() * p->getNumAnimFrames()) - p->getWidth()));
					} else {
						p->setTileOffsetX(0.0f);
					}
					p->setAnim(eAnimTag::duck);
				}
				p->setIsDucking(true);
				//p->setIsDuckAttacking(false);
			}
		}
	} else {
		if (!p->getIsPressingLeft() || !p->getIsPressingRight() && !p->getIsMeleeing() && !p->getIsThrowing() && p->getTimerOpen() <= 25.0f) {
			p->setIsLockedMove(false);
		}
	}

	p->setIsCrawling(false);
	if ((p->getIsPressingDown() || p->getSenseCollidedAbove() && !p->getAboveObject()->getIsEntity()) && !p->getIsCarrying() && !p->getIsInMap()) {
		//p->setIsPressingDown(false);
		if (abs(p->getVelocityX()) < p->getStartMoveVelocity()) {	// For slide to work			
			if (p->getIsPressingLeft()) {			// Crawl left
				p->setIsCrawling(true);
				p->setIsLockedMove(false);
				//std::cout << "cPlayerGrassState crawl left" << "\n";
				p->setMoveVelocity(p->getStartMoveVelocity() * 0.5f);
				p->setAnim(eAnimTag::crawl);
				p->setIsFacingLeft(true);

				p->setIsPressingSprint(false);
			} else if (p->getIsPressingRight()) {	// Crawl right				
				p->setIsCrawling(true);
				p->setIsLockedMove(false);
				//std::cout << "cPlayerGrassState crawl right" << "\n";
				p->setMoveVelocity(p->getStartMoveVelocity() * 0.5f);
				p->setAnim(eAnimTag::crawl);
				p->setIsFacingLeft(false);
				p->setIsPressingSprint(false);
			}
		}
	}
	// Move left
	if (p->getIsPressingLeft() && !p->getIsDownThrusting() && !p->getIsInMap()) {
		p->setIsFacingLeft(true);
		p->setIsSlopeSliding(false);
		if (p->getIsOnGround()) {
			if (p->getIsPressingDown() && p->getVelocityX() < -p->getStartMoveVelocity() * 0.5f) {
				p->setVelocityX(p->getVelocityX() + p->getStartMoveDec() * 0.5f);
			} else if (p->getHasSprint() && p->hasEnoughStamina("sprint") && p->getIsPressingSprint()) {
				if (p->getVelocityX() > -p->getStartMoveVelocity() * p->getSprintValue()) {
					p->setVelocityX(p->getVelocityX() - p->getStartMoveAcc());
				} else if (p->getVelocityX() < -(p->getStartMoveVelocity() * p->getSprintValue())) {
					p->setVelocityX(-(p->getStartMoveVelocity() * p->getSprintValue()));
				}
				//p->setStaminaCounter(p->getStaminaCounter() - (2.0f / p->getStamina()));
				p->decreaseMeterStamina("sprint");
			} else {
				if (p->getVelocityX() > -p->getStartMoveVelocity()) {
					p->setVelocityX(p->getVelocityX() - p->getStartMoveAcc());
				} else if (p->getVelocityX() < -p->getMoveVelocity()) {
					p->setVelocityX(-p->getStartMoveVelocity());
				}
			}
		} else { // In air
			if (p->getVelocityX() > -p->getStartMoveVelocity()) {
				p->setVelocityX(p->getVelocityX() - p->getStartMoveAcc() * 0.4f);
			} else if (p->getVelocityX() < -p->getStartMoveVelocity()) {
				if (!cSoundsManager::isPlaying(eSoundTag::jump) && !p->getHasJumped() && p->getVelocityY() == 0.0f) {
					p->setVelocityX(-p->getStartMoveVelocity());
				}
			}
		}
	}
	// Move right
	if (p->getIsPressingRight() && !p->getIsDownThrusting() && !p->getIsInMap()) {
		p->setIsFacingLeft(false);
		p->setIsSlopeSliding(false);
		if (p->getIsOnGround()) {
			if (p->getIsPressingDown() && p->getVelocityX() > p->getStartMoveVelocity() * 0.5f) {
				p->setVelocityX(p->getVelocityX() - p->getStartMoveDec() * 0.5f);
			} else if (p->getHasSprint() && p->hasEnoughStamina("sprint") && p->getIsPressingSprint()) {
				if (p->getVelocityX() < p->getMoveVelocity() * p->getSprintValue()) {
					p->setVelocityX(p->getVelocityX() + p->getStartMoveAcc());
				} else if (p->getVelocityX() > p->getMoveVelocity() * p->getSprintValue()) {
					p->setVelocityX(p->getMoveVelocity() * p->getSprintValue());
				}
				p->decreaseMeterStamina("sprint");
			} else {
				if (p->getVelocityX() < p->getStartMoveVelocity()) {
					p->setVelocityX(p->getVelocityX() + p->getStartMoveAcc());
				} else if (p->getVelocityX() > p->getStartMoveVelocity()) {
					p->setVelocityX(p->getStartMoveVelocity());
				}
			}
		} else { // In air
			if (p->getVelocityX() < p->getMoveVelocity()) {
				p->setVelocityX(p->getVelocityX() + p->getStartMoveAcc() * 0.4f);
			} else if (p->getVelocityX() > p->getStartMoveVelocity()) {
				if (!cSoundsManager::isPlaying(eSoundTag::jump) && !p->getHasJumped() && p->getVelocityY() == 0.0f) {
					p->setVelocityX(p->getMoveVelocity());
				}
			}
		}
	}




	if (!p->getIsPressingThrow()) {
		p->setLockThrow(false);
	}
	if (p->getLockMelee() || p->getLockThrow()) {
		p->setIsPressingLeft(false);
		p->setIsPressingRight(false);
		/*p->keysHeld[cInputManager::getLeftKey()] = false;
		p->keysHeld[cInputManager::getRightKey()] = false;*/
	}
	// Attack
	if (p->getIsPressingMelee() && !p->getIsCarrying()) {
		p->attackMelee(app, time);
	}

	if (p->getIsMeleeing()) {
		p->setIsLockedMove(true);
		//std::cout << "cPlayerGrassState::update player is attacking" << "\n";
		p->setTimerMelee(p->getTimerMelee() + time);
		if (p->getTimerMelee() >= p->getTimeLimitMelee()) {
			p->setIsMeleeing(false);
			p->setTimerMelee(0.0f);
			//p->m_tileOffsetX = 0.0f;

			p->setIsLockedMove(false);
		}
	}
	// Throw
	/*if (p->m_isPressingThrow) {
		p->attackThrow();
	}*/
	if (p->getIsThrowing()) {
		p->setAnim(eAnimTag::toss);
		p->setIsCarrying(false);
		p->setIsLockedMove(true);
		std::cout << "player is throwing " << p->getTimerThrow() << "\n";
		p->setTimerThrow(p->getTimerThrow() - time);
		if (p->getTimerThrow() <= 0.0f) {
			p->setIsThrowing(false);
			p->setTimerThrow(0.0f);
			//p->m_tileOffsetX = 0.0f;
			p->setIsLockedMove(false);
		}
	}

	// Shoot
	if (p->getIsPressingShoot() && !p->getIsDead()) {
		p->attackShoot();
	}
	if (p->getIsShooting()) {
		//std::cout << "player is attacking" << "\n";
		p->setTimerShoot(p->getTimerState() + time);
		if (p->getTimerShoot() >= p->getTimeLimitShoot()) {
			p->setIsShooting(false);
			p->setTimerShoot(0.0f);
			p->setIsLockedMove(false);
		}
	}

	// Gravity
	if (p->getVelocityY() > 0.0f && p->getIsPressingJump() && p->getHasHover() && (!p->getLockHover() || !p->getUseHoverLock())) {
		//p->setLockJump(true);
		if (p->getVelocityY() >= p->getFallVelocity() * 0.25f) {
			p->setVelocityY(p->getFallVelocity() * 0.25f);
		} else {
			p->setVelocityY(p->getVelocityY() + p->getFallAcc() * 0.25f);
		}
	} else if (p->getIsPressingDownThrust()) {
		if (p->getDownThrustDelayValue() < p->getDownThrustDelay()) {
			p->setDownThrustDelayValue(p->getDownThrustDelayValue() + time);
			p->setVelocityY(0.0f);
			p->setVelocityX(0.0f);
			//p->m_isRiding = false;
			//p->setMovedVelocityX(0.0f);
			//p->setMovedVelocityY(0.0f);
			p->setIsRiding(false);
			p->setBelowObject(nullptr);
		} else {
			//if (p->getStaminaMeterValue() >= (int)(20.0f / p->getStamina())) {
			if (p->hasEnoughStamina("downThrust")) {
				p->decreaseMeterStamina("downThrust");
				//p->setStaminaMeterValue(p->getStaminaMeterValue() - (int)(20.0f / p->getStamina()));
				p->setIsDownThrusting(true);
				//p->m_velocityY = p->m_fallVelocity*2.5f;
				p->setVelocityY(p->getFallVelocity());
				p->setDownThrustDelayValue(0.0f);
				p->setIsPressingDownThrust(false);
				p->setDownThrustCooldownValue(0.0f);
			}
		}
	} else {
		if (p->getVelocityY() >= p->getFallVelocity()) {
			p->setVelocityY(p->getFallVelocity());
		} else {
			p->setVelocityY(p->getVelocityY() + p->getFallAcc());
		}
	}
	if (p->getHasJumped()) {
		p->setJumpTime(p->getJumpTime() + time);
		if (p->getJumpTime() >= 5.0f) {
			//p->m_tileOffsetX = 0.0f;
			p->setHasJumped(false);
			//m_firstJump = true;
			p->setJumpTime(0.0f);
		}
	}
	if (p->getIsPressingJump() && p->getJumpTimeHeld() < p->getJumpTimeToHold() && p->getVelocityY() <= 0.0f) {
		p->setVelocityY(p->getVelocityY() - p->getFallAcc());
		p->setJumpTimeHeld(p->getJumpTimeHeld() + time);
	}
	// Wall slide right
	if (p->getIsNearWallRight() && p->getIsPressingRight()) {
		//std::cout << "wall slide right\n";
		if (p->getVelocityY() >= p->getFallVelocity() * 0.4f) {
			p->setVelocityY(p->getFallVelocity() * 0.4f);
		} else {
			if (p->getVelocityY() > 0.0f) {
				p->setVelocityY(p->getVelocityY() + p->getFallAcc() * 0.4f);
			}
		}
	}
	// Wall jump left
	if (p->getIsNearWallRight() && p->getIsPressingJump() && p->getAnimTag() == eAnimTag::wall) {
		p->setIsPressingJump(false);
		p->setHasJumped(true);

		p->setLockJump(true);
		p->setLockHover(true);

		if (!p->getIsPressingWallJump()) {
			p->setIsPressingWallJump(true);
			//p->m_velocityX = 0.0f;
			//p->m_velocityY = 0.0f;
			std::cout << "Pressed wallJump left\n";
			p->setX(p->getPreviousX());
		}
	}
	// Wall slide left
	if (p->getIsNearWallLeft() && p->getIsPressingLeft()) {
		//std::cout << "wall slide left\n";
		if (p->getVelocityY() >= p->getFallVelocity() * 0.4f) {
			p->setVelocityY(p->getFallVelocity() * 0.4f);
		} else {
			if (p->getVelocityY() > 0.0f) {
				p->setVelocityY(p->getVelocityY() + p->getFallAcc() * 0.4f);
			}
		}
	}
	// Wall jump right
	if (p->getIsNearWallLeft() && p->getIsPressingJump() && p->getAnimTag() == eAnimTag::wall) {
		p->setIsPressingJump(false);
		p->setHasJumped(true);

		p->setLockJump(true);
		p->setLockHover(true);

		if (!p->getIsPressingWallJump() && p->getVelocityX() < 0.2f && p->getVelocityX() > -0.2f/* && cSoundsManager::isPlaying(eSoundTag::wallSlide)*/) {
			p->setIsPressingWallJump(true);
			//p->m_velocityX = 0.0f;
			//p->m_velocityY = 0.0f;
			std::cout << "Pressed wallJump right\n";
			p->setX(p->getPreviousX());
		}
	}
	// Pressed jump
	if (p->getIsPressingWallJump()) {
		p->jumpWall(app, time);
	} else {
		if (p->getIsPressingJump()) {
			p->jump();
		}
	}
	//std::cout << "PlayerGrassState::update " << p->getVelocityX() << "\n";
	if (p->getIsOnGround() || p->getIsInSlope()/*&& (p->getVelocityX() < -1.0f || p->getVelocityX() > 1.0f)*/) {
		//std::cout << p->getIsOnGround() << "\n";
		if (p->getVelocityX() > 0.0f && !p->getSenseCollidedAbove() && !p->getIsCrawling()) {
			if (p->getIsPressingSprint() && p->getHasSprint() && p->getStaminaMeterValue() >= (int)(2.0f / p->getStamina()) && !cSoundsManager::isPlaying(eSoundTag::jump)) {
				
				if (p->getIsPressingLeft()) {
					if (p->getAnimTag() != eAnimTag::turn) {
						p->setTileOffsetX(0.0f);
					}
					p->setAnim(eAnimTag::turn);
				} else {
					p->setAnim(eAnimTag::run);
				}
				if (p->getIsPressingDown()) {
					//cSoundsManager::play(eSoundTag::turn);
					p->setAnim(eAnimTag::slide);
					p->setIsSliding(true);
				} else {
					p->setIsSliding(false);
				}
			} else {
				if (!p->getIsPressingDown()) {
					if (p->getVelocityX() > p->getStartMoveAcc()) {
						p->setAnim(eAnimTag::walk);
						p->setIsSliding(false);
						p->setTimerSlide(0.0f);
					}
				}
			}
		} else if (p->getVelocityX() < 0.0f && !p->getSenseCollidedAbove() && !p->getIsCrawling()) {
			if (p->getIsPressingSprint() && p->getHasSprint() && p->getStaminaMeterValue() >= (int)(2.0f / p->getStamina()) && !cSoundsManager::isPlaying(eSoundTag::jump)) {
				
				if (p->getIsPressingRight()) {
					if (p->getAnimTag() != eAnimTag::turn) {
						p->setTileOffsetX(0.0f);
					}
					p->setAnim(eAnimTag::turn);
				} else {
					p->setAnim(eAnimTag::run);
				}
				if (p->getIsPressingDown()) {
					//cSoundsManager::play(eSoundTag::turn);
					p->setAnim(eAnimTag::slide);
					p->setIsSliding(true);
				} else {
					p->setIsSliding(false);
				}
			} else {
				if (!p->getIsPressingDown()) {
					if (p->getVelocityX() < -p->getStartMoveAcc()) {
						p->setAnim(eAnimTag::walk);
						p->setIsSliding(false);
						p->setTimerSlide(0.0f);
					}
				}
			}
		}
	}
	// Jumping animation
	if (p->getHasJumped()) {
		if (p->getHasJumpedHigh()) {
			p->setAnim(eAnimTag::jumpHigh);
		} else {
			p->setAnim(eAnimTag::jump);
		}
	}

	//std::cout << "cPlayerGrassState " << p->getVelocityY() << "\n";

	if (p->getVelocityY() >= 0.0f && !p->getIsOnGround() && !p->getIsInSlope()) {
		p->setAnim(eAnimTag::fall);
	}

	// Hover animation
	if (p->getVelocityY() > 0.0f && !p->getIsInSlope() && p->getIsPressingJump() && p->getHasHover() && !p->getIsOnGround() && (!p->getLockHover() || !p->getUseHoverLock())
		/*&& !((p->m_isNearWallLeft && p->keysHeld[sf::Keyboard::Left]) || (p->m_isNearWallRight && p->keysHeld[sf::Keyboard::Right]))*/) {
		p->setAnim(eAnimTag::hover);
	}
	// Falling animation
	else if (p->getVelocityY() > 0.2f && !p->getIsOnGround() && !p->getIsInSlope() && (!p->getHasHover() || p->getLockHover() || !p->getIsPressingJump())) {
		if (cSoundsManager::isPlaying(eSoundTag::hover)) {
			cSoundsManager::stop(eSoundTag::hover);
		}
		// On wall
		if (p->getVelocityX() < 1.0f && p->getVelocityX() > -1.0f) {
			if (p->getIsNearWallLeft() && p->getIsPressingLeft()) {
				p->setAnim(eAnimTag::wall);

			}
			if (p->getIsNearWallRight() && p->getIsPressingRight()) {
				p->setAnim(eAnimTag::wall);

			}
		}
	}

	
	/*if (p->getLeftObject() != nullptr) {
		std::cout << p->getLeftObject()->getType() << "\n";
	}
	if (p->getRightObject() != nullptr) {
		std::cout << p->getRightObject()->getType() << "\n";
	}*/
	// Attack animation
	if (p->getIsMeleeing()) {
		//if(p->m_timerMelee <= 30 ) {
		if (p->getIsPressingDown() && p->getVelocityX() == 0.0f) {
			p->setAnim(eAnimTag::duckAttack);
			if (!p->getIsDuckAttacking()) {
				p->setIsDuckAttacking(true);
			}
		} else if (!p->getIsPressingDown()) {
			p->setAnim(eAnimTag::attack);
			if (p->getIsDuckAttacking()) {
				p->setIsDuckAttacking(false);
			}
		}
	}
	// Throw animation
	if (p->getIsThrowing()) {
		p->setAnim(eAnimTag::toss);
	}

	// Downthrust
	if (p->getIsDownThrusting()) {
		if (p->getDownThrustDurationValue() > p->getDownThrustDuration()) {
			p->setIsDownThrusting(false);
			p->setDownThrustDurationValue(0.0f);
		} else {
			p->setAnim(eAnimTag::downThrust);
			p->setDownThrustDurationValue(p->getDownThrustDurationValue() + time);
			//p->m_downThrustCooldownValue = 0;
		}
	} else {
		p->setDownThrustCooldownValue(p->getDownThrustCooldownValue() + time);
		//m_downThrustCooldownValue += time;
	}
	// Digging
	if (p->getIsDigging()) {
		p->setTimerDig(p->getTimerDig() + time);
		std::cout << p->getTimerDig() << "\n";
		p->setAnim(eAnimTag::dig);
		if (p->getTimerDig() > p->getDelayDig()) {
			p->digSand();
			p->setIsDigging(false);
		}
	}
	/*if(p->m_isDownThrusting == false && p->keysHeld[ cInputManager::getDownKey()] && p->keysHeld[ cInputManager::getJumpKey()]) {
	p->m_animCurrent = p->m_animAttack;
	}*/
	if (p->getAnimTag() == eAnimTag::hover && !cSoundsManager::isPlaying(eSoundTag::hover)) {
		cSoundsManager::play(eSoundTag::hover);
		p->setIsHovering(true);
	}
	if (p->getAnimTag() == eAnimTag::wall && !cSoundsManager::isPlaying(eSoundTag::wallSlide) && p->getVelocityY() > 1.0f && p->getVelocityX() >= -0.2f && p->getVelocityX() <= 0.2f) {
		cSoundsManager::play(eSoundTag::wallSlide);
	}
	if ((!p->getIsPressingLeft() && !p->getIsPressingRight()) || p->getAnimTag() != eAnimTag::wall) {
		cSoundsManager::stop(eSoundTag::wallSlide);
	}
	if (p->getAnimTag() == eAnimTag::turn && !cSoundsManager::isPlaying(eSoundTag::turn) && p->getVelocityY() <= p->getFallAcc() && p->getVelocityY() >= -p->getFallAcc()) {
		cSoundsManager::setLoop(eSoundTag::turn, false);
		cSoundsManager::play(eSoundTag::turn);
		//if (p->getIsPressingSprint()) {
		p->setTimerSkidJump(20.0f);
		//}
	}

	if (p->getAnimTag() == eAnimTag::slide && !cSoundsManager::isPlaying(eSoundTag::turn) && (p->getVelocityX() > p->getMoveVelocity() || p->getVelocityX() < -p->getMoveVelocity())) {
		cSoundsManager::setLoop(eSoundTag::turn, false);
		cSoundsManager::play(eSoundTag::turn);
	}


	if (p->getIsDead()) {
		p->setAnim(eAnimTag::death);
	}

	/*if (p->getIsCrawling()) {
		p->setAnim(eAnimTag::crawl);
	}
	if (p->getIsPressingDown() && p->m_isIdle) {
		p->setAnim(eAnimTag::duck);
	}*/

	if (p->getTimerFastMovement() > 0.0f) {
		std::cout << "PlayerGrassState timerFastMovement: " << "\n";
		p->setTimerFastMovement(p->getTimerFastMovement() - time);
		return;
	}

	if (p->getHasSprint() && p->getStaminaMeterValue() > 0 || !p->getIsOnGround()) {
		if (p->getVelocityX() < -p->getMoveVelocity() * p->getSprintValue()) {
			p->setVelocityX( -p->getMoveVelocity() * p->getSprintValue() );
		} else if (p->getVelocityX() > p->getMoveVelocity() * p->getSprintValue()) {
			p->setVelocityX( p->getMoveVelocity() * p->getSprintValue() );
		}
	} else {
		if (p->getVelocityX() < -p->getMoveVelocity()) {
			p->setMoveVelocity(-p->getMoveVelocity());
		} else if (p->getVelocityX() > p->getMoveVelocity()) {
			p->setVelocityX(p->getMoveVelocity());
		}
	}

	if (p->getIsOnGround() && p->getIsIdle()) {
		if (p->getVelocityX() < 0.0f) {
			p->addVelocityX(p->getMoveDec());
		} else if (p->getVelocityX() > 0.0f) {
			p->addVelocityX(-p->getMoveDec());
		}
	}
	//m_velocityX *= (1.0f - m_moveDec);
	//}

	//std::cout << "cPlayerGrassState " << p->getAnim().y << "\n";

	// Change to ledge state
	if (p->getVelocityY() > 0.0f && !p->getIsOnLedge() && !cSoundsManager::isPlaying(eSoundTag::hitHead)) {	
		if (p->getVelocityX() < 1.0f && p->getVelocityX() > -1.0f) {
			//if (p->getVelocityY() < 1.0f && p->getVelocityY() > -1.0f) {
			if (p->getIsNearWallLeft() && p->getIsPressingLeft()) {
				if (p->getLeftObject() != nullptr && p->getLeftObject()->getType() == "clip_ledge_R" && p->getBottom() > p->getLeftObject()->getTop() && p->getTop()+2 < p->getLeftObject()->getTop()) {
					std::cout << "ledge left" << "\n";
					p->setState(new cPlayerLedgeState);
					return;
				}
			} else if (p->getIsNearWallRight() && p->getIsPressingRight()) {
				if (p->getRightObject() != nullptr && p->getRightObject()->getType() == "clip_ledge_L" && p->getBottom() > p->getRightObject()->getTop() && p->getTop()+2 < p->getRightObject()->getTop()) {
					std::cout << "ledge right" << "\n";
					p->setState(new cPlayerLedgeState);
					return;
				}
			}
			//}
		}
	}
}