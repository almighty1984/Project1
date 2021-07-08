#include "PlayerShopState.h"
#include "PlayerGrassState.h"
#include "SavesManager.h"
#include "SoundsManager.h"
#include "InputManager.h"

cPlayerShopState::cPlayerShopState() : m_levelPtr(nullptr), m_shopItemCurrent(0) {
	m_secondCall = false;
}

cPlayerShopState::~cPlayerShopState() {
	m_levelPtr = nullptr;
}

void cPlayerShopState::update(cApp *app, cPlayer *p, float time) {
	//std::cout << "ShopState::update" << "\n";
	if (p == nullptr || p->getAttachedLevel() == nullptr) {
		return;
	}
	p->setIsIdle(true);
	if (!m_secondCall) {
		m_secondCall = true;
		std::cout << "Entered cPlayerShopState" << "\n";
		app->setUseEventInput(true);		
		p->setIsInWater(false);
		p->setVelocityX(0.0f);
		p->setAnim(eAnimTag::idle);
		p->setIsPressingUp(false);
		p->setIsLockedOpen(true);
		m_levelPtr = p->getAttachedLevel();
		m_levelPtr->setDoShowShopBox(0, true);
	}
		
	if (p->getIsKeyHeld(sf::Keyboard::Return) || p->getIsPressingJump()) {
		p->setIsPressingJump(false);
		cSoundsManager::stop(eSoundTag::chestOpen);
		cSoundsManager::play(eSoundTag::chestOpen);

		if (p->getShopItemNumber() == 0) {
			std::cout << p->getVitality() << " ";
			p->setVitality(p->getVitality() + 0.1f);
			cSavesManager::setPlayerVitality(p->getVitality());
			std::cout << p->getVitality() << "\n";
			m_strStream.clear();
			m_strStream.str("");
			m_strStream << p->getVitality();
			//m_fontVitality.setText(m_strStream.str().c_str());
		} else if (p->getShopItemNumber() == 1) {
			std::cout << p->getStamina() << " ";
			p->setStamina(p->getStamina() + 0.1f);
			cSavesManager::setPlayerStamina(p->getStamina());
			std::cout << p->getStamina() << "\n";
			m_strStream.clear();
			m_strStream.str("");
			m_strStream << p->getStamina();
			//m_fontStamina.setText(m_strStream.str().c_str());
		}
	}
	
	p->setVelocityX(0.0f);

	//std::cout << p->getTimeBeingIdle() << "\n";

	if (!p->getIsPressingLeft() && !p->getIsPressingRight() && p->getTimeBeingIdle() > 10.0f) {
		p->setIsLockedMove(false);
	}

	if (p->getIsPressingLeft() && !p->getIsLockedMove() && m_shopItemCurrent > 0) {
		p->setIsLockedMove(true);
		p->setIsPressingLeft(false);
		p->setIsIdle(false);
		cSoundsManager::stop(eSoundTag::hitHead);
		cSoundsManager::play(eSoundTag::hitHead);
		
		--m_shopItemCurrent;
	}
	if (p->getIsPressingRight() && !p->getIsLockedMove() && m_shopItemCurrent < 2) {
		p->setIsLockedMove(true);
		p->setIsPressingRight(false);
		p->setIsIdle(false);
		cSoundsManager::stop(eSoundTag::hitHead);
		cSoundsManager::play(eSoundTag::hitHead);
		
		++m_shopItemCurrent;
	}

	for (unsigned char i = 0; i < 3; ++i) {
		m_levelPtr->setDoShowShopBox(i, false);
	}
	m_levelPtr->setDoShowShopBox(m_shopItemCurrent, true);

	if (p->getIsPressingUp() && !p->getIsLockedOpen()) {
		p->setIsLockedOpen(true);
		std::cout << "PlayerShopState pressed UP" << "\n";
		p->setIsInShop(false);
		cSoundsManager::stop(eSoundTag::hitHead);
		cSoundsManager::play(eSoundTag::hitHead);

		for (unsigned char i = 0; i < 3; ++i) {
			m_levelPtr->setDoShowShopBox(i, false);
		}

		p->setState(new cPlayerGrassState);
		return;
	}
}