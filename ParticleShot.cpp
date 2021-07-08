#include "ParticleShot.h"
#include "RenderingManager.h"
#include "SoundsManager.h"
#include "PlayerSwingState.h"
#include "EntityPigan.h"
#include "EntityPiganHurtState.h"
#include "SoundsManager.h"

void cParticleShot::die(cBaseObject *killer) {
	//std::cout << "cParticleShot::die " << "\n";
	/*cSoundsManager::stop(eSoundTag::hitGround);
	cSoundsManager::play(eSoundTag::hitGround);*/
	m_isDead = true;
}

void cParticleShot::collisionReactionX(cBaseObject *object) {
	//std::cout << "cParticleShot::collisionReactionX " << "\n";
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
		object->getType() == "slope_L_1x1" ||
		object->getType() == "slope_R_1x1" ||
		object->getType() == "slope_L_2x1_0" ||
		object->getType() == "slope_L_2x1_1" ||
		object->getType() == "slope_R_2x1_0" ||
		object->getType() == "slope_R_2x1_1" ||
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
	}
	else if (object->getType() == "e_brick") {
		object->die(this);
		die(object);
	}
	else if (object->getType() == "e_flyling") {
		
	}
	else if (object->getType() == "e_flugan") {
		
	} else if (object->getType() == "e_grodorr") {
		m_isDead = true;
		object->hurt(this, 5.0f);
	}
	else if (object->getType()[0] == 'p' && object->getType()[1] == 'o' && object->getType()[2] == 't') {
		
	}
	else if (object->getType() == "clip") {
		//m_isDead = true;
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

void cParticleShot::collisionReactionY(cBaseObject *object) {
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
	}
	else if (object->getType().at(0) == 'p' && object->getType().at(1) == 'o' && object->getType().at(2) == 't') {
		collisionReactionX(object);
	}
	else if (object->getType() == "clip") {
		//if (!m_isDead) {
			hitGround(object);
			//die();
		//}		
	}
	else if (object->getType() == "clip_top" || object->getType() == "slope_top" || object->getType() == "slope_L_1x1" ||
		object->getType() == "slope_R_1x1" ||
		object->getType() == "slope_L_2x1_0" ||
		object->getType() == "slope_L_2x1_1" ||
		object->getType() == "slope_R_2x1_0" ||
		object->getType() == "slope_R_2x1_1" ) {
		
		if (m_velocityY > 0.0f) {
			//if (!m_isDead) {
				hitGround(object);
				//die();
			//}
					
		}
	}
	else if (object->getType() == "e_brick") {
		collisionReactionX(object);
	}
	else {
		/*collisionReactionX(object);
		m_y = m_previousY;
		m_velocityY *= -0.9f;*/
	}
}