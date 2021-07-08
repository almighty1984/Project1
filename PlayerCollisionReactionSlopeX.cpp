#include "Player.h"

void cPlayer::collisionReactionSlopeX(cBaseObject* object) {
	if (object->getType() == "slope_L_1x1" || object->getType() == "slope_L_seam") {
		collisionReactionSlopeY(object);
	} else if (object->getType() == "slope_R_1x1" || object->getType() == "slope_R_seam") {
		collisionReactionSlopeY(object);
	} else if (object->getType() == "slope_L_2x1_0") {
		collisionReactionSlopeY(object);
	} else if (object->getType() == "slope_L_2x1_1") {
		collisionReactionSlopeY(object);
	} else if (object->getType() == "slope_R_2x1_0") {
		collisionReactionSlopeY(object);		
	} else if (object->getType() == "slope_R_2x1_1") {
		collisionReactionSlopeY(object);
	} else if (object->getType() == "slope_LU_1x1") {
		m_y = object->getY() + m_slopeOffsetX - m_subtractUp;
		m_velocityY = abs(m_velocityX);
	} else if (object->getType() == "slope_RU_1x1") {
		m_y = object->getY() + 16 - m_slopeOffsetX - m_subtractUp;
		m_velocityY = abs(m_velocityX);
	} else if (object->getType() == "slope_LU_2x1_0") {
		m_y = object->getY() + m_slopeOffsetX * 0.5f - m_subtractUp;
		m_velocityY = abs(m_velocityX) * 0.5f;
	} else if (object->getType() == "slope_LU_2x1_1") {
		m_y = object->getY() + 8 + m_slopeOffsetX * 0.5f - m_subtractUp;
		m_velocityY = abs(m_velocityX) * 0.5f;
	} else if (object->getType() == "slope_RU_2x1_0") {		
		m_velocityY = abs(m_velocityX) * 0.5f;
		m_y = object->getBottom() - m_slopeOffsetX * 0.5f - m_subtractUp + 2;		
	} else if (object->getType() == "slope_RU_2x1_1") {		
		m_velocityY = abs(m_velocityX) * 0.5f;
		m_y = object->getBottom() - 8 - m_slopeOffsetX * 0.5f - m_subtractUp + 2;				
	}
}