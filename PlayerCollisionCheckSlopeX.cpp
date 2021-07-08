#include "Player.h"


bool cPlayer::collisionCheckSlopeX(cBaseObject* object) {
	char offsetY = 0;
	char waterOffset = 0;

	if (m_isInWater) {
		waterOffset = 5;
	}

	float left = getLeft() /*- waterOffset*/;
	float right = getRight() /* + waterOffset*/;
	float bottom = getBottom() + 8 + waterOffset;
	float top = getTop() + 16 + waterOffset;

	//if (m_hasJumped) { return false; }
	offsetY = 16;
	m_slopeOffsetX = 16 - abs(getMiddleX() - object->getRight());
	left = getMiddleX() - 0;
	right = getMiddleX() + 0;

	if (m_velocityX + m_movedVelocityX < 0.0f/* && !m_isRiding*//* || (m_isRiding && m_belowObject != nullptr && m_belowObject->getVelocityX() < 0.0f)*/) {
		if (getMiddleX() < object->getRight() && getMiddleX() > object->getLeft()) {
			/*if (object->getType().substr(0, 7) == "slope_L") {
				return false;
			} else */if (object->getType() == "slope_R_1x1") {
				if (bottom > object->getTop() + m_slopeOffsetX && top < object->getBottom() + m_slopeOffsetX) {
					return true;
				}
			} else if (object->getType() == "slope_R_2x1_0") {
				if (bottom > object->getTop() + m_slopeOffsetX * 0.5f && top < object->getBottom() + m_slopeOffsetX * 0.5f) {
					return true;
				}
			} else if (object->getType() == "slope_R_2x1_1") {
				if (bottom > object->getTop() + 8 + m_slopeOffsetX * 0.5f && top < object->getBottom() + 8 + m_slopeOffsetX * 0.5f) {
					return true;
				}
			} else if (object->getType() == "slope_RU_2x1_0") {
				if (bottom > object->getTop() + offsetY - m_slopeOffsetX * 0.5f && top < object->getBottom() + offsetY - m_slopeOffsetX * 0.5f) {
					return true;
				}
			} else if (object->getType() == "slope_RU_2x1_1") {
				if (bottom > object->getTop() + offsetY - 8 - m_slopeOffsetX * 0.5f && top < object->getBottom() + offsetY - 8 - m_slopeOffsetX * 0.5f) {
					return true;
				}
			} else if (object->getType() == "slope_RU_1x1") {
				if (bottom > object->getTop() + offsetY - m_slopeOffsetX && top < object->getBottom() + offsetY - m_slopeOffsetX) {
					return true;
				}
			}
		}
	} else if (m_velocityX + m_movedVelocityX > 0.0f/* && !m_isRiding*//* || (m_isRiding && m_belowObject != nullptr && m_belowObject->getVelocityX() > 0.0f)*/) {
		if (getMiddleX() > object->getLeft() && getMiddleX() < object->getRight()) {

			/*if (object->getType().substr(0, 7) == "slope_R") {
				return false;
			} else */if (object->getType() == "slope_L_1x1") {
				if (bottom > object->getTop() + offsetY - m_slopeOffsetX && top < object->getBottom() + offsetY - m_slopeOffsetX) {
					return true;
				}
			} else if (object->getType() == "slope_L_2x1_0") {
				if (bottom > object->getTop() + offsetY - m_slopeOffsetX * 0.5f && top < object->getBottom() + offsetY - m_slopeOffsetX * 0.5f) {
					return true;
				}
			} else if (object->getType() == "slope_L_2x1_1") {
				if (bottom > object->getTop() + offsetY - 8 - m_slopeOffsetX * 0.5f && top < object->getBottom() + offsetY - 8 - m_slopeOffsetX * 0.5f) {
					return true;
				}
			} else if (object->getType() == "slope_LU_2x1_0") {
				if (bottom > object->getTop() + m_slopeOffsetX * 0.5f && top < object->getBottom() + m_slopeOffsetX * 0.5f) {
					return true;
				}
			} else if (object->getType() == "slope_LU_2x1_1") {
				if (bottom > object->getTop() + 8 + m_slopeOffsetX * 0.5f && top < object->getBottom() + 8 + m_slopeOffsetX * 0.5f) {
					return true;
				}
			} else if (object->getType() == "slope_LU_1x1") {
				if (bottom > object->getTop() + m_slopeOffsetX && top < object->getBottom() + m_slopeOffsetX) {
					return true;
				}
			}
		}
	}
	return false;
}