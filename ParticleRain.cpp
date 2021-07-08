#include "ParticleRain.h"
#include "RenderingManager.h"
#include "SoundsManager.h"
#include "PlayerSwingState.h"
#include "EntityPigan.h"
#include "EntityPiganHurtState.h"
#include "SoundsManager.h"

//void cParticleRain::die(cBaseObject *killer) {
//	////std::cout << "cParticleShot::die " << "\n";
//	//cSoundsManager::stop(eSoundTag::hitGround);
//	//cSoundsManager::play(eSoundTag::hitGround);
//	m_isDead = true;
//}

void cParticleRain::collisionReactionX(cBaseObject *object) {
	//std::cout << "cParticleShot::collisionReactionX " << "\n";
	if (object->getIsDead()) {
		return;
	}
	/*if (object->getIsSlope()) {
		collisionReactionSlopeX(object);
		return;
	}*/
	if (object->getType().substr(0, 5) == "coin_") {
	} else if (object->getType().substr(0, 5) == "door_") {
	} else if (object->getType().substr(0, 6) == "level_") {
	} else if (object->getType() == "player") {
	} else if (object->getType().substr(0, 5) == "sign_") {
	} else if (object->getType().substr(0, 5) == "shop_") {
	} else if (object->getType().substr(0, 8) == "slope_L_") {
	} else if (object->getType().substr(0, 8) == "slope_R_") {
	} else if (object->getType().substr(0, 7) == "target_") {
	} else if (object->getType().substr(0, 8) == "trigger_") {
	} else if (object->getType() == "clip") {
		//die(object);
		//m_isDead = true;
	} else if (object->getType() == "e_swing") {
	} else {
		//die(object);
		//m_isDead = true;
		//std::cout << object->getType() << "\n";
		//if (m_isDead == false) {
		//	m_isDead = true;
		//	object->m_particles.push_back(new cParticle);
		//	object->m_particles.at(object->m_particles.size() - 1)->loadConfig("Data\\Particles\\p_dust.cfg");

		//	//object->m_particles.at(object->m_particles.size() - 1)->setVelocityX(0.0f);

		//	std::cout << object->m_particles.at(object->m_particles.size() - 1)->getVelocityX() << "\n";

		//	object->m_particles.at(object->m_particles.size() - 1)->setX(object->getX());
		//	object->m_particles.at(object->m_particles.size() - 1)->setY(object->getY());
		//	object->m_particles.at(object->m_particles.size() - 1)->update(0.0f);

		//	cSoundsManager::m_soundBreakPot.play();
		//	cRenderingManager::addParticle(object->m_particles.at(object->m_particles.size() - 1));
		//}
	}
}

void cParticleRain::collisionReactionY(cBaseObject *object) {
	//std::cout << "cParticleRain::collisionReactionY " << object->getType() << "\n";
	/*if (object->getIsSlope()) {
		collisionReactionSlopeY(object);
		return;
	}*/
	if (object->getIsDead()) {
		return;
	}
	if (object->getType().substr(0, 4) == "cam_" ||
		object->getType().substr(0, 5) == "coin_" ||
		object->getType().substr(0, 6) == "chest_" ||
		object->getType().substr(0, 5) == "door_" ||
		object->getType().substr(0, 7) == "e_item_" ||
		object->getType().substr(0, 7) == "e_grass" ||
		object->getType().substr(0, 6) == "level_" ||
		object->getType() == "player" ||
		object->getType() == "swing" ||
		object->getType().substr(0, 5) == "sign_" ||
		object->getType().substr(0, 5) == "shop_" ||
		object->getType().substr(0, 8) == "trigger_" ||
		object->getType().substr(0, 5) == "wall_") {

		return;
	} else if (object->getType() == "clip" || object->getType() == "clip_crawl" || object->getType() == "clip_top" || object->getType() == "slope_top") {
		//if (!m_isDead) {
		hitGround(object);
		//die(object);
	//}		
	} else if (object->getType() == "slope_top" || object->getType() == "slope_L_1x1" ||
		object->getType() == "slope_R_1x1" ||
		object->getType() == "slope_L_2x1_0" ||
		object->getType() == "slope_L_2x1_1" ||
		object->getType() == "slope_R_2x1_0" ||
		object->getType() == "slope_R_2x1_1") {

		if (m_velocityY > 0.0f) {			
			hitGround(object);
			//die();
		//}

		}
	} else if (object->getType().substr(0, 7) == "target_") {
		if (object->getAnimTag() != eAnimTag::death) {
			hitGround(object);
		}
	} else if (object->getType() == "e_brick") {
		if (object->getLevelY() <= 0.0f) {
			m_doRemove = true;
			return;
		}
		hitGround(object);
		//object->die(this);
	} else if (object->getType() == "e_swing") {
	} else {
		if (object->getLevelY() <= 0.0f) {
			m_doRemove = true;
			return;
		}
		hitGround(object);

		m_movedVelocityX = object->getVelocityX();
		/*collisionReactionX(object);
		m_y = m_previousY;
		m_velocityY *= -0.9f;*/
	}
}