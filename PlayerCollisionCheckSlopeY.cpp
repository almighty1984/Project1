#include "Player.h"

bool cPlayer::collisionCheckSlopeY(cBaseObject* object) {
	char offsetY = 0;
	if ((!m_isInWater && m_velocityY <= m_fallAcc)/* || (m_isInWater && m_velocityY <= m_fallAcc)*/) {
		offsetY = 8;
	}

	float bottom = getBottom() + offsetY + 0;

	float top = getTop() + 16;

	// Moving up
	if (m_velocityY < 0.0f) {
		m_slopeOffsetX = 16 - abs(getMiddleX() - object->getRight());
		if (object->getType() == "slope_LU_1x1") {
			if (top <= object->getTop() + m_slopeOffsetX && bottom >= object->getTop()) {
				if (getMiddleX() >= object->getLeft() && getMiddleX() <= object->getRight()) {
					return true;
				}
			}
		} else if (object->getType() == "slope_RU_1x1") {
			if (top <= object->getBottom() - m_slopeOffsetX && bottom >= object->getTop()) {
				if (getMiddleX() >= object->getLeft() && getMiddleX() <= object->getRight()) {
					return true;
				}
			}
		} else if (object->getType() == "slope_LU_2x1_0") {
			if (top <= object->getTop() + m_slopeOffsetX * 0.5f && bottom >= object->getTop()) {
				if (getMiddleX() >= object->getLeft() && getMiddleX() <= object->getRight()) {
					return true;
				}
			}
		} else if (object->getType() == "slope_LU_2x1_1") {
			if (top <= object->getTop() + 8 + m_slopeOffsetX * 0.5f && bottom >= object->getTop()) {
				if (getMiddleX() >= object->getLeft() && getMiddleX() <= object->getRight()) {
					return true;
				}
			}
		} else if (object->getType() == "slope_RU_2x1_0") {
			if (top <= object->getBottom() - m_slopeOffsetX * 0.5f && bottom >= object->getTop()) {
				if (getMiddleX() >= object->getLeft() && getMiddleX() <= object->getRight()) {
					return true;
				}
			}
		} else if (object->getType() == "slope_RU_2x1_1") {
			if (top <= object->getBottom() - 8 - m_slopeOffsetX * 0.5f && bottom >= object->getTop()) {
				if (getMiddleX() >= object->getLeft() && getMiddleX() <= object->getRight()) {
					return true;
				}
			}
		} else {
			return false;
		}
	} else if (m_velocityY >= 0.0f) {
		m_slopeOffsetX = 16 - abs(getMiddleX() - object->getRight());
		if (object->getType().substr(0, 8) == "slope_LU" || object->getType().substr(0, 8) == "slope_RU") {
			return false;
		} else if (object->getType() == "slope_L_seam") {
			if (bottom >= (object->getTop() + 16 - m_slopeOffsetX) && top <= object->getBottom() + 16 - m_slopeOffsetX) {
				if (getMiddleX() >= object->getLeft() && getMiddleX() <= object->getRight()) {
					return true;
				}
			}
		} else if (object->getType() == "slope_R_seam") {
			if (bottom >= (object->getTop() + m_slopeOffsetX) && top <= object->getBottom() + m_slopeOffsetX) {
				if (getMiddleX() >= object->getLeft() && getMiddleX() <= object->getRight()) {
					return true;
				}
			}
		} else if (object->getType() == "slope_L_1x1") {
			if (bottom/*+waterOffset*/ >= object->getTop() + 16 - m_slopeOffsetX && top <= object->getBottom() + 16 - m_slopeOffsetX) {
				if (getMiddleX() >= object->getLeft() && getMiddleX() <= object->getRight()) {
					return true;
				}
			}
		} else if (object->getType() == "slope_R_1x1") {
			if (bottom/*+waterOffset*/ >= object->getTop() + m_slopeOffsetX && top <= object->getBottom() + m_slopeOffsetX) {
				if (getMiddleX() >= object->getX() && getMiddleX() <= object->getRight()) {
					return true;
				}
			}
		} else if (object->getType() == "slope_L_2x1_0") {
			if (bottom >= (object->getTop() + 16 - m_slopeOffsetX / 2) && top <= object->getBottom() + 16 - m_slopeOffsetX / 2) {
				if (getMiddleX() >= object->getLeft() && getMiddleX() <= object->getRight()) {
					return true;
				}
			}
		} else if (object->getType() == "slope_L_2x1_1") {
			if (bottom >= (object->getTop() + 8 - m_slopeOffsetX / 2) && top <= object->getBottom() + 8 - m_slopeOffsetX / 2) {
				if (getMiddleX() >= object->getLeft() && getMiddleX() <= object->getRight()) {
					return true;
				}
			}
		} else if (object->getType() == "slope_R_2x1_0") {
			if (bottom >= (object->getTop() + m_slopeOffsetX / 2) && top <= object->getBottom() + m_slopeOffsetX / 2) {
				if (getMiddleX() >= object->getLeft() && getMiddleX() <= object->getRight()) {
					return true;
				}
			}
		} else if (object->getType() == "slope_R_2x1_1") {
			if (bottom >= (object->getTop() + 8 + m_slopeOffsetX / 2) && top <= object->getBottom() + 8 + m_slopeOffsetX / 2) {
				if (getMiddleX() >= object->getLeft() && getMiddleX() <= object->getRight()) {
					return true;
				}
			}
		}
	}
	return false;
}