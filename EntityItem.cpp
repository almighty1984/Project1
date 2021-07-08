#include "EntityItem.h"
//#include "InputManager.h"
#include "SoundBufferManager.h"
#include "RenderingManager.h"
#include "SoundsManager.h"

//#include "EntityItemIdleState.h"
#include "Particle.h"

#include <string>
#include <iostream>
#include <fstream>
#include <sstream> 

cEntityItem::cEntityItem() {
}

cEntityItem::~cEntityItem() {
	/*for (auto it = m_particles.begin(); it != m_particles.end(); ++it) {
		cRenderingManager::removeParticle(*it);
		delete *it;
	}
	m_particles.clear();*/
}

void cEntityItem::collisionReactionX(cBaseObject *object) {
	//if (object->getType() == "e_bounce_U_0" || object->getType() == "e_bounce_U_1" ||
	//	object->getType() == "cam_lock" || object->getType() == "cam_unlock" ||
	//	object->getType() == "cam_lock_ws" || object->getType() == "cam_unlock_ws" ||
	//	object->getType() == "cam_lock_y" || object->getType() == "cam_unlock_y" ||
	//	object->getType() == "chest_0" ||
	//	object->getType() == "door_exit" ||	object->getType() == "door_0" ||
	//	object->getType() == "e_ball" ||
	//	object->getType() == "e_item_coin" ||
	//	object->getType() == "e_grodorr" ||
	//	object->getType() == "e_flugan" ||
	//	object->getType() == "e_flyling" ||
	//	object->getType() == "slope_L_1x1" || object->getType() == "slope_R_1x1" ||
	//	object->getType() == "slope_L_2x1_0" || object->getType() == "slope_L_2x1_1" ||
	//	object->getType() == "slope_R_2x1_0" || object->getType() == "slope_R_2x1_1" ||	
	//	object->getType() == "view_lock" || object->getType() == "view_unlock" ||
	//	object->getType() == "wall_out_L" || object->getType() == "wall_out_R" ||
	//	object->getType() == "wall_out_UP" || object->getType() == "wall_out_DOWN" ||
	//	object->getType() == "wall_in_L" ||	object->getType() == "wall_in_R" ||
	//	object->getType() == "wall_in_L_UP" || object->getType() == "wall_in_DOWN" ||
	//	object->getType() == "swing" ||
	//	object->getType() == "sign_0" || object->getType() == "sign_1" || object->getType() == "sign_2" ||
	//	object->getType() == "sign_exit" ||
	//	object->getType() == "level_start") {
	//	return;
	//}
	//else {
	//	//m_velocityX = 0.0f;
	//	//m_x = m_previousX;

	//	//m_levelX = m_previousLevelX;
	//}
}
void cEntityItem::collisionReactionY(cBaseObject *object) {
	//if (object->getType() == "cam_lock" || object->getType() == "cam_unlock" ||
	//	object->getType() == "chest_0" ||
	//	object->getType() == "door_exit" || object->getType() == "door_0" ||
	//	object->getType() == "e_ball" ||
	//	object->getType() == "e_item_coin" ||
	//	object->getType() == "e_grodorr" ||
	//	object->getType() == "e_flugan" ||
	//	object->getType() == "e_flyling" ||
	//	object->getType() == "view_lock" || object->getType() == "view_unlock" ||
	//	object->getType() == "wall_out_L" || object->getType() == "wall_out_R" ||
	//	object->getType() == "wall_out_UP" || object->getType() == "wall_out_DOWN" ||
	//	object->getType() == "wall_in_L" || object->getType() == "wall_in_R" ||
	//	object->getType() == "wall_in_L_UP" || object->getType() == "wall_in_DOWN" ||
	//	object->getType() == "swing" ||
	//	object->getType() == "sign_0" || object->getType() == "sign_1" || object->getType() == "sign_2" || object->getType() == "sign_exit" ||
	//	object->getType() == "level_start" ||
	//	object->getType() == "cam_lock" || object->getType() == "cam_unlock" ||
	//	object->getType() == "cam_lock_ws" || object->getType() == "cam_unlock_ws" ||
	//	object->getType() == "cam_lock_y" || object->getType() == "cam_unlock_y"
	//	) {
	//	return;
	//}
	//else {
	//	//if (m_velocityY > m_fallAcc*5) {
	//	//	m_velocityY *= -0.9f;
	//	//	/*if (cSoundsManager::m_soundHead.getStatus() != sf::SoundSource::Playing) {
	//	//		cSoundsManager::play(eSoundTag::hitHead);
	//	//	}*/
	//	//}
	//	//else {
	//		m_velocityY = 0.0f;
	//		m_y = m_previousY;
	//		//m_levelY = m_previousLevelY;
	//		m_y = object->getY() - m_height;
	//	//}	
	//	
	//}
}


void cEntityItem::update(cApp *app, float time) {
	if (m_startDelay > 0.0f) {
		m_startDelay -= time;
		m_isHidden = true;
		return;
	} else {
		m_isHidden = false;
	}

	if (m_timeToBeIdle != 0.0f && !m_isDead) {
		if (m_timerState > m_timeToBeIdle) {
			m_isDead = true;
		}
		m_timerState += time;
	}

	m_previousX = m_x;
	m_previousY = m_y;
	m_previousLevelX = m_levelX;
	m_previousLevelY = m_levelY;

	m_x += m_velocityX;
	m_y += m_velocityY;
	
	if (m_attachedLevel != nullptr) {
		m_levelX = m_startX + (m_x - m_startX) + m_attachedLevel->getX();
		m_levelY = m_startY + (m_y - m_startY) + m_attachedLevel->getY();
	}

	if (m_velocityY == 0.0f) {
		m_velocityX = 0.0f;
	}
	
	if (m_velocityY >= m_fallVelocity*time) {
		m_velocityY = m_fallVelocity*time;
	}
	else {
		m_velocityY += m_fallAcc*time;
	}

	/*for (unsigned short i = 0; i<m_particles.size(); ++i) {
		m_particles.at(i)->update(time);

		if (m_particles.at(i)->getIsDead() == true) {
			cRenderingManager::removeParticle(m_particles.at(i));
			m_particles.erase(m_particles.begin() + i, m_particles.begin() + i + 1);
		}
	}*/
	// Death animation
	if (m_isDead) {
		setAnim(eAnimTag::death);
	} else {
		setAnim(eAnimTag::idle);
	}
	// Update animation		
	if (m_animTime >= 10.0f) {
		m_tileOffsetX += m_width;
		if (m_tileOffsetX >= (m_width*m_numAnimFrames - m_width)) {
			if (m_currentLoops < m_numAnimLoops && m_numAnimLoops != 0) {
				//m_tileOffsetX = 0;
				m_tileOffsetX = (float)(m_width*m_numAnimFrames - m_width);
				m_currentLoops += 1;
			}
			else if (m_numAnimLoops == 0) {
				m_tileOffsetX = 0.0f;
				m_currentLoops = 0;
			}
		}
		m_animTime = 0.0f;
	}
	else {
		m_animTime += m_animSpeed*time;
	}
	
	if (m_tileOffsetX >= (m_width*m_numAnimFrames)-m_width ) {
		m_tileOffsetX = (float)(m_width*m_numAnimFrames-m_width);
	}
}