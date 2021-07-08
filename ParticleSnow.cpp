#include "ParticleSnow.h"
#include "RenderingManager.h"
#include "SoundsManager.h"
#include "PlayerSwingState.h"
#include "EntityPigan.h"
#include "EntityPiganHurtState.h"
#include "SoundsManager.h"

//void cParticleSnow::die(cBaseObject *killer) {
//	////std::cout << "cParticleShot::die " << "\n";
//	//cSoundsManager::stop(eSoundTag::hitGround);
//	//cSoundsManager::play(eSoundTag::hitGround);
//	m_isDead = true;
//}

void cParticleSnow::collisionReactionX(cBaseObject *object) {
	//std::cout << "cParticleShot::collisionReactionX " << "\n";
	if (object->getType().substr(0, 2) == "e_" || 		
		object->getType().substr(0, 5) == "door_" ||
		object->getType().substr(0, 6) == "level_" ||
		object->getType().substr(0, 7) == "target_" ||
		object->getType().substr(0, 8) == "trigger_" ||
		object->getType().substr(0, 5) == "sign_" ||
		object->getType() == "swing" ||
		object->getType().substr(0, 8) == "slope_L_" ||
		object->getType().substr(0, 8) == "slope_R_" ||
		object->getType() == "flag" ||
		object->getType() == "bounce_2" ||
		object->getType() == "bounce_3" ||
		
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
	}
	else if (object->getType() == "clip") {
		die(object);
		//m_isDead = true;
	}
	else {
		die(object);
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

void cParticleSnow::collisionReactionY(cBaseObject *object) {
	//std::cout << "cParticleSnow::collisionReactionY" << "\n";
	if (object->getType().substr(0, 6) == "level_" ||
		object->getType().substr(0, 5) == "door_" ||
		object->getType().substr(0, 7) == "target_" ||
		object->getType().substr(0, 8) == "trigger_" ||
		object->getType().substr(0, 5) == "sign_" ||
		object->getType() == "swing" ||
		object->getType() == "flag" ||
		object->getType() == "e_bounce_U_0" ||
		object->getType() == "e_bounce_U_1" ||
		object->getType() == "bounce_2" ||
		object->getType() == "bounce_3" ||
		object->getType().substr(0, 4) == "cam_" ||
		object->getType().substr(0, 5) == "wall_" ||
		object->getType() == "player") {

		return;
	}
	else if (object->getType().substr(0, 3) == "pot") {
		collisionReactionX(object);
	}
	else if (object->getType() == "clip") {
		//if (!m_isDead) {
		hitGround(object);
		//die();
	//}		
	}
	else if (object->getType() == "clip_drop" || object->getType() == "clip_top" || object->getType() == "slope_top" || object->getType() == "slope_L_1x1" ||
		object->getType() == "slope_R_1x1" ||
		object->getType() == "slope_L_2x1_0" ||
		object->getType() == "slope_L_2x1_1" ||
		object->getType() == "slope_R_2x1_0" ||
		object->getType() == "slope_R_2x1_1") {

		if (m_velocityY > 0.0f) {
			//std::cout << m_slopeOffsetX << "\n";
			//if (!m_isDead) {
			hitGround(object);
			//die();
		//}

		}
	}
	else {
		/*collisionReactionX(object);
		m_y = m_previousY;
		m_velocityY *= -0.9f;*/
	}
}