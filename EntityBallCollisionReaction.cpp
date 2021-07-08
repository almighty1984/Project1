#include "EntityBall.h"
#include "SoundsManager.h"

void cEntityBall::collisionReactionX(cBaseObject *object) {
	if (object->getIsSlope()) {
		m_isInSlope = true;
		m_isSlopeSliding = true;
		collisionReactionSlopeX(object);
		return;
	}
	m_isInSlope = false;
	m_isSlopeSliding = false;
	//std::cout << object->getType() << "\n";
	if (object->getType().substr(0, 4) == "coin" ||

		object->getType() == "slope_L_1x1" || object->getType() == "slope_R_1x1" ||
		object->getType() == "slope_L_2x1_0" || object->getType() == "slope_L_2x1_1" ||
		object->getType() == "slope_R_2x1_0" || object->getType() == "slope_R_2x1_1" ||
		object->getType() == "cam_lock" || object->getType() == "cam_unlock" ||
		object->getType() == "door_exit" || object->getType() == "door_0" ||
		object->getType() == "wall_area_out" ||
		object->getType() == "wall_out_L" || object->getType() == "wall_out_R" ||
		object->getType() == "wall_out_UP" || object->getType() == "wall_out_DOWN" ||
		object->getType() == "wall_in_L" || object->getType() == "wall_in_R" ||
		object->getType() == "wall_in_L_UP" || object->getType() == "wall_in_L_DOWN" ||
		object->getType() == "wall_in_R_UP" || object->getType() == "wall_in_R_DOWN" ||
		object->getType() == "e_item_coin" || object->getType() == "e_item_health" ||
		object->getType() == "swing" ||
		object->getType() == "sign_0" || object->getType() == "sign_1" || object->getType() == "sign_2" ||
		object->getType() == "sign_exit" ||
		object->getType() == "item_sprint" ||
		object->getType() == "level_start" ||
		object->getType() == "level_top_0" || object->getType() == "level_top_1" || object->getType() == "level_top_2" || object->getType() == "level_top_3" ||
		object->getType() == "cam_lock" || object->getType() == "cam_unlock" ||
		object->getType() == "cam_lock_ws" || object->getType() == "cam_unlock_ws" ||
		object->getType() == "cam_lock_y" || object->getType() == "cam_unlock_y" ||
		object->getType() == "view_lock" || object->getType() == "view_unlock") {
		return;
	} else if (object->getType() == "e_bounce_U_0" || object->getType() == "e_bounce_U_1") {
		collisionReactionY(object);	
	} else if (object->getType() == "chest_0") {
		return;
	} else if (object->getType() == "e_ball") {
		object->setVelocityX(m_velocityX);

		if (getMiddleX() < object->getMiddleX()) {
			object->setX(getRight());
		} else {
			object->setX(getLeft() - object->getWidth() + object->getSubtractRight());
		}
	} else if (object->getType() == "e_flugan" || object->getType() == "e_flyling" || object->getType() == "e_grodorr") {
		/*object->setIsDead(true);
		object->setVelocityY(0.0f);*/
		object->setNumHealth(0);		
		object->setTileOffsetX(0.0f);
		cSoundsManager::stop(eSoundTag::hit);
		cSoundsManager::play(eSoundTag::hit);

		unsigned char randNum;
		randNum = (rand() % 3);
		if (randNum == 0) {
			cSoundsManager::play(eSoundTag::fluganHurt0);
		}
		else if (randNum == 1) {
			cSoundsManager::play(eSoundTag::fluganHurt1);
		}
		else if (randNum == 2) {
			cSoundsManager::play(eSoundTag::fluganHurt2);
		}
		object->die(this);
	}
	//else if (object->getType() == "slope_L_1x1" || object->getType() == "slope_seam_L") {
	//	m_isInSlope = true;
	//	//m_isOnGround = true;
	//	if (m_velocityX > m_moveVelocity * 0.3f) {
	//		m_velocityX = m_moveVelocity * 0.3f;
	//		//m_hasJumped = true;
	//	}
	//	setVelocityFromSlope(16.0f, 16.0f);
	//}
	//else if (object->getType() == "slope_R_1x1" || object->getType() == "slope_seam_R") {
	//	m_isInSlope = true;
	//	//m_isOnGround = true;
	//	if (m_velocityX < -m_moveVelocity * 0.3f) {
	//		m_velocityX = -m_moveVelocity * 0.3f;
	//		//m_hasJumped = true;
	//	}
	//	setVelocityFromSlope(-16.0f, 16.0f);
	//}
	//else if (object->getType() == "slope_L_2x1_0" || object->getType() == "slope_L_2x1_1") {
	//	m_isInSlope = true;
	//	if (m_velocityX > m_moveVelocity * 0.6f) {
	//		m_velocityX = m_moveVelocity * 0.6f;
	//	}
	//	setVelocityFromSlope(32.0f, 16.0f);
	//}
	//else if (object->getType() == "slope_R_2x1_0" || object->getType() == "slope_R_2x1_1") {
	//	m_isInSlope = true;
	//	if (m_velocityX < -m_moveVelocity * 0.6f) {
	//		m_velocityX = -m_moveVelocity * 0.6f;
	//	}
	//	setVelocityFromSlope(-32.0f, 16.0f);
	//}
	else if (object->getType() == "door1") {
		//m_nextLevel = object->getType();
	}
	else if (object->getType() == "water") {
		if (m_velocityY > 0.0f) {
			//this->setState(new cPlayerWaterState);
		}
	}
	else if (object->getType() == "water_out") {
		if (m_velocityY > 0.0f) {
			//this->setState(new cPlayerGrassState);
		}
	}
	else if (object->getType() == "e_pigan") {
		return;
	}
	else if (object->getType() == "e_flyling") {
		return;
	}
	else if (object->getType() == "p_melee") {
		return;
	}
	else if (object->getType() == "player") {
		//std::cout << "Collided with player\n";
		/*object->setVelocityX(2*m_velocityX);
		object->setVelocityY(-1.0f);*/
	}
	else if (object->getType() == "clip_top") {
		/*m_y = object->getY() - m_height + object->getSubtractUp();
		m_velocityY = 0.0f;*/
	}
	else if (object->getType() == "slope_top") {
		/*m_y = object->getY() - m_height;
		m_velocityY = 0.0f;*/
	} else {
		if (m_velocityX < 0.0f) {
			m_x = object->getX() + object->getWidth() - object->getSubtractRight() - m_subtractLeft;
		}
		if (m_velocityX > 0.0f) {
			m_x = object->getX() + object->getSubtractLeft() - m_width + m_subtractRight;
		}

		if (abs(m_velocityX) > 1.0f) {
			m_velocityX *= -0.5f;
		} else {
			m_velocityX = 0.0f;
		}
		//m_x = m_previousX;

		m_levelX = m_previousLevelX;
	}
}

void cEntityBall::collisionReactionY(cBaseObject *object) {
	if (object->getIsSlope()) {
		m_isSlopeSliding = true;
		m_isInSlope = true;
		collisionReactionSlopeY(object);
		return;
	}
	m_isSlopeSliding = false;
	m_isInSlope = false;
	if (object->getType().at(0) == 'c' && object->getType().at(1) == 'o' && object->getType().at(2) == 'i' && object->getType().at(3) == 'n' ||
		object->getType() == "door_exit" || object->getType() == "door_0" ||
		object->getType() == "wall_area_out" ||
		object->getType() == "wall_out_L" || object->getType() == "wall_out_R" ||
		object->getType() == "wall_out_UP" || object->getType() == "wall_out_DOWN" ||
		object->getType() == "wall_in_L" || object->getType() == "wall_in_R" ||
		object->getType() == "wall_in_L_UP" || object->getType() == "wall_in_L_DOWN" ||
		object->getType() == "wall_in_R_UP" || object->getType() == "wall_in_R_DOWN" ||
		object->getType() == "cam_lock" || object->getType() == "cam_unlock" ||
		object->getType() == "e_item_coin" || object->getType() == "e_item_health" ||
		object->getType() == "swing" ||
		object->getType() == "sign_0" || object->getType() == "sign_1" || object->getType() == "sign_2" ||
		object->getType() == "sign_exit" ||
		object->getType() == "item_sprint" ||
		object->getType() == "level_start" ||
		object->getType() == "level_top_0" || object->getType() == "level_top_1" || object->getType() == "level_top_2" || object->getType() == "level_top_3" ||
		object->getType() == "cam_lock" || object->getType() == "cam_unlock" ||
		object->getType() == "cam_lock_ws" || object->getType() == "cam_unlock_ws" ||
		object->getType() == "cam_lock_y" || object->getType() == "cam_unlock_y" ||
		object->getType() == "view_lock" || object->getType() == "view_unlock") {
		return;
	} else if (object->getType() == "e_ball") {
		if (getMiddleY() < object->getMiddleY()) {
			m_y = object->getTop() + m_subtractDown;
		} else {
			object->setY(getTop() + object->getSubtractDown());
		}
		object->setVelocityX(m_velocityX);
		//object->setVelocityX(m_velocityX);
	} else if (object->getType() == "e_bounce_U_0" || object->getType() == "e_bounce_U_1") {
		m_velocityY = -abs(m_velocityY) * 0.1f - m_jumpForce * 2.0f;
		object->setTileOffsetX(0.0f);
		object->setIsDead(true);
		cSoundsManager::stop(eSoundTag::bounce);
		cSoundsManager::play(eSoundTag::bounce);
		cSoundsManager::stop(eSoundTag::jump);
		cSoundsManager::play(eSoundTag::jump);
	}
	else if (object->getType() == "chest_0") {

	}
	else if (object->getType() == "door1") {
		
	}
	else if (object->getType() == "e_grodorr") {
		//collisionReactionX(object);
	}
	else if (object->getType() == "water") {
		
	}
	else if (object->getType() == "water_out") {
		
	}	
	else if (object->getType() == "e_pigan") {
		return;
	}
	else if (object->getType() == "e_flyling") {
		return;
	}
	else if (object->getType() == "p_melee") {
		return;
	}
	else if (object->getType() == "player") {
		return;
	}
	else {
		//if(m_velocityY >= 0.0f) {
		//	//m_hasJumped = false;
		//	m_y = object->getY()-m_height+m_subtractDown;
		//}
		//else {
		//	m_y = m_previousY;
		//}			

		if (m_velocityY > 0.0f) {
			m_y = object->getY() - m_height + m_subtractDown;
		}
		m_velocityY = 0.0f;
		m_isOnGround = true;

		//m_y = m_previousY;
		//m_levelY = m_previousLevelY;
		//m_y = object->getY()-m_height;
	}
}
