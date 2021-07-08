#include "ParticleGrevertBounce.h"
#include "SoundsManager.h"

void cParticleGrevertBounce::collisionReactionX(cBaseObject* object) {
	//std::cout << "cParticleGrodorr::collisionReactionX " << object->getType() << "\n";
	if (object->getType() == "cam_lock" || object->getType() == "cam_unlock" ||
		object->getType() == "cam_lock_ws" || object->getType() == "cam_unlock_ws" ||
		object->getType() == "clip" ||
		object->getType() == "clip_top" ||
		object->getType() == "clip_bot" ||
		object->getType() == "door_0" || object->getType() == "door_exit" ||
		object->getType() == "view_lock" || object->getType() == "view_unlock" ||
		object->getType() == "wall_out_UP" ||
		object->getType() == "wall_out_DOWN" ||
		object->getType() == "wall_out_LEFT" ||
		object->getType() == "wall_out_RIGHT" ||
		object->getType() == "wall_in_UP" ||
		object->getType() == "wall_in_DOWN" ||
		object->getType() == "wall_in_LEFT" ||
		object->getType() == "wall_in_RIGHT" ||
		object->getType() == "p_sense") {
		return;
	} else if (object->getType() == "player") {
		collisionReactionY(object);
	} else if (object->getType() == "trigger") {
		return;
	} else if (object->getType().substr(0, 7) == "target_") {
		return;
	} else if (object->getType() == "e_flugan") {
		return;
	} else if (object->getType() == "e_grodorr") {
		return;
	} else if (object->getType() == "e_flyling") {
		return;
	} else {
		return;
	}
}

void cParticleGrevertBounce::collisionReactionY(cBaseObject* object) {
	 if (object->getType() == "player" && object->getIsOnGround()) {
		 m_doRemove = true;
		 
		 object->setVelocityY(m_velocityY);
		 
		 if (!cSoundsManager::isPlaying(eSoundTag::bounce)) {
			 cSoundsManager::play(eSoundTag::bounce);
		 }
	}
}