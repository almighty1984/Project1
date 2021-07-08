#include "ParticleSenseGrodorr.h"
#include "Object.h"
#include "Entity.h"
#include "EntityGrodorrAttackState.h"
#include "InputManager.h"
#include "SoundsManager.h"
#include "ParticleSense.h"
#include "Player.h"

void cParticleSenseGrodorr::collisionReactionX(cBaseObject *object) {
	if (m_parent != nullptr && m_parent->getIsRiding()) {
		return;
	}
	if (object->getType().substr(0, 4) == "clip") {
	} else if (object->getType().substr(0, 4) == "coin") {
	} else if (object->getType().substr(0, 3) == "cam") {
	} else if (object->getType().substr(0, 5) == "door_") {
	} else if (object->getType().substr(0, 8) == "e_bounce") {
	} else if (object->getType() == "e_brick") {
	} else if (object->getType() == "e_flugan") {
	} else if (object->getType() == "e_flyling") {
	} else if (object->getType() == "e_grodorr") {
	} else if (object->getType() == "e_pigan") {
	} else if (object->getType().substr(0, 11) == "e_item") {
	} else if (object->getType().substr(0, 8) == "trigger_") {
	} else if (object->getType().substr(0, 5) == "level") {
	} else if (object->getType().substr(0, 4) == "view") {
	} else if (object->getType().substr(0, 4) == "path") {
	} else if (object->getType().substr(0, 4) == "sign") {
	} else if (object->getType().substr(0, 5) == "slope") {
	} else if (object->getType().substr(0, 5) == "wall_") {
	} else if (object->getType().substr(0, 5) == "water") {
	} else if (object->getType().substr(0, 4) == "coin") {
	} else if (object->getType() == "e_grass") {
		//std::cout << "sensed grass" << "\n";
		if (m_parent == nullptr) { return; };
		if (m_timeBeingAlive > 1.0f) { return; }
		object->setIsIdle(false);
		int num = 0;
		if (m_parent->getMiddleX() < object->getMiddleX()) {
			object->setIsFacingLeft(false);
			num = (int)abs(object->getMiddleX() - m_parent->getMiddleX());
			//std::cout << num << " " << num / 2 << "\n";
		} else {
			object->setIsFacingLeft(true);
			num = (int)abs(object->getMiddleX() - m_parent->getMiddleX());
			//std::cout << num << " " << num / 2 << "\n";
		}
		float tileX = 32.0f * 7.0f - ((num / 4) * 32.0f);
		if (tileX <= 0.0f) {
			tileX = 0.0f;
		} else if (tileX > 0.0f && tileX <= 48.0f) {
			tileX = 32.0f;
		} else if (tileX > 48.0f && tileX < 80.0f) {
			tileX = 64.0f;
		} else if (tileX > 80.0f && tileX < 128.0f) {
			tileX = 96.0f;
		}
		object->setTileOffsetX(tileX);
	} else if (object->getType() == "player" || object->getType() == "e_pigan") {
		m_isDead = true;
		
		if (object->getIsInWater()) {
			return;
		}
		if (m_parent != nullptr) {			
			if (m_velocityX < 0.0f) {
				std::cout << "left" << "\n";
				m_parent->senseCollidedLeft(object);
			} else if (m_velocityX > 0.0f) {
				std::cout << "right" << "\n";
				m_parent->senseCollidedRight(object);
			}			
		}
	} else if (object->getType().substr(0, 7) == "target_") {
		//m_isDead = true;
		if (object->getAnimTag() == eAnimTag::idle) {
			//std::cout << "cParticleSenseGrodorr::collisionReactionX " << object->getAnim().y << "\n";
			m_doRemove = true;			
		}
	} else if (object->getType() == "e_flyling") {
		return;
	} else {
		//m_isDead = true;
	}
}

void cParticleSenseGrodorr::collisionReactionY(cBaseObject *object) {
	collisionReactionX(object);
}