#include "PlayerSwingState.h"
#include "PlayerGrassState.h"
#include "SoundsManager.h"
#include "InputManager.h"

cPlayerSwingState::cPlayerSwingState() {
	m_secondCall = false;
}

cPlayerSwingState::~cPlayerSwingState() {

}

void cPlayerSwingState::update(cApplication* application, float time, cPlayer* player) {	
	if (player == NULL) {
		return;
	}

	if (m_secondCall == false) {
		m_secondCall = true;
		std::cout << "In swing" << std::endl;
		//player->m_belowObject = NULL;
		//player->setIsCameraLockedX(false);

		//player->setIsHidden(true);

		player->setPositionY(player->m_morphObject->getPositionY()-16);
		player->setVelocityY(0.0f);

		player->m_morphObject->setImagePath("Data\\Images\\player_roten_swing.png");
		//player->m_morphObject->setTileOffsetX(512.0f);
		player->m_morphObject->setIsHidden(false);
	}

	// Sprint release
	if (player->keysHeld[cInputManager::get().getSprintKey()])
		player->keysHeld[cInputManager::get().getSprintKey()] = false;

	// Move left
	if (player->keysHeld[cInputManager::get().getLeftKey()]) {
		player->m_facingLeft = true;
		player->m_morphObject->setFacingLeft(true);
		//player->m_isIdle = false;

		if (player->m_positionY + 64 > player->m_morphObject->getPositionY() + 8) {
			if (player->getVelocityX() > -4.5f){
				player->m_velocityX -= player->m_moveAcc*0.4f;
			} else if (player->getVelocityX() < 4.5f) {
				player->m_velocityX += player->m_moveAcc*0.4f;
			}
		}
	}
	
	
	// Move right
	if (player->keysHeld[cInputManager::get().getRightKey()]) {
		player->m_facingLeft = false;
		player->m_morphObject->setFacingLeft(false);

		//player->m_isIdle = false;		

		if (player->m_positionY + 64 > player->m_morphObject->getPositionY() + 8) {
			if (player->getVelocityX() < 4.5f){
				player->m_velocityX += player->m_moveAcc*0.4f;
			} else if (player->getVelocityX() > -4.5f) {
				player->m_velocityX -= player->m_moveAcc*0.4f;
			}
		}
	}

	float posDiffX=0.0f;

	if(player->getFacingLeft() == false) {		
		posDiffX = player->getPositionX()+player->getWidth()/2 - player->m_morphObject->getPositionX()+8 - 16.0f;
		std::cout << posDiffX << std::endl;
		if(posDiffX >= -100.0f && posDiffX <= -35.0f)
			player->m_morphObject->setTileOffsetX(0.0f);
		else if(posDiffX >= -35.0f && posDiffX <= -25.0f)
			player->m_morphObject->setTileOffsetX(128.0f);
		else if(posDiffX >= -25.0f && posDiffX <= -15.0f)
			player->m_morphObject->setTileOffsetX(256.0f);
		else if(posDiffX >= -15.0f && posDiffX <= -5.0f)
			player->m_morphObject->setTileOffsetX(384.0f);
		else if(posDiffX >= -5.0f && posDiffX <= 5.0f)
			player->m_morphObject->setTileOffsetX(512.0f);

		else if(posDiffX >= 5.0f && posDiffX <= 15.0f)
			player->m_morphObject->setTileOffsetX(640.0f);
		else if(posDiffX >= 15.0f && posDiffX <= 25.0f)
			player->m_morphObject->setTileOffsetX(768.0f);
		else if(posDiffX >= 25.0f && posDiffX <= 35.0f)
			player->m_morphObject->setTileOffsetX(896.0f);
		else if(posDiffX >= 35.0f && posDiffX <= 100.0f)
			player->m_morphObject->setTileOffsetX(1024.0f);
	}
	else {
		posDiffX = player->getPositionX()+player->getWidth()/2 - player->m_morphObject->getPositionX()+8 - 16.0f;
		std::cout << posDiffX << std::endl;
		if(posDiffX >= -100.0f && posDiffX <= -35.0f)
			player->m_morphObject->setTileOffsetX(1024.0f);
		else if(posDiffX >= -30.0f && posDiffX <= -25.0f)
			player->m_morphObject->setTileOffsetX(896.0f);
		else if(posDiffX >= -25.0f && posDiffX <= -15.0f)
			player->m_morphObject->setTileOffsetX(768.0f);
		else if(posDiffX >= -15.0f && posDiffX <= -5.0f)
			player->m_morphObject->setTileOffsetX(640.0f);

		else if(posDiffX >= -5.0f && posDiffX <= 5.0f)
			player->m_morphObject->setTileOffsetX(512.0f);
		else if(posDiffX >= 5.0f && posDiffX <= 15.0f)
			player->m_morphObject->setTileOffsetX(384.0f);
		else if(posDiffX >= 15.0f && posDiffX <= 25.0f)
			player->m_morphObject->setTileOffsetX(256.0f);
		else if(posDiffX >= 25.0f && posDiffX <= 35.0f)
			player->m_morphObject->setTileOffsetX(128.0f);
		else if(posDiffX >= 35.0f && posDiffX <= 100.0f)
			player->m_morphObject->setTileOffsetX(0.0f);		
	}

	if (player->getPositionX()+player->getWidth()/2 < player->m_morphObject->getPositionX()+8) {
		//player->m_animateBackwards = false;
		if (player->m_velocityX < 4.0f) {
			player->m_velocityX += player->m_moveDec*1.25f;
		}
		
		if(player->getFacingLeft() == true) {
			player->setTileOffsetX(0.0f);
		} else {
			player->setTileOffsetX(player->getWidth()*player->getNumFrames()-player->getWidth());
		}
		//player->m_morphObject->setTileOffsetX(0.0f);

		//offsetX = (player->m_morphObject->getPositionX()+8) - (player->getPositionX()+32);
		////player->setPositionY(player->m_morphObject->getPositionY() - offsetX);
		////player->setVelocityY( player->getVelocityX() );
		//player->m_velocityY = offsetX*0.75f*(player->m_velocityX*0.05f);
	} else if (player->getPositionX()+player->getWidth()/2 > player->m_morphObject->getPositionX()+8) {
		//player->m_animateBackwards = true;		
		if (player->m_velocityX > -4.0f) {
			player->m_velocityX -= player->m_moveDec*1.25f;
		}

		if(player->getFacingLeft() == true) {
			player->setTileOffsetX(player->getWidth()*player->getNumFrames()-player->getWidth());
		} else {
			player->setTileOffsetX(0.0f);
		}

		//player->m_morphObject->setTileOffsetX(512.0f);

		/*offsetX = (player->getPositionX()+32) - (player->m_morphObject->getPositionX()+8);
		player->m_velocityY = offsetX*0.75f*(-player->m_velocityX*0.05f);*/
	}

	if (player->keysHeld[cInputManager::get().getJumpKey()] ||
		player->mouseButtonsHeld[cInputManager::get().getJumpMouseButton()] ||
		(player->getFacingLeft() == false && posDiffX >= 50.0f && posDiffX <= 100.0f) ||
		(player->getFacingLeft() == true && posDiffX >= -100.0f && posDiffX <= -50.0f) ) {
		
		player->setState(new cPlayerGrassState);
		player->setInSwing(false);

		std::cout << "Dropped swing\n";

		//player->setTileOffsetX(768.0f);
		//player->setTileOffsetY(0.0f);
		//player->m_animCurrent.y = 0;
		player->m_morphObject->setWidth(16);
		player->m_morphObject->setHeight(16);		
		//player->m_morphObject->setIsHidden(true);
		
		if(posDiffX >= -70.0f && posDiffX <= -60.0f) {
			player->setVelocityY(-7.5f);
		}
		else if(posDiffX >= -60.0f && posDiffX <= -50.0f) {
			player->setVelocityY(-7.0f);
			player->setVelocityX( player->getVelocityX() * 1.05f);
		}
		else if(posDiffX >= -50.0f && posDiffX <= -40.0f) {
			player->setVelocityY(-6.5f);
			player->setVelocityX( player->getVelocityX() * 1.10f);
		}
		else if(posDiffX >= -40.0f && posDiffX <= -30.0f) {			
			player->setVelocityY(-6.0f);
			player->setVelocityX( player->getVelocityX() * 1.15f);
		}
		else if(posDiffX >= -30.0f && posDiffX <= -20.0f) {
			player->setVelocityY(-5.5f);
			player->setVelocityX( player->getVelocityX() * 1.20f);
		}
		else if(posDiffX >= -20.0f && posDiffX <= -10.0f) {
			player->setVelocityY(-5.0f);
			player->setVelocityX( player->getVelocityX() * 1.25f);
		}

		else if(posDiffX >= -10.0f && posDiffX <= 0.0f)	{
			player->setVelocityY(-4.5f);
			player->setVelocityX( player->getVelocityX() * 1.3f);
		}

		else if(posDiffX >= 0.0f && posDiffX <= 10.0f) {
			player->setVelocityY(-5.0f);
			player->setVelocityX( player->getVelocityX() * 1.25f);
		}
		else if(posDiffX >= 10.0f && posDiffX <= 20.0f) {
			player->setVelocityY(-5.5f);
			player->setVelocityX( player->getVelocityX() * 1.20f);
		}
		else if(posDiffX >= 20.0f && posDiffX <= 30.0f) {
			player->setVelocityY(-6.0f);
			player->setVelocityX( player->getVelocityX() * 1.15f);
		}
		else if(posDiffX >= 30.0f && posDiffX <= 40.0f) {
			player->setVelocityY(-6.5f);
			player->setVelocityX( player->getVelocityX() * 1.10f);
		}
		else if(posDiffX >= 40.0f && posDiffX <= 50.0f) {
			player->setVelocityY(-7.0f);
			player->setVelocityX( player->getVelocityX() * 1.05f);
		}
		else if(posDiffX >= 50.0f && posDiffX <= 60.0f) {
			player->setVelocityY(-7.5f);
		}

		std::cout << player->m_velocityY << std::endl;
		cSoundsManager::get().m_soundSwingDetach.play();
		cSoundsManager::get().m_soundJump.play();
	}

	// Throw
	if ((player->keysHeld[cInputManager::get().getThrowKey()] || player->mouseButtonsHeld[cInputManager::get().getThrowMouseButton()]) && !player->getIsDead() && !player->m_lockThrow) {
		player->attackThrow();
	}
	if (player->m_isThrowing == true) {
		//std::cout << "player is attacking" << std::endl;
		++player->m_timerThrow;
		if (player->m_timerThrow >= player->m_timeLimitThrow) {
			player->m_isThrowing = false;
			player->m_timerThrow = 0;
			//player->m_tileOffsetX = 0.0f;
			player->m_lockMove = false;
		}
	}
}