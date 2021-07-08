#include "PlayerGrassState.h"
#include "PlayerSwingState.h"
#include "PlayerMapState.h"
#include "PlayerShopState.h"
#include "RenderingManager.h"
#include "SoundsManager.h"
#include "SavesManager.h"
#include <iostream>

#include "InputManager.h"

cPlayerGrassState::cPlayerGrassState() {
	m_secondCall = false;
}

cPlayerGrassState::~cPlayerGrassState() {

}

void cPlayerGrassState::update(cApplication* application, float time, cPlayer* p) {
	//std::cout << "cPlayerGrassState::update" << std::endl;
	if (p == NULL || application == NULL) {
		return;
	}
	//p->m_velocityX = p->m_moveVelocity;
	/*if (p->m_hasBoost == true) {
		p->keysHeld[cInputManager::get().getLeftKey()] = false;
		p->keysHeld[cInputManager::get().getRightKey()] = false;
		}*/
	//std::cout << p->m_inLevelChangeArea << std::endl;
	if ((p->keysHeld[cInputManager::get().getLeftKey()] || p->keysHeld[cInputManager::get().getRightKey()] || p->m_joystickMovedX < -cInputManager::get().getJoystickDeadzone() ||  p->m_joystickMovedX > cInputManager::get().getJoystickDeadzone()) && !p->getIsDead()) {
		if (!application->getIsWidescreen() && !p->m_inLevelChangeArea) {
			cRenderingManager::get().setIsViewLocked(false);
		}
		if (p->m_tileOffsetX == 256.0f || p->m_tileOffsetX == 768.0f/* && p->m_belowObject != NULL*/) {
			//std::cout << p->m_tileOffsetX << " " << p->m_soundStepGrass.GetPlayingOffset() << std::endl;
			//if(p->m_hasJumped == false/* && p->m_velocityY <= p->m_fallAcc && p->m_velocityY > -p->m_fallAcc && (p->getVelocityX() < -0.1f || p->getVelocityX() > 0.1f)*/) {
			if (p->m_animCurrent.y == 64 && /*cSoundsManager::get().m_soundJump.getStatus() != sf::SoundSource::Playing && */cSoundsManager::get().m_soundSwingDetach.getStatus() != sf::SoundSource::Playing) {
				cSoundsManager::get().m_soundStepGrass.stop();
				cSoundsManager::get().m_soundStepGrass.play();
			}
			//}
		}
	}

	if (p->keysHeld[cInputManager::get().getLeftKey()] && p->keysHeld[cInputManager::get().getRightKey()]) {
		p->m_lockMove = true;
		p->m_isIdle = true;
	}


	if ((!p->keysHeld[cInputManager::get().getJumpKey()] && !p->mouseButtonsHeld[cInputManager::get().getJumpMouseButton()] && !p->joystickButtonsHeld[cInputManager::get().getJumpJoystickButton()]) || p->m_animCurrent.y != p->m_animHover.y) {
		cSoundsManager::get().m_soundHover.stop();
		p->m_isHovering = false;
	}

	if ((!p->keysHeld[cInputManager::get().getLeftKey()] && !p->keysHeld[cInputManager::get().getRightKey()] && p->m_joystickMovedX < cInputManager::get().getJoystickDeadzone() && p->m_joystickMovedX > -cInputManager::get().getJoystickDeadzone()) || p->m_animCurrent.y != p->m_animWall.y
		) {
		cSoundsManager::get().m_soundWallSlide.stop();
	}

	if (p->keysHeld[cInputManager::get().getUpKey()]) {
		//p->keysHeld[cInputManager::get().getUpKey()] == false;
		if (p->getInShop() == true)
			p->setState(new cPlayerShopState);
	}
	//std::cout << p->m_hasJumped << std::endl;
	
	if (p->keysHeld[cInputManager::get().getDownKey()] || p->m_joystickMovedY > cInputManager::get().getJoystickDeadzone() && !p->getIsDead() && !p->getIsDownThrusting() && !p->m_isDigging) {
		//p->setDoAnimateBackwards(false);
		std::cout << p->getVelocityY() << std::endl;
		// Not on ground
		if (cSoundsManager::get().m_soundJump.getStatus() == sf::SoundStream::Playing/* || cSoundsManager::get().m_soundBounce.getStatus() == sf::SoundStream::Playing*/
			&& p->m_staminaMeterValue >= (int)(50.0f / p->m_stamina) && !p->m_pressedDownThrust && p->m_downThrustCooldownValue >= p->m_downThrustCooldown && !p->m_onGround && !p->m_inSlope/*velocityY > p->m_fallAcc*/) {
			cSoundsManager::get().m_soundFluganCharge.stop();
			cSoundsManager::get().m_soundFluganCharge.play();
			p->m_velocityX = 0.0f;
			p->m_pressedDownThrust = true;
			p->m_downThrustDurationValue = 0;
			//p->m_isRiding = false;
			//p->m_belowObject = NULL;
			//std::cout << p->getVelocityY() << std::endl;
		}
		else {
			if (p->m_belowObject != NULL && p->m_belowObject->getType().at(0) == 's' && p->m_belowObject->getType().at(1) == 'a' && p->m_belowObject->getType().at(2) == 'n' && p->m_belowObject->getType().at(3) == 'd') {
				std::cout << "Sand below\n";
				if (p->keysHeld[cInputManager::get().getJumpKey()] || p->joystickButtonsHeld[cInputManager::get().getJumpJoystickButton()] || p->mouseButtonsHeld[cInputManager::get().getJumpMouseButton()]) {
					p->keysHeld[cInputManager::get().getJumpKey()] = false;
					p->joystickButtonsHeld[cInputManager::get().getJumpJoystickButton()] = false;
					p->mouseButtonsHeld[cInputManager::get().getJumpMouseButton()] = false;
					p->m_isDigging = true;
					p->m_pressedDownThrust = false;
					p->m_tileOffsetX = 0.0f;
					cSoundsManager::get().m_soundSwingAttach.stop();
					cSoundsManager::get().m_soundSwingAttach.play();
				}
			}
			p->m_lockMove = true;
			if (!p->keysHeld[cInputManager::get().getAttackKey()] && !p->joystickButtonsHeld[cInputManager::get().getAttackJoystickButton()] && !p->mouseButtonsHeld[cInputManager::get().getAttackMouseButton()]) {
				/*if (p->m_animCurrent != p->m_animDuck) {
					p->m_tileOffsetX = 0.0f;*/
					p->m_animCurrent = p->m_animDuck;
				//}
				p->m_isDuckAttacking = false;
			}
		}
	}
	else {
		if ((!p->keysHeld[cInputManager::get().getLeftKey()] || !p->keysHeld[cInputManager::get().getRightKey()]) && !p->m_isAttacking && !p->m_isThrowing)
			p->m_lockMove = false;
	}

	// Move left
	if ((p->keysHeld[cInputManager::get().getLeftKey()] || p->m_joystickMovedX < -cInputManager::get().getJoystickDeadzone()) && !p->getIsDead() && !p->getIsDownThrusting() && !p->m_lockMove) {
		p->m_facingLeft = true;
		p->m_isIdle = false;		

		// On ground
		if (p->m_onGround /*&& cSoundsManager::get().m_soundJump.getStatus() != sf::SoundStream::Playing*/) {
			if (p->m_hasSprint && p->m_staminaMeterValue >= (int)(2.0f/p->m_stamina) && p->keysHeld[cInputManager::get().getSprintKey()] || p->joystickButtonsHeld[cInputManager::get().getSprintJoystickButton()]) {
				if (p->m_velocityX > -p->m_moveVelocity*p->m_sprintValue) {
					p->m_velocityX -= p->m_moveAcc;
				} else if (p->m_velocityX < -(p->m_moveVelocity*p->m_sprintValue)) {
					p->m_velocityX = -(p->m_moveVelocity*p->m_sprintValue);
				}
				p->m_staminaCounter -= (2.0f / p->m_stamina);
			} else {
				if (p->m_velocityX > -p->m_moveVelocity) {
					p->m_velocityX -= p->m_moveAcc;
				} else if (p->m_velocityX < -p->m_moveVelocity) {
					p->m_velocityX = -p->m_moveVelocity;
				}
			}
		}
		else { // In air
			if (p->m_velocityX > -p->m_moveVelocity) {
				p->m_velocityX -= p->m_moveAcc*0.4f;
			} else if (p->m_velocityX < -p->m_moveVelocity) {
				if (cSoundsManager::get().m_soundJump.getStatus() == sf::SoundSource::Stopped && !p->m_hasJumped && p->m_velocityY == 0.0f) {
					p->m_velocityX = -p->m_moveVelocity;
				}
			}			
		}
	}
	// Move right
	if ((p->keysHeld[cInputManager::get().getRightKey()] || p->m_joystickMovedX > cInputManager::get().getJoystickDeadzone()) && !p->getIsDead() && !p->getIsDownThrusting() && !p->m_lockMove) {
		p->m_facingLeft = false;
		p->m_isIdle = false;

		// On ground
		if (p->m_onGround /* && cSoundsManager::get().m_soundJump.getStatus() != sf::SoundStream::Playing*/) {
			if (p->m_hasSprint && p->m_staminaMeterValue >= (int)(2.0f/p->m_stamina) && p->keysHeld[cInputManager::get().getSprintKey()] || p->joystickButtonsHeld[cInputManager::get().getSprintJoystickButton()]) {
				if (p->m_velocityX < p->m_moveVelocity*p->m_sprintValue) {
					p->m_velocityX += p->m_moveAcc;
				} else if (p->m_velocityX > p->m_moveVelocity*p->m_sprintValue) {
					p->m_velocityX = p->m_moveVelocity*p->m_sprintValue;
				}
				p->m_staminaCounter -= (2.0f / p->m_stamina);
			} else {
				if (p->m_velocityX < p->m_moveVelocity) {
					p->m_velocityX += p->m_moveAcc;
				} else if (p->m_velocityX > p->m_moveVelocity) {
					p->m_velocityX = p->m_moveVelocity;
				}
			}
		} else { // In air
			if (p->m_velocityX < p->m_moveVelocity) {
				p->m_velocityX += p->m_moveAcc*0.4f;
			} else if (p->m_velocityX > p->m_moveVelocity) {
				if (cSoundsManager::get().m_soundJump.getStatus() == sf::SoundSource::Stopped && !p->m_hasJumped && p->m_velocityY == 0.0f) {
					p->m_velocityX = p->m_moveVelocity;
				}
			}		
		}
	}

	if (p->m_lockJump && !p->keysHeld[cInputManager::get().getJumpKey()] && !p->mouseButtonsHeld[cInputManager::get().getJumpMouseButton()] && !p->joystickButtonsHeld[cInputManager::get().getJumpJoystickButton()]) {
		p->m_lockJump = false;
	}
	if (p->m_lockHover && !p->keysHeld[cInputManager::get().getJumpKey()] && !p->mouseButtonsHeld[cInputManager::get().getJumpMouseButton()] && !p->joystickButtonsHeld[cInputManager::get().getJumpJoystickButton()]) {
		p->m_lockHover = false;
	}

	// Jump
	if ((p->keysHeld[cInputManager::get().getJumpKey()] || p->mouseButtonsHeld[cInputManager::get().getJumpMouseButton()] || p->joystickButtonsHeld[cInputManager::get().getJumpJoystickButton()]) && !p->keysHeld[cInputManager::get().getDownKey()] && !p->getIsDead()) {
		//p->keysHeld[ cInputManager::get().getJumpKey() ] = false;			
		p->jump(application->getUseJumpLock(), application->getUseHoverLock());
	}

	if (!p->keysHeld[cInputManager::get().getAttackKey()] && !p->mouseButtonsHeld[cInputManager::get().getAttackMouseButton()] && !p->joystickButtonsHeld[cInputManager::get().getAttackJoystickButton()]) {
		p->m_lockAttack = false;

		/*if(p->getInSwing() == true) {
		std::cout << "not in swing\n";
		p->setInSwing(false);
		p->m_velocityY = -abs(p->m_velocityX)*1.5;
		std::cout << p->m_velocityY << std::endl;
		}*/
	}
	if (!p->keysHeld[cInputManager::get().getThrowKey()] && !p->mouseButtonsHeld[cInputManager::get().getThrowMouseButton()]) {
		p->m_lockThrow = false;
	}
	if (p->m_lockAttack || p->m_lockThrow) {
		p->keysHeld[cInputManager::get().getLeftKey()] = false;
		p->keysHeld[cInputManager::get().getRightKey()] = false;
	}
	// Attack
	if ((p->keysHeld[cInputManager::get().getAttackKey()] || p->mouseButtonsHeld[cInputManager::get().getAttackMouseButton()] || p->joystickButtonsHeld[cInputManager::get().getAttackJoystickButton()]) && !p->getIsDead() && !p->m_lockAttack) {
		p->attackMelee(application);
	}
	if (p->m_isAttacking) {
		//std::cout << "player is attacking" << std::endl;
		++p->m_timerAttack;
		if (p->m_timerAttack >= p->m_timeLimitAttack) {
			p->m_isAttacking = false;
			p->m_timerAttack = 0;
			//p->m_tileOffsetX = 0.0f;
			p->m_lockMove = false;
		}
	}
	// Throw
	if ((p->keysHeld[cInputManager::get().getThrowKey()] || p->mouseButtonsHeld[cInputManager::get().getThrowMouseButton()]) && !p->getIsDead() && !p->m_lockThrow) {
		p->attackThrow();
	}
	if (p->m_isThrowing == true) {
		//std::cout << "player is attacking" << std::endl;
		++p->m_timerThrow;
		if (p->m_timerThrow >= p->m_timeLimitThrow) {
			p->m_isThrowing = false;
			p->m_timerThrow = 0;
			//p->m_tileOffsetX = 0.0f;
			p->m_lockMove = false;
		}
	}
	// Shoot
	if ((p->keysHeld[cInputManager::get().getShootKey()] || p->mouseButtonsHeld[cInputManager::get().getShootMouseButton()])  || p->joystickButtonsHeld[cInputManager::get().getShootJoystickButton()] && !p->getIsDead()) {
		p->attackShoot();
	}
	if (p->m_isShooting) {
		//std::cout << "player is attacking" << std::endl;
		++p->m_timerShoot;
		if (p->m_timerShoot >= p->m_timeLimitShoot) {
			p->m_isShooting = false;
			p->m_timerShoot = 0;
			p->m_lockMove = false;
		}
	}

	// Gravity
	if (p->m_velocityY > 0.0f && (p->keysHeld[cInputManager::get().getJumpKey()] || p->mouseButtonsHeld[cInputManager::get().getJumpMouseButton()] || p->joystickButtonsHeld[cInputManager::get().getJumpJoystickButton()]) && p->m_hasHover && !p->m_lockHover) {
		p->m_lockJump = true;
		if (p->m_velocityY >= p->m_fallVelocity*0.25f) {
			p->m_velocityY = p->m_fallVelocity*0.25f;
		}
		else {
			p->m_velocityY += p->m_fallAcc*0.25f;
		}
	}
	else if (p->m_pressedDownThrust) {
		if (p->m_downThrustDelayValue < p->m_downThrustDelay) {
			++p->m_downThrustDelayValue;
			p->m_velocityY = 0.0f;
			p->m_velocityX = 0.0f;
			//p->m_isRiding = false;
		} else {
			if (p->m_staminaMeterValue >= (int)(50.0f / p->m_stamina)) {
				p->m_staminaMeterValue -= (int)(50.0f / p->m_stamina);
				p->m_isDownThrusting = true;
				//p->m_velocityY = p->m_fallVelocity*2.5f;
				p->m_velocityY = p->m_fallVelocity;
				p->m_downThrustDelayValue = 0;
				p->m_pressedDownThrust = false;
				p->m_downThrustCooldownValue = 0;
			}			
		}
	}
	else {
		if (p->m_velocityY >= p->m_fallVelocity) {
			p->m_velocityY = p->m_fallVelocity;
		}
		else {
			p->m_velocityY += p->m_fallAcc;
		}
	}
	if (p->m_hasJumped) {
		++p->m_jumpTime;
		if (p->m_jumpTime >= 5) {
			//p->m_tileOffsetX = 0.0f;
			p->m_hasJumped = false;
			//m_firstJump = true;
			p->m_jumpTime = 0;
		}
	}
	if (p->m_jumpHeldTime*10 < p->m_jumpHold && (p->keysHeld[cInputManager::get().getJumpKey()] || p->mouseButtonsHeld[cInputManager::get().getJumpMouseButton()] || p->joystickButtonsHeld[cInputManager::get().getJumpJoystickButton()]) && p->m_velocityY <= 0.0f) {
		p->m_velocityY -= p->m_fallAcc;
		p->m_jumpHeldTime++;
	}
	// Wall slide right
	if (p->m_inJumpWallRight && (p->keysHeld[cInputManager::get().getRightKey()] || p->m_joystickMovedX > cInputManager::get().getJoystickDeadzone())) {
		//std::cout << "wall slide right\n";
		if (p->m_velocityY >= p->m_fallVelocity*0.4f) {
			p->m_velocityY = p->m_fallVelocity*0.4f;
		}
		else {
			p->m_velocityY += p->m_fallAcc*0.4f;
		}
	}
	// Wall jump left
	if (p->m_inJumpWallRight && (p->keysHeld[cInputManager::get().getJumpKey()] || p->mouseButtonsHeld[cInputManager::get().getJumpMouseButton()] || p->joystickButtonsHeld[cInputManager::get().getJumpJoystickButton()])) {
		p->keysHeld[cInputManager::get().getJumpKey()] = false;
		p->mouseButtonsHeld[cInputManager::get().getJumpMouseButton()] = false;
		p->joystickButtonsHeld[cInputManager::get().getJumpJoystickButton()] = false;
		p->m_hasJumped = true;

		p->m_lockJump = true;
		p->m_lockHover = true;
		
		if (!p->m_pressedWallJump && cSoundsManager::get().m_soundWallSlide.getStatus() == sf::SoundStream::Playing) {
			p->m_pressedWallJump = true;
			//p->m_velocityX = 0.0f;
			//p->m_velocityY = 0.0f;
			std::cout << "Pressed wallJump left\n";
			p->m_positionX = p->m_previousX;
		}
	}
	// Wall slide left
	if (p->m_inJumpWallLeft && (p->keysHeld[cInputManager::get().getLeftKey()] || p->m_joystickMovedX < -cInputManager::get().getJoystickDeadzone()) ) {
		//std::cout << "wall slide left\n";
		if (p->m_velocityY >= p->m_fallVelocity*0.4f) {
			p->m_velocityY = p->m_fallVelocity*0.4f;
		}
		else {
			p->m_velocityY += p->m_fallAcc*0.4f;
		}
	}
	// Wall jump right
	if (p->m_inJumpWallLeft && (p->keysHeld[cInputManager::get().getJumpKey()] || p->mouseButtonsHeld[cInputManager::get().getJumpMouseButton()] || p->joystickButtonsHeld[cInputManager::get().getJumpJoystickButton()])) {
		p->keysHeld[cInputManager::get().getJumpKey()] = false;
		p->mouseButtonsHeld[cInputManager::get().getJumpMouseButton()] = false;
		p->joystickButtonsHeld[cInputManager::get().getJumpJoystickButton()] = false;
		p->m_hasJumped = true;

		p->m_lockJump = true;
		p->m_lockHover = true;

		if (p->m_pressedWallJump == false && cSoundsManager::get().m_soundWallSlide.getStatus() == sf::SoundStream::Playing) {
			p->m_pressedWallJump = true;
			//p->m_velocityX = 0.0f;
			//p->m_velocityY = 0.0f;
			std::cout << "Pressed wallJump right\n";
			p->m_positionX = p->m_previousX;
		}
	}
	// Pressed Wall jump
	if (p->m_pressedWallJump) {
		p->jumpWall(application, time);
	}

	if (p->m_velocityX > 0.0f) {	// Moving right animation
		if ((p->keysHeld[cInputManager::get().getSprintKey()] || p->joystickButtonsHeld[cInputManager::get().getSprintJoystickButton()]) && p->m_hasSprint && p->m_staminaMeterValue >= (int)(2.0f/p->m_stamina)) {
			p->m_animCurrent = p->m_animRun;
			if (p->keysHeld[cInputManager::get().getLeftKey()] || p->m_joystickMovedX < -cInputManager::get().getJoystickDeadzone() && cSoundsManager::get().m_soundJump.getStatus() != sf::SoundSource::Playing && cSoundsManager::get().m_soundSwingDetach.getStatus() != sf::SoundSource::Playing) {
				p->m_animCurrent = p->m_animTurn;
			}
		} else {
			if (p->m_velocityX > p->m_moveAcc) {
				p->m_animCurrent = p->m_animWalk;
			} else {
				p->m_animCurrent = p->m_animIdle;
			}
		}
	} else if (p->m_velocityX < 0.0f) { // Moving left animation
		if ((p->keysHeld[cInputManager::get().getSprintKey()] || p->joystickButtonsHeld[cInputManager::get().getSprintJoystickButton()]) && p->m_hasSprint && p->m_staminaMeterValue >= (int)(2.0f/p->m_stamina)) {
			p->m_animCurrent = p->m_animRun;
			if (p->keysHeld[cInputManager::get().getRightKey()] || p->m_joystickMovedX > cInputManager::get().getJoystickDeadzone() && cSoundsManager::get().m_soundJump.getStatus() != sf::SoundSource::Playing && cSoundsManager::get().m_soundSwingDetach.getStatus() != sf::SoundSource::Playing) {
				p->m_animCurrent = p->m_animTurn;
			}
		} else {
			if (p->m_velocityX < -p->m_moveAcc) {
				p->m_animCurrent = p->m_animWalk;
			} else {
				p->m_animCurrent = p->m_animIdle;
			}
		}
	} else { // Idle
		if (p->m_facingLeft) {
			if (p->m_velocityX < 0.0f) {
				if (p->m_velocityX < -p->m_moveVelocity) {
					p->m_velocityX += p->m_moveDec*0.5f;
				} else {
					p->m_velocityX += p->m_moveDec;
				}
			} else {
				p->m_velocityX = 0.0f;
			}
		} else if (!p->m_facingLeft) {
			if (p->m_velocityX > 0.0f) {
				if (p->m_velocityX > p->m_moveVelocity) {
					p->m_velocityX -= p->m_moveDec*0.5f;
				} else {
					p->m_velocityX -= p->m_moveDec;
				}
			} else {
				p->m_velocityX = 0.0f;
			}
		}
		if (!p->m_lockMove && !p->keysHeld[cInputManager::get().getDownKey()]) {
			p->m_animCurrent = p->m_animIdle;
		}
	}
	// Jumping animation
	if (p->m_velocityY < 0.2f) {
		p->m_animCurrent = p->m_animJump;
	}
	// Hover animation
	if (p->m_velocityY >= 0.5f && (p->keysHeld[cInputManager::get().getJumpKey()] || p->mouseButtonsHeld[cInputManager::get().getJumpMouseButton()] || p->joystickButtonsHeld[cInputManager::get().getJumpJoystickButton()]) && p->m_hasHover == true && p->m_lockHover == false
		/*&& !((p->m_inJumpWallLeft && p->keysHeld[sf::Keyboard::Left]) || (p->m_inJumpWallRight && p->keysHeld[sf::Keyboard::Right]))*/) {
		p->m_animCurrent = p->m_animHover;
	}
	// Falling animation
	else if (p->m_velocityY > 0.2f && (p->m_hasHover == false || p->m_lockHover == true || (!p->keysHeld[cInputManager::get().getJumpKey()] && !p->mouseButtonsHeld[cInputManager::get().getJumpMouseButton()] && !p->joystickButtonsHeld[cInputManager::get().getJumpJoystickButton()]))) {
		if (cSoundsManager::get().m_soundHover.getStatus() == sf::SoundSource::Playing)
			cSoundsManager::get().m_soundHover.stop();
		// On wall
		if ((p->m_inJumpWallLeft && (p->keysHeld[cInputManager::get().getLeftKey()] || p->m_joystickMovedX < -cInputManager::get().getJoystickDeadzone())) || (p->m_inJumpWallRight && (p->keysHeld[cInputManager::get().getRightKey()] || p->m_joystickMovedX > cInputManager::get().getJoystickDeadzone()))) {
			p->m_animCurrent = p->m_animWall;
		} else if (p->m_velocityY >= p->m_fallAcc && !p->m_onGround) {
			p->m_animCurrent = p->m_animFall;
		}
	}
	// Attack animation
	if (p->m_isAttacking) {
		//if(p->m_timerAttack <= 30 ) {
		if (p->keysHeld[cInputManager::get().getDownKey()] || p->m_joystickMovedY > cInputManager::get().getJoystickDeadzone()) {
			p->m_animCurrent = p->m_animDuckAttack;
			if (p->m_isDuckAttacking == false) {
				p->m_isDuckAttacking = true;
			}
		} else {
			p->m_animCurrent = p->m_animAttack;
			if (p->m_isDuckAttacking == true) {
				p->m_isDuckAttacking = false;
			}
		}
	}
	// Throw animation
	if (p->m_isThrowing == true) {
		p->m_animCurrent = p->m_animThrow;
	}
	// Swing animation
	/*if (p->m_inSwing == true)
	p->setIsHidden(false);
	else {
	p->setIsHidden(false);
	if (p->m_morphObject != NULL) {
	p->m_morphObject->setIsHidden(true);++p->m_downThrustCooldownValue;is
	p->m_morphObject->setTileOffsetX(512.0);
	}
	}*/
	// Ledge animation
	if (p->m_inLedge)
		p->setIsHidden(false);
	else {
		p->setIsHidden(false);
		if (p->m_morphObject != NULL) {
			p->m_morphObject->setIsHidden(true);
			p->m_morphObject->setTileOffsetX(512.0);
		}
	}
	// Downthrust
	if (p->m_isDownThrusting) {		
		if (p->m_downThrustDurationValue > p->m_downThrustDuration) {
			p->m_isDownThrusting = false;
			p->m_downThrustDurationValue = 0;
		} else {
			p->m_animCurrent = p->m_animDownThrust;
			++p->m_downThrustDurationValue;
			//p->m_downThrustCooldownValue = 0;
		}
	} else {
		++p->m_downThrustCooldownValue;
	}	
	// Digging
	if (p->m_isDigging) {
		if (p->m_diggingTimer > p->m_diggingDelay) {
			p->m_isDigging = false;			
			p->digSand();
		} else {
			++p->m_diggingTimer;
			std::cout << p->m_diggingTimer << std::endl;
			p->m_animCurrent = p->m_animDig;
		}
	}
	/*if(p->m_isDownThrusting == false && p->keysHeld[ cInputManager::get().getDownKey()] && p->keysHeld[ cInputManager::get().getJumpKey()]) {
	p->m_animCurrent = p->m_animAttack;
	}*/
	if (p->m_animCurrent.y == p->m_animHover.y && cSoundsManager::get().m_soundHover.getStatus() == sf::SoundStream::Stopped) {
		cSoundsManager::get().m_soundHover.play();
		p->m_isHovering = true;
	}
	if (p->m_animCurrent.y == p->m_animWall.y && cSoundsManager::get().m_soundWallSlide.getStatus() == sf::SoundSource::Stopped && p->getVelocityY() > 1.0f) {
		cSoundsManager::get().m_soundWallSlide.play();
	}
	if (p->m_animCurrent.y == p->m_animTurn.y && cSoundsManager::get().m_soundTurn.getStatus() == sf::SoundSource::Stopped && p->getVelocityY() <= p->getFallAcc() && p->getVelocityY() >= -p->getFallAcc()) {
		cSoundsManager::get().m_soundTurn.play();
	}
	/*if(p->m_animCurrent.y == p->m_animTurn.y && cSoundsManager::get().m_soundWallSlide.getStatus() != sf::SoundSource::Playing)
	cSoundsManager::get().m_soundWallSlide.play();*/
	if (p->getIsDead()) {
		p->m_animCurrent = p->m_animDeath;
	}	   
	// Deceleration when we are on ground
	if (p->getVelocityY() >= 0.0f && p->getVelocityY() <= p->getFallAcc()) {		
		// Deceleration when you have stopped running to the right
		if (p->m_isIdle == true && p->m_velocityX > 0.0f) {
			p->m_velocityX -= p->m_moveDec;
		}
		// Deceleration when you have stopped running to the left
		if (p->m_isIdle == true && p->m_velocityX < 0.0f) {
			p->m_velocityX += p->m_moveDec;
		}
	}

	if (p->m_hasSprint && p->m_staminaMeterValue > 0.0f) {
		if (p->m_velocityX < -p->m_moveVelocity*p->m_sprintValue) {
			p->m_velocityX = -p->m_moveVelocity*p->m_sprintValue;
		} else if (p->m_velocityX > p->m_moveVelocity*p->m_sprintValue) {
			p->m_velocityX = p->m_moveVelocity*p->m_sprintValue;
		}
	} else {
		if (p->m_velocityX < -p->m_moveVelocity) {
			p->m_velocityX = -p->m_moveVelocity;
		} else if (p->m_velocityX > p->m_moveVelocity) {
			p->m_velocityX = p->m_moveVelocity;
		}
	}
}