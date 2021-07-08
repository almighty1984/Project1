#include "EntityPigan.h"
#include "EntityPiganWalkState.h"
#include "EntityPiganHurtState.h"
//#include "InputManager.h"
#include "SoundBufferManager.h"
#include "RenderingManager.h"

#include "Particle.h"

#include <string>
#include <iostream>
#include <fstream>
#include <sstream> 

cEntityPigan::cEntityPigan() : m_secondCall(false) {
	m_type = "e_pigan";

	m_width = 32;
	m_height = 32;
	m_spriteOffsetX = 0.0f;
	m_spriteOffsetY = 0.0f;
	//m_velocityX = -0.75f;

	/*m_particles.push_back(new cParticle);

	m_particles.at(m_particles.size()-1)->loadConfig("Data\\Particles\\p_hit.cfg");
	m_particles.at(m_particles.size()-1)->update(0.0f);	*/

	m_state = new cEntityPiganWalkState;
}

cEntityPigan::~cEntityPigan() {
	/*for(unsigned short i=0; i<m_particles.size(); ++i) {
		cRenderingManager::removeParticle(m_particles.at(i));
		m_particles.erase(m_particles.begin()+i, m_particles.begin()+i+1);
	}*/

	delete m_state;
	m_state = nullptr;
	//m_isDead = true;
}

#include "Entity.h"
#include "EntityGrodorr.h"
#include "SoundsManager.h"

void cEntityPigan::collisionReactionX(cBaseObject* object) {
	if (object->getIsSlope()) {
		collisionReactionSlopeX(object);
		return;
	}
	if (m_type.substr(0, 12) == "e_train") { return; };


	if (object->getType() == "e_bounce_U_0" || object->getType() == "e_bounce_U_1" ||		
		object->getType() == "door_0" || object->getType() == "door_exit" ||
		object->getType() == "e_item_health" ||
		object->getType() == "slope_L_1x1" || object->getType() == "slope_R_1x1" ||
		object->getType() == "slope_L_2x1_0" || object->getType() == "slope_L_2x1_1" ||
		object->getType() == "slope_R_2x1_0" || object->getType() == "slope_R_2x1_1" ||
		object->getType() == "cam_lock" || object->getType() == "cam_unlock" ||
		object->getType() == "wall_area_out" ||
		object->getType() == "wall_out_L" || object->getType() == "wall_out_R" ||
		object->getType() == "wall_out_UP" || object->getType() == "wall_out_DOWN" ||
		object->getType() == "wall_in_L" || object->getType() == "wall_in_R" ||
		object->getType() == "swing" ||
		object->getType() == "sign_0" || object->getType() == "sign_1" || object->getType() == "sign_2" ||
		object->getType() == "sign_exit" ||
		object->getType().substr(0, 8) == "trigger_" ||
		object->getType() == "level_start" ||
		object->getType() == "cam_lock" || object->getType() == "cam_unlock" ||
		object->getType() == "cam_lock_ws" || object->getType() == "cam_unlock_ws" ||
		object->getType() == "cam_lock_y" || object->getType() == "cam_unlock_y" ||
		object->getType() == "view_lock" || object->getType() == "view_unlock") {
		return;
	}
	if (object->getType() == "clip_top" || object->getType() == "clip_drop") {
		return;
	} else if (object->getType().substr(0, 4) == "coin") {
	} else if (object->getType() == "door1") {
		//m_nextLevel = object->getType();
	} else if (object->getType() == "e_grass") {
		object->setIsIdle(false);
		int num = 0;
		if (getMiddleX() < object->getMiddleX()) {
			object->setIsFacingLeft(false);
			num = (int)abs(object->getMiddleX() - getMiddleX());
			//std::cout << num << " " << num / 2 << "\n";
		} else {
			object->setIsFacingLeft(true);
			num = (int)abs(object->getMiddleX() - getMiddleX());
			//std::cout << num << " " << num / 2 << "\n";
		}
		float tileX = (num / 4) * 32.0f;
		object->setTileOffsetX(32 * 7 - tileX);
	}/* else if (object->getType() == "e_grodorr") {
		if (getIsOnBack()) {
			object->setVelocityX(-object->getVelocityX());
			return;
		}
		if (object->getMiddleX() > getMiddleX()) {
			m_isFacingLeft = true;
			m_x = object->getLeft() - m_width + m_subtractRight;
		} else {
			m_isFacingLeft = false;
			m_x = object->getRight() - m_subtractLeft;			
		}
	} */else if (object->getType() == "e_train") {

	} else if (object->getType() == "water") {
		if (m_velocityY > 0.0f) {
			//this->setState(new cPlayerWaterState);
		}
	} else if (object->getType() == "water_out") {
		if (m_velocityY > 0.0f) {
			//this->setState(new cPlayerGrassState);
		}
	} else if (object->getType() == "e_flyling") {
	} else if (object->getType() == "e_flugan") {
	} else if (object->getType() == "e_grodorr") {
	} else if (object->getType() == "e_grevert") {
	} else if (object->getType() == "e_pigan") {
	} else if (object->getType() == "p_melee") {		
	} else if (object->getType() == "p_coin") {		
	} else if (object->getType() == "player") {
		//std::cout << "Collided with player\n";
		/*object->setVelocityX(2*m_velocityX);
		object->setVelocityY(-1.0f);*/
	} else if (object->getType() == "start_unlocked") {
		return;
	} else if (object->getType() == "slope_top") {
		//m_y = object->getTop() - m_height + m_subtractDown;
	} else if (object->getType() == "slope_bottom") {
		m_y = object->getBottom() - m_subtractUp;
	} else if (object->getType().substr(0, 7) == "target_") {
		if (object->getAnimTag() == eAnimTag::death) {
			return;
		}
		if (m_velocityX < 0.0f) {
			m_x = object->getRight() - m_subtractLeft;
		}
		if (m_velocityX > 0.0f) {
			m_x = object->getLeft() - m_width + m_subtractRight;
		}
		m_velocityX *= -1.0f;
		m_isFacingLeft = !m_isFacingLeft;
		//m_x = m_previousX;
		//m_levelX = m_previousLevelX;
	} else {
		if (m_velocityX < 0.0f) {
			m_x = object->getX() + object->getWidth() - m_subtractLeft;
			m_isFacingLeft = false;
		}
		if (m_velocityX > 0.0f) {
			m_x = object->getX() - m_width + m_subtractRight;
			m_isFacingLeft = true;
		}
		//m_x = m_previousX;

		m_levelX = m_previousLevelX;
	}
}

void cEntityPigan::collisionReactionY(cBaseObject* object) {
	if (object->getIsSlope()) {
		collisionReactionSlopeY(object);
		return;
	}
	if (m_type.substr(0, 7) == "e_train") { return; };

	if (object->getType().substr(0, 11) == "e_bounce_U_") {
	} else if (object->getType().substr(0, 4) == "coin") {
	} else if (object->getType().substr(0, 5) == "door_0") {
	} else if (object->getType() == "door_exit") {

	} else if (object->getType() == "e_item_health") {
	} else if (object->getType() == "wall_area_out") {
	} else if (object->getType() == "cam_lock" || object->getType() == "cam_unlock") {
	} else if (object->getType() == "swing") {
	} else if (object->getType() == "sign_0" || object->getType() == "sign_1" || object->getType() == "sign_2") {
	} else if (object->getType() == "sign_exit") {
	} else if (object->getType().substr(0, 8) == "trigger_") {
	} else if (object->getType() == "level_start") {
	} else if (object->getType() == "cam_lock" || object->getType() == "cam_unlock") {
	} else if (object->getType().substr(0, 4) == "cam_") {
	} else if (object->getType().substr(0, 5) == "view_") {		
	}
	if (object->getType() == "e_bounce_U_0" || object->getType() == "e_bounce_U_1") {
		m_y = m_previousY;
		m_velocityY = -m_jumpForce * 2;
		object->setTileOffsetX(0.0f);
		object->setIsDead(true);

		if (cSoundsManager::isPlaying(eSoundTag::bounce)) {
			cSoundsManager::stop(eSoundTag::bounce);
		}
		cSoundsManager::play(eSoundTag::bounce);
	} else if (object->getType() == "e_grass") {
		collisionReactionX(object);
	} else if (object->getType() == "clip_top") {
		if (m_velocityY >= 0.0f) {
			m_isOnGround = true;
			m_y = object->getY() - m_height + m_subtractDown + object->getSubtractUp();
			if (m_isOnBack) {
				m_velocityX *= 0.9f;
			}
		} else {
			return;
		}
	} else if (object->getType() == "clip_ledge_L") {
		m_y = object->getY() - m_height + m_subtractDown + object->getSubtractUp();
		m_velocityY = 0.0f;
		m_velocityX = abs(m_velocityX);
	} else if (object->getType() == "clip_ledge_R") {
		m_y = object->getY() - m_height + m_subtractDown + object->getSubtractUp();
		m_velocityY = 0.0f;
		m_velocityX = -abs(m_velocityX);
	} else if (object->getType() == "clip_left" || object->getType() == "clip_right") {
		return;
	} else if (object->getType() == "door1") {
		//m_nextLevel = object->getType();
	} else if (object->getType() == "water") {
		if (m_velocityY > 0.0f) {
			//this->setState(new cPlayerWaterState);
		}
	} else if (object->getType() == "water_out") {
		if (m_velocityY < 0.0f) {
			if (object->getType() == "water_out") {
				m_velocityY = -m_jumpForce;
				//m_jumpTime = 0.0f;
				//this->setState(new cPlayerGrassState);
			}
		}
	} else if (object->getType() == "slope_top") {
		m_y = object->getY() - m_height + m_subtractDown + object->getSubtractUp();
		m_isOnGround = true;
	} else if (object->getType().substr(0, 7) == "target_") {
		if (object->getAnimTag() == eAnimTag::death) {
			return;
		}
		if (m_velocityY < 0.0f) {
			m_y = object->getBottom() - m_subtractUp;
		} else if (m_velocityY > 0.0f) {
			m_y = object->getTop() - m_height + m_subtractDown;
		}
	} else if (object->getType() == "e_pigan") {
		return;
	} else if (object->getType() == "e_flyling") {
		return;
	} else if (object->getType() == "e_flugan") {
		collisionReactionX(object);
	} else if (object->getType() == "e_grevert") {
	} else if (object->getType() == "e_grodorr") {
		collisionReactionX(object);
	} else if (object->getType() == "e_train") {
		m_velocityY = 0.0f;
		m_movedVelocityY = object->getVelocityY();
		m_movedVelocityX = object->getVelocityX();
		m_y = object->getY() - m_height + object->getSubtractUp() + 0.0f;
		m_isOnGround = true;
		m_isInSlope = false;
	} else if (object->getType() == "p_melee") {
		return;
	} else if (object->getType() == "p_coin") {
		return;
	} else if (object->getType() == "player") {
		return;
	} else {
		if (m_velocityY > 0.0f) {
			m_y = object->getY() - m_height + m_subtractDown;			
		} else {
			m_y = m_previousY;
		}
		//m_y = m_previousY;
		/*if (m_velocityY >= 0.0f) {
			m_y = object->getY()-m_height+m_subtractDown;
		}*/
		m_velocityY = 0.0f;
		m_isOnGround = true;

		

		//m_y = m_previousY;
		//m_levelY = m_previousLevelY;
		//m_y = object->getY()-m_height;
	}
}

void cEntityPigan::hurt(cBaseObject* hurter, float amount) {
	if (!m_isHurting) {
		m_isHurting = true;
		setState(new cEntityPiganHurtState);
	}
}

void cEntityPigan::update(cApp* app, float time) {
	if (m_attachedLevel == nullptr) {
		return;
	}
	if (m_isLocked) {
		m_velocityX = 0.0f;
		m_velocityY = 0.0f;
		m_tileOffsetX = 0.0f;
		m_tileOffsetY = 0.0f;
	} else {
		if (m_state != nullptr) {
			m_state->update(app, this, time);
		}
	}



	// Animate
	if (m_animTime >= 10.0f) {
		m_tileOffsetX += m_width;

		if (m_tileOffsetX >= m_width * m_numAnimFrames) {
			if (m_currentLoops < m_numAnimLoops && m_numAnimLoops != 0) {
				//m_tileOffsetX = 0;
				m_tileOffsetX = (float)(m_width * m_numAnimFrames);
				setCurrentLoops(getCurrentLoops() + 1);
			}
			if (getNumAnimLoops() == 0) {
				setTileOffsetX(0.0f);
				setCurrentLoops(0);
			}
		}
		setAnimTime(0.0f);
	} else {
		setAnimTime(getAnimTime() + getAnimSpeed());
	}
	if (getTileOffsetX() >= (getWidth() * getNumAnimFrames()) - getWidth()) {
		setTileOffsetX((float)(getWidth() * getNumAnimFrames() - getWidth()));
	}

	// Regenerate health
	if (m_numHealth > 0.0f) {
		if (m_numHealth < m_startHealth) {
			m_numHealth += 0.05f/* * time*/;
		} else if (m_numHealth > m_startHealth) {
			m_numHealth = m_startHealth;
		}
	}
	// Hide health bar at full health
	if (m_numHealth <= 0.0f || m_numHealth == m_startHealth) {
		m_meterHealthBackground.setIsHidden(true);
		m_meterHealth.setIsHidden(true);
	} else {
		m_meterHealthBackground.setIsHidden(false);
		m_meterHealth.setIsHidden(false);
	}

	m_meterHealthBackground.setX(m_x);
	m_meterHealthBackground.setY(m_y + 16);
	m_meterHealthBackground.setWidth((int)m_startHealth);
	m_meterHealthBackground.update(time);

	m_meterHealth.setX(m_x);
	m_meterHealth.setY(m_y + 16);
	m_meterHealth.setWidth((int)m_numHealth);
	m_meterHealth.update(time);

	//m_velocityY = 0.0f;

	m_previousX = m_x;
	m_previousY = m_y;
	m_previousLevelX = m_levelX;
	m_previousLevelY = m_levelY;

	if (m_isCarried && m_carrier != nullptr) {
		setIsSolid(false);
		m_timerState = 0.0f;
		if (m_leftObject != nullptr) {
			std::cout << m_leftObject->getType() << "\n";
		}
		m_x = m_carrier->getMiddleX() - m_width / 2;
		m_y = m_carrier->getTop() - m_height - 8;
		m_startX = m_carrier->getLevelX() + m_carrier->getWidth() * 0.5f - m_width * 0.5f;
		m_startY = m_carrier->getLevelY() + m_carrier->getHeight() - m_height - 8;
		m_velocityX = m_carrier->getVelocityX();
		m_velocityY = m_carrier->getVelocityY();
	} else {
		setIsSolid(true);
		m_x += (m_velocityX + m_movedVelocityX);
		m_y += (m_velocityY + m_movedVelocityY);
		/*m_startX = m_oldStartX;
		m_startY = m_oldStartY;
		if (m_attachedLevel != nullptr) {
			m_x = -m_attachedLevel->getX() + m_startX;
			m_y = -m_attachedLevel->getY() + m_startY;
		}*/
	}

	if (m_attachedLevel != nullptr) {
		m_levelX = m_startX + (m_x - m_startX) + m_attachedLevel->getX();
		m_levelY = m_startY + (m_y - m_startY) + m_attachedLevel->getY();
	}

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
	if (getVelocityY() >= getFallVelocity()) {
		setVelocityY(getFallVelocity());
	} else {
		setVelocityY(getVelocityY() + getFallAcc());
	}

	

}