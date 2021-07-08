#include "ParticleHealth.h"
#include "RenderingManager.h"
#include "SoundsManager.h"
#include "PlayerSwingState.h"
#include "EntityPigan.h"
#include "EntityPiganHurtState.h"

bool cParticleHealth::collisionCheckX(cBaseObject* object) {
	if (object == this || object == nullptr || object == m_parent) {
		return false;
	}
	if (!getIsSolidX() || !object->getIsSolidX()) {
		return false;
	}
	if (object->getIsSlope()) {
		return collisionCheckSlopeX(object);
	}
	float left = getLeft();
	float right = getRight();
	float bottom = getBottom();
	float top = getTop();
	if (m_velocityX + m_movedVelocityX >= 0.0f) {
		if (right > object->getLeft() && getMiddleX() < object->getRight()) {
			if (bottom > object->getTop() && top < object->getBottom()) {
				return true;
			}
		}
	} else if (m_velocityX + m_movedVelocityX <= 0.0f) {
		if (left < object->getRight() && getMiddleX() > object->getLeft()) {
			if (bottom > object->getTop() && top < object->getBottom()) {
				return true;
			}
		}
	}
	return false;
}

bool cParticleHealth::collisionCheckY(cBaseObject* object) {
	if (object == this || object == nullptr || object == m_parent) {
		return false;
	}
	if (!getIsSolidY() || !object->getIsSolidY()) {
		return false;
	}
	if (object->getIsSlope()) {
		return collisionCheckSlopeY(object);
	}
	float left = getLeft();
	float right = getRight();
	float bottom = getBottom() + 2;
	float top = getTop();
	if (m_velocityY + m_movedVelocityY <= 0.0f) {
		if (top < object->getBottom() && getMiddleY() > object->getTop()) {
			if (left < object->getRight() && right > object->getLeft()) {
				return true;
			}
		}
	} else if (m_velocityY + m_movedVelocityY >= 0.0f) {
		if (bottom > object->getTop() && getMiddleY() < object->getBottom()) {
			if (left < object->getRight() && right > object->getLeft()) {
				return true;
			}
		}
	}
	return false;
}

void cParticleHealth::collisionReactionX(cBaseObject *object) {
	std::cout << object->getType() << "\n";
	if (object->getType() == "level_start" ||
		object->getType() == "level_top_0" ||
		object->getType() == "level_top_1" ||
		object->getType() == "level_top_2" ||
		object->getType() == "level_top_3" ||
		object->getType() == "level_bottom_0" ||
		object->getType() == "level_bottom_1" ||
		object->getType() == "level_bottom_2" ||
		object->getType() == "level_bottom_3" ||
		object->getType() == "level_left_0" ||
		object->getType() == "level_left_1" ||
		object->getType() == "level_left_2" ||
		object->getType() == "level_left_3" ||
		object->getType() == "level_right_0" ||
		object->getType() == "level_right_1" ||
		object->getType() == "level_right_2" ||
		object->getType() == "level_right_3" ||
		object->getType() == "door_0" ||
		object->getType() == "door_1" ||
		object->getType() == "door_2" ||
		object->getType() == "door_3" ||
		object->getType() == "door_exit" ||
		object->getType() == "lever" ||
		object->getType() == "trigger" ||
		object->getType() == "sign_0" ||
		object->getType() == "sign_1" ||
		object->getType() == "sign_2" ||
		object->getType() == "sign_3" ||
		object->getType() == "sign_exit" ||
		object->getType() == "swing" ||
		object->getType() == "slope_L_1x1" ||
		object->getType() == "slope_R_1x1" ||
		object->getType() == "slope_L_2x1_0" ||
		object->getType() == "slope_L_2x1_1" ||
		object->getType() == "slope_R_2x1_0" ||
		object->getType() == "slope_R_2x1_1" ||
		object->getType() == "flag" ||
		object->getType() == "e_bounce_U_0" ||
		object->getType() == "e_bounce_U_1" ||
		object->getType() == "bounce_2" ||
		object->getType() == "bounce_3" ||
		object->getType() == "cam_lock" ||
		object->getType() == "cam_unlock" ||
		object->getType() == "cam_lock_y" ||
		object->getType() == "cam_unlock_y" ||
		object->getType() == "cam_lock_ws" ||
		object->getType() == "cam_unlock_ws") {

		return;
	}
	else if (object->getType() == "e_flyling") {
		
	} else if (object->getType() == "e_flugan") {
		
	} else if (object->getType()[0] == 'p' && object->getType()[1] == 'o' && object->getType()[2] == 't') {
		
	} else if (object->getType() == "player") {
		std::cout << "hello particle\n";
		cPlayer* player = static_cast<cPlayer*>(object);
		if (player->getVitalityMeterValue() >= 64) {
			return;
		}
		player->setVitalityMeterValue(player->getVitalityMeterValue() + 32);
		if (player->getVitalityMeterValue() > 64) {
			player->setVitalityMeterValue(64);
		}
		m_isDead = true;
	} else {
		m_velocityX = 0.0f;
		m_velocityY = 0.0f;
	}
}

void cParticleHealth::collisionReactionY(cBaseObject *object) {
	if (object->getType().substr(0, 6) == "level_" ||
		object->getType().substr(0, 5) == "door_" ||
		object->getType() == "lever" ||
		object->getType() == "trigger" ||
		object->getType() == "sign_0" ||
		object->getType() == "sign_1" ||
		object->getType() == "sign_2" ||
		object->getType() == "sign_3" ||
		object->getType() == "sign_exit" ||
		object->getType() == "swing" ||
		object->getType() == "slope_L_1x1" ||
		object->getType() == "slope_R_1x1" ||
		object->getType() == "slope_L_2x1_0" ||
		object->getType() == "slope_L_2x1_1" ||
		object->getType() == "slope_R_2x1_0" ||
		object->getType() == "slope_R_2x1_1" ||
		object->getType() == "flag" ||
		object->getType() == "e_bounce_U_0" ||
		object->getType() == "e_bounce_U_1" ||
		object->getType() == "bounce_2" ||
		object->getType() == "bounce_3" ||
		object->getType() == "cam_lock" ||
		object->getType() == "cam_unlock" ||
		object->getType() == "cam_lock_y" ||
		object->getType() == "cam_unlock_y" ||
		object->getType() == "cam_lock_ws" ||
		object->getType() == "cam_unlock_ws") {

		return;
	} else if (object->getType() == "player") {
		collisionReactionX(object);
	}
	else if (object->getType().at(0) == 'p' && object->getType().at(1) == 'o' && object->getType().at(2) == 't') {
		collisionReactionX(object);
	}
	else {
		m_velocityY = -5.0f;
	}
}