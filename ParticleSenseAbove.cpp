#include "Object.h"
#include "Entity.h"
#include "EntityGrodorrAttackState.h"
#include "InputManager.h"
#include "SoundsManager.h"
#include "ParticleSenseAbove.h"
#include "Player.h"


void cParticleSenseAbove::collisionReactionX(cBaseObject* object) {
	/*if (object->getIsDead()) {
		return;
	}*/

	if (object->getIsAnim() && object->getAnimTag() == eAnimTag::death) {
		return;
	}
	if (object->getType().substr(0, 3) == "cam" ||
		object->getType() == "clip_top" ||
		object->getType() == "door_0" || object->getType() == "door_exit" ||
		object->getType() == "e_brick" ||
		object->getType().substr(0, 11) == "e_item" ||
		object->getType().substr(0, 5) == "level" ||
		object->getType().substr(0, 4) == "view" ||
		object->getType().substr(0, 4) == "path" ||
		object->getType().substr(0, 4) == "sign" ||
		object->getType().substr(0, 5) == "slope" ||
		object->getType().substr(0, 5) == "wall_" ||
		object->getType().substr(0, 5) == "water") {
		return;
	} else if (object->getType() == "clip_crawl") {
		if (m_parent != nullptr) {
			if (m_parent != nullptr && m_parent->getIsOnGround() && !object->getIsCarried()) {
				m_parent->senseCollidedAbove(object);
			}
		}
		return;
	} else if (object->getType() == "player") {
		return;
	} else if (object->getType().substr(0, 8) == "trigger_") {
		return;
	} else if (object->getType().substr(0, 7) == "target_") {
		return;
	} else if (object->getType() == "e_flyling") {
		return;
	} else {
		return;
	}
}

void cParticleSenseAbove::collisionReactionY(cBaseObject* object) {
	return;
}