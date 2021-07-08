#include "Player.h"
#include "Entity.h"

bool cPlayer::collisionCheckEntityX(cEntity* entity) {
	//float heightCheck;
	//return;
	if (entity == nullptr) {
		return false;
	}
	/*if (entity->getIsStatic() && m_velocityX == 0.0f) {
		return;
	}*/
	/*if (m_isCarrying && entity->getCarrier() != nullptr && this == entity->getCarrier()) {
		return;
	}*/

	if (m_isThrowing && m_thrownObject == entity) {
		return false;
	}
	/*if (m_velocityX < 1.0f && m_velocityX > -1.0f) {
		return;
	}*/

	/*if (getAnimTag() == eAnimTag::duck && entity->getMiddleY() < getBottom()) {
		return;
	}*/

	//if (m_isRiding && m_belowObject == entity) {
	//	//std::cout << "Won't collide X with below object" << "\n";
	//	return false;
	//}

	if (entity->getIsDead() || m_isDead) {
		return false;
	}


	if (getTop() + 4 < entity->getBottom() && getBottom() - 4 > entity->getTop()) {
		// Moving left or entity moving right
		if (m_velocityX + m_movedVelocityX < 0.0f || entity->getVelocityX() + entity->getMovedVelocityX() > 0.0f) {
			if (getLeft() < entity->getRight() && getRight() > entity->getLeft()) {
				//collisionReactionEntityX(entity);
				//entity->collisionReactionX(this);
				//return;
				return true;
			}
		}
		// Moving right or entity moving left
		if (m_velocityX + m_movedVelocityX > 0.0f || entity->getVelocityX() + entity->getMovedVelocityX() < 0.0f) {
			if (getRight() > entity->getLeft() && getLeft() < entity->getRight()) {
				//collisionReactionEntityX(entity);
				//entity->collisionReactionX(this);
				return true;
			}
		}

	}



	//else if (getLeft() < entity->getRight() && getRight() > entity->getLeft()) {
	//	collisionReactionEntityX(entity);
	//	entity->collisionReactionX(this);
	//	//std::cout << "Collided right\n";			
	//}
	return false;
}