#include "Player.h"

#include "InputManager.h"
#include "SoundBufferManager.h"
#include "SoundsManager.h"
#include "SavesManager.h"
#include "RenderingManager.h"

#include "PlayerGrassState.h"
#include "PlayerWaterState.h"
#include "PlayerWaterJumpState.h"
#include "PlayerShopState.h"

#include "MusicManager.h"

#include "EntityFluganChargeState.h"
#include "EntityFlylingFlightState.h"
#include "EntityFlylingChargeState.h"
#include "EntityFlylingBounceState.h"

#include "EntityItem.h"

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

void cPlayer::collisionReactionY(cBaseObject* object) {
	if (object->getIsSlope()) {
		collisionReactionSlopeY(object);
		return;
	}
	//std::cout << "cPlayer::collisionReactionY " << object->getType() << "\n";

	if ( //object->getType() == "wall_L_in" ||
		//object->getType() == "wall_R_in" ||
		object->getType() == "clip_bot" ||
		object->getType() == "clip_left" || object->getType() == "clip_right" ||
		object->getType() == "swing" ||
		object->getType() == "lever" ||
		object->getType().substr(0, 6) == "music_" ||
		object->getType().substr(0, 10) == "shop_item_") {
		return;
	} else if (object->getType() == "cam_lock_y") {
		collisionReactionX(object);
	} else if (object->getType() == "cam_unlock_y") {
		collisionReactionX(object);
	} else if (object->getType() == "view_lock") {
		collisionReactionX(object);
	} else if (object->getType() == "view_unlock") {
		collisionReactionX(object);
	} else if (object->getType() == "cam_lock") {
		collisionReactionX(object);
	} else if (object->getType() == "cam_lock_ws") {
		collisionReactionX(object);
	} else if (object->getType() == "cam_unlock") {
		collisionReactionX(object);
	} else if (object->getType() == "cam_unlock_ws") {
		collisionReactionX(object);
	} else if (object->getType() == "cam_scroll_up") {
		collisionReactionX(object);
	} else if (object->getType() == "cam_scroll_down") {
		collisionReactionX(object);
	} else if (object->getType() == "cam_reset_y") {
		collisionReactionX(object);
	} else if (object->getType() == "death") {
		m_velocityY *= -1.0f;
		/*if (!m_isDead) {
			m_isDead = true;
			m_tileOffsetX = 0.0f;
		}*/
	} else if (object->getType() == "level_bottom_0" || object->getType() == "level_bottom_1" || object->getType() == "level_bottom_2" || object->getType() == "level_bottom_3" || object->getType() == "level_top_0" || object->getType() == "level_top_1" || object->getType() == "level_top_2" || object->getType() == "level_top_3" || object->getType() == "level_left_0" || object->getType() == "level_left_1" || object->getType() == "level_left_2" || object->getType() == "level_left_3" || object->getType() == "level_right_0" || object->getType() == "level_right_1" || object->getType() == "level_right_2" || object->getType() == "level_right_3") {
		//if(m_nextLevel != object->getType())
		m_nextLevel = object->getType();
	} else if (object->getType() == "boost") {
		collisionReactionX(object);
	} else if (object->getType().substr(0, 6) == "chest_") {
		return;
	} else if (object->getType().substr(0, 5) == "door_") {
		collisionReactionX(object);
	} else if (object->getType() == "level_start") {
		collisionReactionX(object);
	} else if (object->getType() == "flag") {
		return;
	} else if (object->getType().at(0) == 'c' && object->getType().at(1) == 'o' && object->getType().at(2) == 'i' && object->getType().at(3) == 'n') {
		collisionReactionX(object);
	} else if (object->getType() == "item_sprint" || object->getType() == "item_hover" || object->getType() == "item_whirl") {
		collisionReactionX(object);
	} else if (object->getType().substr(0, 4) == "sign" && object->getType().size() == 6) {
		collisionReactionX(object);
	} else if (object->getType() == "sign_exit") {
		collisionReactionX(object);
	} else if (object->getType() == "water") {
		if (!m_isInWater/* && m_velocityY > 0.0f*//* && m_timerState > 10.0f*/) {
			m_isPressingDownThrust = false;
			m_isDownThrusting = false;
			m_isInWater = true;
			setState(new cPlayerWaterState);
		}
	} else if (object->getType() == "water_in") {
		if (!m_isInWater/* && m_timerState > 10.0f*/) {
			//m_y = object->getBottom()-m_height;
			m_isPressingDownThrust = false;
			m_isDownThrusting = false;
			/*if (m_velocityY > 2.0f) {
				m_velocityY = 2.0f;
			}*/
			//m_velocityY = 4.0f;

			m_isInWater = true;
			//std::cout << m_isInWater << "\n";
			setState(new cPlayerWaterState);
			//m_velocityY = m_fallVelocity * 0.5f;

			if (m_velocityY > 0.0f /*&& m_timerState > 4.0f*/ && !cSoundsManager::isPlaying(eSoundTag::splash)) {
				cLevel* level = m_attachedLevel;
				if (level == nullptr) { return; };
				level->addParticle(new cParticle);
				level->getParticleLast()->loadConfig("Data\\Particles\\p_splash.cfg");
				level->getParticleLast()->setX(object->getX());
				level->getParticleLast()->setY(object->getY() - 16);
				level->getParticleLast()->update(0.0f);

				level->addParticle(new cParticle);
				level->getParticleLast()->loadConfig("Data\\Particles\\p_dust.cfg");
				level->getParticleLast()->attachParent(this);
				level->getParticleLast()->setX(object->getX());
				level->getParticleLast()->setY(object->getY() - 4.0f);
				level->getParticleLast()->setDoGravitate(true);
				level->getParticleLast()->setVelocityX(-2.0f);
				level->getParticleLast()->setVelocityY(-4.0f);
				level->getParticleLast()->setTimeToBeAlive(15);

				level->addParticle(new cParticle);
				level->getParticleLast()->loadConfig("Data\\Particles\\p_dust.cfg");
				level->getParticleLast()->attachParent(this);
				level->getParticleLast()->setX(object->getX());
				level->getParticleLast()->setY(object->getY() - 4.0f);
				level->getParticleLast()->setDoGravitate(true);
				level->getParticleLast()->setVelocityX(2.0f);
				level->getParticleLast()->setVelocityY(-4.0f);
				level->getParticleLast()->setTimeToBeAlive(15);
			}
		} else {
			return;
		}
		//} else if (object->getType() == "water") {
		//	//if (!m_isInWater) {
		//	//	m_isPressingDownThrust = false;
		//	//	m_isDownThrusting = false;
		//	//	//if (getVelocityY() > 0.0f) {
		//	//		//setVelocityY(getMoveVelocity());
		//	//		//p->keysHeld[cInputManager::getDownKey()] = false;
		//	//		//m_velocityY = 0.0f;
		//	//		m_isInWater = true;
		//	//		this->setState(new cPlayerWaterState);
		//	//	//}
		//	//} else {
		//	//	return;
		//	//}
	} else if (object->getType() == "water_not") {
		collisionReactionX(object);
	} else if (object->getType() == "water_out") {
		// If above velocity threshold, set to dive
		if (m_velocityY > m_fallVelocity * 0.5f && !m_isInWater/*getImagePath() == "Data\\Players\\Images\\player_roten.png"*/) {
			setImagePath("Data\\Players\\Images\\player_roten_swim.png");
			setSpriteOffsetY(8);
			if (abs(m_velocityX) > 1.0f) {
				setTileOffsetY(512.0f);
			} else {
				m_tileOffsetY = 576.0f;
			}
		}
		//std::cout << m_isInWater << "\n";
		/*if (m_isInWater && m_velocityY < 0.0f && !keysHeld[cInputManager::getUpKey()]) {
			m_velocityY = 0.0f;
			return;
		}

		else */

		// If we're swimming near the surface, don't jump out
		if (m_velocityY < 0.0f && m_velocityY > -1.5f) {
			m_velocityY = abs(m_velocityY * 0.5f);
			m_y = object->getBottom() - m_subtractUp;
			return;
		}

		if (m_isInWater && !m_isInWaterJump && m_velocityY <= -1.25f/* && keysHeld[cInputManager::getUpKey()]*//* */) {
			std::cout << "´collisionOccurredY() " << object->getType() << "\n";
			m_velocityY = -abs(m_velocityY) * 1.25f - m_jumpForce * 1.25f;
			m_isInWaterJump = true;
			m_isInWater = false;
			//m_velocityY = -abs(m_velocityY) * 1.0f - m_jumpForce * 1.5f;
			m_jumpTime = 0;
			setState(new cPlayerWaterJumpState);

			cLevel* level = m_attachedLevel;
			if (level == nullptr) { return; };

			level->addParticle(new cParticle);
			level->getParticleLast()->loadConfig("Data\\Particles\\p_splash.cfg");
			level->getParticleLast()->setX(object->getX());
			level->getParticleLast()->setY(object->getY());
			level->getParticleLast()->update(0.0f);

			level->addParticle(new cParticle);
			level->getParticleLast()->loadConfig("Data\\Particles\\p_dust.cfg");
			level->getParticleLast()->attachParent(this);
			level->getParticleLast()->setX(object->getX());
			level->getParticleLast()->setY(object->getY() - 4.0f + 16.0f);
			level->getParticleLast()->setDoGravitate(true);
			level->getParticleLast()->setVelocityX(-2.0f);
			level->getParticleLast()->setVelocityY(-4.0f);
			level->getParticleLast()->setTimeToBeAlive(15);

			level->addParticle(new cParticle);
			level->getParticleLast()->loadConfig("Data\\Particles\\p_dust.cfg");
			level->getParticleLast()->attachParent(this);
			level->getParticleLast()->setX(object->getX());
			level->getParticleLast()->setY(object->getY() - 4.0f + 16.0f);
			level->getParticleLast()->setDoGravitate(true);
			level->getParticleLast()->setVelocityX(2.0f);
			level->getParticleLast()->setVelocityY(-4.0f);
			level->getParticleLast()->setTimeToBeAlive(15);
			//}
		}
	} else if (object->getType() == "p_health") {
		collisionReactionX(object);
	} else if (object->getType() == "shop_in") {
		return;
	} else if (object->getType() == "start_unlocked") {
		collisionReactionX(object);
	} else if (object->getType().substr(0, 7) == "target_") {
		//if (object->getAnimTag() == eAnimTag::death) {		// WHY THE NEED TO DO THIS?????
		if (object->getIsDead()) {
			//m_isNearWallRight = false;
			//m_isNearWallLeft = false;
			return;
		}
		m_isInSlope = false;
		m_hasJumped = false;
		m_hasJumpedHigh = false;
		m_isRiding = false;
		m_isOnGround = true;
		m_velocityY = 0.0f;
		m_movedVelocityY = 0.0f;
		m_y = object->getY() - m_height + m_subtractDown + object->getSubtractUp();
	} else if (object->getType().substr(0, 8) == "trigger_") {
		return;
	} else if (object->getType() == "timer_stop") {
		m_isTimerStopped = true;
	} else if (object->getType().substr(0, 4) == "sand") {
		// Moving down
		if (m_velocityY >= 0.0f) {
			m_belowObject = object;
			m_y = object->getY() - m_height + m_subtractDown + object->getSubtractUp();
			m_isRiding = false;
		} else {
			m_belowObject = nullptr;
			m_y = m_previousY;
		}
		m_velocityY = 0.0f;
		m_isOnGround = true;
		m_isInSlope = false;
		m_isSlopeSliding = false;

		m_movedVelocityX = 0.0f;
		m_movedVelocityY = 0.0f;
		m_isDownThrusting = false;
		m_isPressingDownThrust = false;
		m_isInSlope = false;
		m_isNearWallRight = false;
		m_isNearWallLeft = false;
	} else {		
		m_isRiding = false;
		m_movedVelocityX = object->getVelocityX();
		m_movedVelocityY = object->getVelocityY();

		if (m_velocityY >= 0.0f) {
			m_belowObject = object;
			if (cSoundsManager::isPlaying(eSoundTag::jump)) {
				cSoundsManager::stop(eSoundTag::jump);
			}
			if (cSoundsManager::isPlaying(eSoundTag::hover)) {
				cSoundsManager::stop(eSoundTag::hover);
			}
			m_isHovering = false;
			m_isSlopeSliding = false;
			m_lockThrustForward = false;
			m_isPressingDownThrust = false;
			m_hasJumped = false;
			m_hasJumpedHigh = false;
			m_isInSlope = false;

			//m_y = m_previousY;
			m_y = object->getY() - m_height + m_subtractDown + object->getSubtractUp();
			//std::cout << m_joyMovedY << "\n";
			if (m_isInWater) {
				return;
			}
			hitGround(object);
			m_velocityY = 0.0f;
			m_isOnGround = true;
			if (!getIsPressingJump()) {
				m_lockJump = false;
			}
			//setIsPressingJump(false);

			if (object->getType() == "clip_drop" && getIsPressingDown() && getIsPressingJump()) {
				std::cout << "cPlayer::collisionReactionY drop down" << "\n";
				m_y = object->getY() - m_height + m_subtractDown + 12;
				m_delayCollisionLevel = 15.0f;
				m_velocityX = 0.0f;
				//m_isPressingDownThrust = true;
				m_isDownThrusting = false;
				m_isSlopeSliding = false;

				if (!m_isOnGround) {
					m_tileOffsetX = 0.0f;
				}
				m_isOnGround = true;
				m_downThrustDurationValue = m_downThrustDuration + 1;

				setIsPressingJump(false);
				return;
			}			
			/*if (!getIsPressingLeft() && !getIsPressingRight()) {
				setAnim(eAnimTag::idle);
			}*/			
		} else if (m_velocityY < 0.0f) {
			m_belowObject = nullptr;
			if (object->getType() == "clip_drop" || object->getType() == "clip_top") {
				return;
			}
			m_velocityY = -m_velocityY;
			//m_y = m_previousY;
			m_y = object->getBottom() - m_subtractUp + 1;

			if (!m_isInWater) {
				//cSoundsManager::stop(eSoundTag::jump);
				cSoundsManager::stop(eSoundTag::hitHead);
				cSoundsManager::play(eSoundTag::hitHead);
			}
		}
		//m_y = m_previousY;

		/*if (keysHeld[cInputManager::getJumpKey()] == false) {
			m_hasJumped = false;
		}*/
		
		;
		//clearSense();
	}
}