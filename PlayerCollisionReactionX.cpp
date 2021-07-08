#include "Player.h"

#include "CameraManager.h"
#include "InputManager.h"
#include "SoundBufferManager.h"
#include "SoundsManager.h"
#include "SavesManager.h"
#include "RenderingManager.h"

#include "PlayerGrassState.h"
#include "PlayerWaterState.h"
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

void cPlayer::collisionReactionX(cBaseObject* object) {
	if (object->getIsSlope()) {
		collisionReactionSlopeX(object);
		return;
	}
	if (object->getType() == "clip_bot" ||
		object->getType() == "clip_top" || object->getType() == "clip_bottom") {
		return;
	} else if (object->getType() == "cam_lock_y") {
		cCameraManager::setIsLockedY(true);
		//m_isCameraLockedY = true;
	} else if (object->getType() == "cam_unlock_y") {
		cCameraManager::setIsLockedY(false);
		//m_isCameraLockedY = false;
	} else if (object->getType() == "cam_lock") {
		m_doStartUnlocked = false;
		if (!cRenderingManager::getIsWidescreen()) {
			cCameraManager::setIsLockedX(true);
			//m_isCameraLockedX = true;
		}
	} else if (object->getType() == "cam_unlock") {
		m_doStartUnlocked = false;
		if (!cRenderingManager::getIsWidescreen()) {
			cCameraManager::setIsLockedX(false);
			//m_isCameraLockedX = false;
		}
	} else if (object->getType() == "cam_lock_ws") {
		m_doStartUnlocked = false;
		if (cRenderingManager::getIsWidescreen()) {
			cCameraManager::setIsLockedX(true);
			//m_isCameraLockedX = true;
		}
	} else if (object->getType() == "cam_unlock_ws") {
		m_doStartUnlocked = false;
		if (cRenderingManager::getIsWidescreen()) {
			//m_isCameraLockedX = false;
			cCameraManager::setIsLockedX(false);
		} else {
			cRenderingManager::m_window.setIsViewLocked(true);
		}
	} else if (object->getType() == "cam_scroll_up") {
		cCameraManager::scrollY(m_attachedLevel, this, -1.0f);
	} else if (object->getType() == "cam_scroll_down") {
		cCameraManager::scrollY(m_attachedLevel, this, 1.0f);
	} else if (object->getType() == "cam_reset_y") {
		cCameraManager::resetY(m_attachedLevel, this, 1.0f);
	} else if (object->getType().substr(0, 4) == "coin") {
		if (object->getIsDead() == false) {
			object->setIsDead(true);
			object->setAnim(eAnimTag::death);
			//object->setIsHidden(true);
			//object->setCurrentLoops(0);
			object->setTileOffsetX(0.0f);
			//object->setTileOffsetY(16.0f);
			cSoundsManager::stop(eSoundTag::coin);
			cSoundsManager::play(eSoundTag::coin);
			int tmpInt = 0;
			if (object->getType().size() == 6) { // below 10
				tmpInt = 0;
				std::istringstream(object->getType().substr(5, 1)) >> tmpInt;
			} else if (object->getType().size() == 7) { // 10 or above
				tmpInt = 0;
				std::istringstream(object->getType().substr(5, 2)) >> tmpInt;
			}
			std::cout << "cPlayer::collisionReactionX " << object->getType() << " " << tmpInt << "\n";
			cSavesManager::addCoin(m_currentLevel, tmpInt);
		}
	} else if (object->getType() == "chest_0") {
		return;
	} else if (object->getType() == "clip_bot") {
		return;
	} else if (object->getType() == "clip_drop") {
		return;
	} else if (object->getType() == "clip_top") {
		/*m_y = object->getY() - m_height + object->getSubtractUp();
		m_velocityY = 0.0f;*/
		return;
	} else if (object->getType() == "death") {
		m_velocityX *= -1.0f;
		/*if (m_isDead == false) {
			m_isDead = true;
			m_tileOffsetX = 0.0f;
			//playSoundDeath();
			cSoundsManager::play(eSoundTag::death);
		}*/
	} else if (object->getType().substr(0, 4) == "door" && object->getType().size() == 6) {
		unsigned char num = atoi(object->getType().substr(5, 1).c_str());
		m_isInDoor[num] = true;
		m_isNearDoor = true;
	} else if (object->getType() == "door_exit") {
		for (unsigned char i = 0; i < 4; ++i) {
			m_isInDoor[i] = false;
		}
		m_isNearDoor = false;
	} else if (object->getType() == "swing" || object->getType().substr(0, 10) == "shop_item_") {
		return;
	} else if (object->getType().substr(0, 6) == "target") {
		//if (object->getAnimTag() == eAnimTag::death) {		// WHY THE NEED TO DO THIS HERE?????
		if (object->getIsDead()) {
			//m_isNearWallRight = false;
			//m_isNearWallLeft = false;
			return;
		}
		//std::cout << "cPlayer::collisionReactionX " << object->getType() << " " << object->getAnim().y << "\n";
		m_isRiding = false;
		m_belowObject = nullptr;
		m_isInSlope = false;
		//m_x = m_previousX;
		if (m_velocityX + m_movedVelocityX < 0.0f) {
			m_x = object->getRight() - m_subtractLeft + 0;
		} else {
			m_x = object->getLeft() - m_width + m_subtractRight;
		}
		m_velocityX = 0.0f;
		m_movedVelocityX = 0.0f;
		if (m_isNearWallLeft || m_isNearWallRight && !m_isOnGround) {
			slideWall(object);
		}
	} else if (object->getType() == "timer_stop") {
		m_isTimerStopped = true;
	} else if (object->getType().substr(0, 8) == "trigger_") {
		//std::cout << "cPlayer::collisionReactionX "<< object->getType().substr(0, 8) << "\n";
		return;
	} else if (object->getType().substr(0, 13) == "level_bottom_" ||
		object->getType().substr(0, 10) == "level_top_" ||
		object->getType().substr(0, 11) == "level_left_" ||
		object->getType().substr(0, 12) == "level_right_") {
		//if(m_nextLevel != object->getType())
		//std::cout << m_isInWater << "\n";
		m_nextLevel = object->getType();
	} else if (object->getType() == "level_start") {
		if (!object->getIsDead() && !m_isDead) {
			if (m_hasCollidedSave == false) {
				m_hasCollidedSave = true;
			}
			object->setIsDead(true);

			m_timerSave = (float)object->getTimeToBeDead();
		}
	} else if (object->getType() == "flag") {
		return;
	} else if (object->getType() == "item_sprint" || object->getType() == "item_hover" || object->getType() == "item_whirl") {
		object->setIsDead(true);
		if (!m_hasCollidedItem) {
			m_hasCollidedItem = true;
			m_collidedItemType = object->getType();
		}
		if (object->getType() == "item_sprint") {
			if (!m_hasSprint) {
				m_hasSprint = true;
				object->setIsHidden(true);
			}
		} else if (object->getType() == "item_hover") {
			if (!m_hasHover) {
				m_hasHover = true;
				object->setIsHidden(true);
			}
		} else if (object->getType() == "item_whirl") {
			if (!m_hasWhirl) {
				m_hasWhirl = true;
				object->setIsHidden(true);
			}
		}
		/*} else if (object->getType().at(0) == 'p' && object->getType().at(1) == 'o' && object->getType().at(2) == 't') {
			m_velocityX = 0.0f;
			m_x = m_previousX;*/
	} else if (object->getType() == "p_health") {		
		if (m_vitalityMeterValue >= 64) {
			std::cout << "health full\n";
			return;
		} else {
			std::cout << "hello player\n";
			/*setVitalityMeterValue(getVitalityMeterValue() + 32);
			if (getVitalityMeterValue() > 64) {
				setVitalityMeterValue(64);
			}*/
			object->collisionReactionX(this);
		}
		//std::cout << "player collided with p_health" << "\n";
		
	} else if (object->getType() == "p_grodorr") {
		std::cout << "player collided with p_grodorr" << "\n";
		object->collisionReactionX(this);
	} else if (object->getType() == "shop_in") {
		return;
	} else if (object->getType().substr(0, 4) == "sign") {
		return;
	} else if (object->getType() == "start_unlocked") {
		m_doStartUnlocked = true;
	} else if (object->getType() == "slope_top") {
		m_y = object->getTop() - m_height + m_subtractDown;
		m_velocityY = 0.0f;
	} else if (object->getType() == "slope_bottom") {
		m_y = object->getBottom() - m_subtractUp;
	} else if (object->getType() == "view_lock") {
		cRenderingManager::setIsViewLocked(true);
		m_inLevelChangeArea = true;
	} else if (object->getType() == "view_unlock") {
		cRenderingManager::setIsViewLocked(false);
		m_inLevelChangeArea = false;
	} else if (object->getType() == "music_0") {
		m_doPlayMusic0 = true;
		m_doPlayMusic1 = false;
		/*cMusicManager::setMusicBackground("Data\\Sounds\\music_130122-02.ogg");
		cMusicManager::playMusicBackground();*/
	} else if (object->getType() == "music_1") {
		m_doPlayMusic1 = true;
		m_doPlayMusic0 = false;
		/*cMusicManager::setMusicBackground("Data\\Sounds\\music_130121-01.ogg");
		cMusicManager::playMusicBackground();*/
	} else if (object->getType() == "water_in") {
		collisionReactionY(object);
	} else if (object->getType() == "water") {
		collisionReactionY(object);
	} else if (object->getType() == "water_not") {
		if (m_isInWater) {
			m_isInWater = false;
			setState(new cPlayerGrassState);
		}
	} else if (object->getType() == "water_out") {
		collisionReactionY(object);
		//if (m_isInWater) {
		//	m_isInWater = false;
		//	//std::cout << m_isInWater << "\n";
		//	if (m_velocityY < 0.0f) {
		//		this->setState(new cPlayerGrassState);
		//	}
		//}
	} else {
		//std::cout << "x" << "\n";
		m_isRiding = false;
		m_belowObject = nullptr;

		//m_x = m_previousX;
		if (m_velocityX + m_movedVelocityX < 0.0f) {
			m_x = object->getRight() - m_subtractLeft + 0;
		} else {
			m_x = object->getLeft() - m_width + m_subtractRight;
		}
		m_velocityX = 0.0f;
		m_movedVelocityX = 0.0f;

		if (m_isNearWallLeft || m_isNearWallRight && !m_isOnGround && !m_isInSlope) {
			slideWall(object);
			return;
		}

		if (m_isOnGround || m_isInSlope) {
			setAnim(eAnimTag::idle);
		}

		if (getIsPressingLeft()) {
			setIsPressingLeft(false);
		}
		if (getIsPressingRight()) {
			setIsPressingRight(false);
		}
		//m_isInSlope = false;
	}
}