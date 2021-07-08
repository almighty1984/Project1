
#include "Entity.h"

bool cEntity::collisionCheckY(cBaseObject* object) {
	if (object == nullptr || object->getIsDead() || m_isDead) {
		return false;
	}
	if (object->getIsSlope()) {
		return collisionCheckSlopeY(object);
	}

	float bottom = getBottom();
	float top = getTop();

	if (m_velocityY + m_movedVelocityY < 0.0f) {
		if (getRight() - 4 > object->getLeft() && getLeft() + 4 < object->getRight()) {
			if (top < object->getBottom() && top + 4 > object->getTop()) {
				//collisionReactionY(object);
				return true;
				//object->collisionReactionY(this);
			}
		}
	} else if (m_velocityY + m_movedVelocityY > 0.0f) {
		if (bottom >= object->getTop() && top < object->getBottom()/*getTop() + 10 < object->getBottom()*/) {
			// Be a little more lenient if near a wall we can jump on
			if (m_isNearWallLeft || m_isNearWallRight) {
				if (getMiddleX() + 0 <= object->getRight() && getMiddleX() - 0 >= object->getLeft()) {
					//collisionReactionY(object);
					return true;
				}
			} else {
				if (getLeft() + 4 <= object->getRight() - 2 && getRight() - 4 >= object->getLeft() + 2) {
					//collisionReactionY(object);
					return true;
				}
			}
		}
	}
	return false;
}