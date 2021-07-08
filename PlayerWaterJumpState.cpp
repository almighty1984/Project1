#include "PlayerGrassState.h"
#include "PlayerWaterJumpState.h"
#include "SoundsManager.h"
#include "InputManager.h"

#include <iostream>

cPlayerWaterJumpState::cPlayerWaterJumpState() {
	m_secondCall = false;
}

cPlayerWaterJumpState::~cPlayerWaterJumpState() {

}

void cPlayerWaterJumpState::update(cApp *app, cPlayer *p, float time) {
	if (p == nullptr || app == nullptr || p->getIsInShop()) {
		return;
	}
	if (m_secondCall == false) {
		m_secondCall = true;
		p->setTimerState(0.0f);
		p->setIsInWaterJump(true);
		p->setIsInWater(false);

		//p->setDoPlayMusic1(false);
		//p->setDoPlayMusic0(true);

		p->setSubtractUp(36);
		p->setSubtractDown(8);
		//p->resetCollisionBox();		
		
		std::cout << "cPlayerWaterJumpState" << "\n";
		p->setImagePath("Data\\Players\\Images\\player_roten_swim.png");
		p->setTileOffsetY(0.0f);

		p->setIsUpsideDown(false);
		p->setSpriteOffsetY(8);	
		//app->setUseEventInput(false);
		if (!cSoundsManager::isPlaying(eSoundTag::splash)) {
			cSoundsManager::play(eSoundTag::splash);
		}
	}
	std::cout << "cPlayerWaterJumpState " << p->getTimerState() << "\n";
	p->setTimerState(p->getTimerState() + time);

	

	if (p->getVelocityY() > 1.0f || p->getIsOnGround()/* || p->m_timerState > 20.0f*/) {
		if (p->getIsInWaterJump()) {
			p->setIsInWaterJump(false);
			p->setState(new cPlayerGrassState);
			return;
		}
	}

	if (p->getVelocityY() >= p->getFallVelocity()) {
		p->setVelocityY(p->getFallVelocity());
	}
	else {
		p->setVelocityY(p->getVelocityY() + p->getFallAcc());
	}

	// Move left
	if (p->getIsPressingLeft() && !p->getIsDead() && !p->getIsDownThrusting() && !p->getIsLockedMove()) {
		if (p->getVelocityX() > -p->getMoveVelocity()) {
			p->setVelocityX(p->getVelocityX() - p->getStartMoveAcc() * 0.4f);
		}
		else if (p->getVelocityX() < -p->getMoveVelocity()) {
			p->setVelocityX(-p->getMoveVelocity());
		}
	}

	// Move right
	if (p->getIsPressingRight() && !p->getIsDead() && !p->getIsDownThrusting() && !p->getIsLockedMove()) {
		if (p->getVelocityX() < p->getMoveVelocity()) {
			p->setVelocityX(p->getVelocityX() + p->getStartMoveAcc() * 0.4f);
		} else if (p->getVelocityX() > p->getMoveVelocity()) {
			p->setVelocityX(p->getMoveVelocity());
		}
	}

	//bool moved = false;
	bool movingUp = false;
	bool movingDown = false;
	bool movingLeft = false;
	bool movingRight = false;

	if (p->getVelocityY() > 0.0f) {
		movingUp = false;
		movingDown = true;
	}
	if (p->getVelocityY() < 0.0f) {
		movingUp = true;
		movingDown = false;
	}

	if (p->getVelocityX() < 0.0f) {
		p->setIsFacingLeft(true);
		movingLeft = true;
		movingRight = false;
	}
	if (p->getVelocityX() > 0.0f) {
		p->setIsFacingLeft(false);
		movingLeft = false;
		movingRight = true;
	}
	if (p->getVelocityX() < 0.0f && p->getVelocityX() > 0.0f) {
		movingLeft = false;
		movingRight = false;
	}

	
	float radians = atan2(p->getVelocityY(), p->getVelocityX());

	if (radians < 0.0f) {
		radians += 3.14159265f * 2;
	}

	float degrees = radians * 180 / 3.14159265f;
	float stepDegrees = 22.5f;
	std::cout << radians << " " << degrees << "\n";

	// Straight down
	if (degrees > 78.75f && degrees < 101.25f) {
		p->setTileOffsetY(576.0f);
	} else if (degrees > 101.25f && degrees < 123.75f) {
		p->setIsFacingLeft(true);
		p->setTileOffsetY(512.0f);
	} else if (degrees > 123.75f && degrees < 146.25f) {
		p->setIsFacingLeft(true);
		p->setTileOffsetY(448.0f);
	} else if (degrees > 146.25f && degrees < 168.75f) {
		p->setIsFacingLeft(true);
		p->setTileOffsetY(384.0f);
	}
	// Straight left
	else if (degrees > 168.75f && degrees < 191.25f) {
		p->setIsFacingLeft(true);
		p->setTileOffsetY(64.0f);
	} else if (degrees > 191.25f && degrees < 213.75f) {
		p->setIsFacingLeft(true);
		p->setTileOffsetY(128.0f);
	} else if (degrees > 213.75f && degrees < 236.25f) {
		p->setIsFacingLeft(true);
		p->setTileOffsetY(192.0f);
	} else if (degrees > 236.25f && degrees < 258.75f) {
		p->setIsFacingLeft(true);
		p->setTileOffsetY(256.0f);
	}
	// Straight up
	else if (degrees > 258.75f && degrees < 281.25f) {
		p->setTileOffsetY(320.0f);
	} else if (degrees > 281.25f && degrees < 303.75f) {
		p->setTileOffsetY(256.0f);
	} else if (degrees > 303.75f && degrees < 326.25f) {
		p->setTileOffsetY(192.0f);
	} else if (degrees > 326.25f && degrees < 348.75f) {
		p->setTileOffsetY(128.0f);
	}
	// Straight right
	else if (degrees > 348.75f && degrees < 11.25f) {
		p->setIsFacingLeft(false);
		p->setTileOffsetY(64.0f);
	} else if (degrees > 11.25f && degrees < 33.75f) {
		p->setIsFacingLeft(false);
		p->setTileOffsetY(384.0f);
	} else if (degrees > 33.75f && degrees < 56.25f) {
		p->setIsFacingLeft(false);
		p->setTileOffsetY(448.0f);
	} else if (degrees > 56.25f && degrees < 78.75f) {
		p->setIsFacingLeft(false);
		p->setTileOffsetY(512.0f);
	}
}