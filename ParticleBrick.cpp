#include "ParticleBrick.h"
#include "RenderingManager.h"
#include "SoundsManager.h"
#include "PlayerSwingState.h"
#include "EntityPigan.h"
#include "EntityPiganHurtState.h"
#include "SoundsManager.h"

void cParticleBrick::die(cBaseObject *killer) {
	if (killer == nullptr) {
		return;
	}
	//std::cout << "cParticleBrick::die " << "\n";
	/*cSoundsManager::stop(eSoundTag::hitHead);
	cSoundsManager::play(eSoundTag::hitHead);*/
	m_isDead = true;
}

void cParticleBrick::collisionReactionX(cBaseObject *object) {
	if (object->getIsSlope()) {
		collisionReactionSlopeX(object);
		return;
	}
	//std::cout << "cParticleBrick::collisionReactionX " << "\n";
	if (object->getType().substr(0, 4) == "cam_" ||
		object->getType().substr(0, 5) == "door_" ||
		object->getType().substr(0, 6) == "level_" ||
		object->getType().substr(0, 8) == "trigger_" ||
		object->getType().substr(0, 5) == "sign_" ||
		object->getType() == "swing" ||
		object->getType() == "e_bounce_U_0" ||
		object->getType() == "e_bounce_U_1" ||
		object->getType() == "player") {
		return;
	} else if (object->getType() == "e_flyling") {
		if (object->getIsDead()) { return; };

		cSoundsManager::stop(eSoundTag::hit);
		cSoundsManager::play(eSoundTag::hit);
		object->die(this);		
	} else if (object->getType() == "e_brick") {
		//if (object->getTimeBeingAlive() > 10.0f && m_timeBeingAlive > 6.0f) {			
			//m_velocityX *= -1.0f;
			//die(object);
			//object->die(this);
		//}		
	} else if (object->getType() == "e_flugan") {
		if (cSoundsManager::isPlaying(eSoundTag::hit)) {
			cSoundsManager::stop(eSoundTag::hit);
		}
		cSoundsManager::play(eSoundTag::hit);
		if (object->getIsDead() == false) {
			cEntityFlugan* entityFlugan;
			entityFlugan = static_cast<cEntityFlugan*>(object);
			std::cout << "p_brick collided with entity_flugan" << "\n";
			entityFlugan->setIsHurting(true);
			entityFlugan->setIsAttacking(true);
			entityFlugan->setNumHealth(entityFlugan->getNumHealth() - 50);
			entityFlugan->setHurtAgainDelayValue(entityFlugan->getHurtAgainDelay());
			//object->setIsDead(true);
			m_isDead = true;
		}
	} else if (object->getType() == "p_brick") {
		
	} else if (object->getType() == "p_melee") {

	} else if (object->getType().substr(0, 3) == "pot") {
		return;
	} else if (object->getType() == "clip") {
		m_velocityX *= -1.0f;
	} else if (object->getType() == "clip_drop") {
	} else if (object->getType() == "slope_top" || object->getType() == "slope_L_1x1" ||
		object->getType() == "slope_R_1x1" ||
		object->getType() == "slope_L_2x1_0" ||
		object->getType() == "slope_L_2x1_1" ||
		object->getType() == "slope_R_2x1_0" ||
		object->getType() == "slope_R_2x1_1") {

		/*if (m_velocityY > 0.0f) {
			hitGround(object);
		}*/
	} else if (object->getType().substr(0, 7) == "target_") {
		if (object->getAnimTag() == eAnimTag::idle) {
			m_velocityX *= -1.0f;
			m_x = m_previousX;
		}
	}
	else {
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

void cParticleBrick::collisionReactionY(cBaseObject *object) {
	if (object->getIsSlope()) {
		collisionReactionSlopeY(object);
		return;
	}
	/*std::cout << object->getType() << "\n";
	return;*/
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
		object->getType() == "cam_unlock_ws" ||
		object->getType() == "wall_in_top" ||
		object->getType() == "wall_in_bottom" ||
		object->getType() == "wall_in_left" ||
		object->getType() == "wall_in_right" ||
		object->getType() == "wall_out_left" ||
		object->getType() == "wall_out_right" ||
		object->getType() == "wall_out_top" ||
		object->getType() == "wall_out_bottom" ||
		object->getType() == "player") {

		return;
	} else if (object->getType() == "e_brick") {
		//collisionReactionX(object);
		//hitGround(object);
	} else if (object->getType().substr(0, 3) == "pot") {
		collisionReactionX(object);
	} else if (object->getType() == "clip") {
		if (m_velocityY < 0.0f) {
			m_y = object->getBottom()  + 8 - m_subtractUp;
			m_velocityY = abs(m_velocityY);
		} else {
			hitGround(object);
		}		
	} else if (object->getType() == "clip_top" || object->getType() == "clip_drop") {
		if (m_velocityY > 0.0f) {
			hitGround(object);
		}
	} else if (object->getType().substr(0, 7) == "target_") {
		hitGround(object);
	} else {
		//m_velocityY = -m_velocityY;
		/*collisionReactionX(object);
		m_y = m_previousY;
		m_velocityY *= -0.9f;*/
	}
}