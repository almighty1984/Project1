#include "resource.h"
#include "App.h"
#include "RenderingManager.h"
#include "SoundsManager.h"
#include "InputManager.h"
#include <Windows.h>

#include "GameState.h"
#include <chrono>
void cApp::run(cApp* app) {
	cRenderingManager::createWindow(m_windowWidth, m_windowHeight, 32, "Roten", m_windowMultiplier, m_isFullscreen, m_isWidescreen);
	//cRenderingManager::setView(0, 0, m_windowWidth, m_windowHeight);
	cRenderingManager::setFramerateLimit(m_frameRate);
	cRenderingManager::setUseVerticalSync(m_useVerticalSync);

	//std::cout << "m_useVerticalSync = " << m_useVerticalSync << "\n";
	m_isRunning = true;

	std::cout << "Starting game loop\n";

	sf::Clock clock;
	float prevTime = 0.0f;
	float newTime = 0.0f;
	float deltaTime = 0.0f;

	float fpsCurrent = 0.0f;

	newTime = clock.restart().asSeconds();
	float frameCount = 0.0f;

	while (m_isRunning) {
		sf::Event sfEvent;
		//HCURSOR hcursor;
		while (cRenderingManager::m_window.getEvent(sfEvent)) {
			HINSTANCE hInstance = GetModuleHandle(0);
			HCURSOR hcursor = LoadCursor(hInstance, MAKEINTRESOURCE(IDI_CURSOR1));
			//hcursor = LoadCursorFromFileA("Data\\Cursors\\Crosshairs 2 red.cur");			
			//hcursor = LoadCursor(NULL, ID_MOVING_VIEW);
			SetCursor(hcursor);
			/*if (sf::Joystick::isConnected(0)) {
				std::cout << "Joystick 0 is connected\n";
			}*/
			if (sfEvent.type == sf::Event::Closed) {
				cRenderingManager::closeWindow();
				shutdown();
			}
			if (sfEvent.type == sf::Event::MouseLeft) {
				std::cout << "mouse gone" << "\n";
				app->setIsLocked(true);
			} else if (sfEvent.type == sf::Event::MouseEntered) {
				std::cout << "mouse found" << "\n";
				app->setIsLocked(false);
			}
			// Mouse moved
			if ((sfEvent.type == sf::Event::MouseMoved)) {
				//std::cout << sfEvent.mouseMove.x << " " << sfEvent.mouseMove.y << "\n";
				m_state->setHasMouseMoved(true);
				m_state->setMouseY((int)(sfEvent.mouseMove.y / m_windowMultiplier));
				cInputManager::setHasMouseMoved(true);
				cInputManager::setMouseY((int)(sfEvent.mouseMove.y / m_windowMultiplier));

				m_state->setMouseX((int)(sfEvent.mouseMove.x / m_windowMultiplier));
				cInputManager::setMouseX((int)(sfEvent.mouseMove.x / m_windowMultiplier));
			} else {
				m_state->setHasMouseMoved(false);
				cInputManager::setHasMouseMoved(false);
			}
			if ((sfEvent.type == sf::Event::MouseButtonPressed)) {
				if (sfEvent.key.code == cInputManager::getMeleeMouseButton()) {
					cInputManager::mouseButtonDown(cInputManager::getMeleeMouseButton());
					m_state->mouseButtonDown(this, cInputManager::getMeleeMouseButton());
				}
				if (sfEvent.key.code == cInputManager::getJumpMouseButton()) {
					cInputManager::mouseButtonDown(cInputManager::getJumpMouseButton());
					m_state->mouseButtonDown(this, cInputManager::getJumpMouseButton());
				}
				if (sfEvent.key.code == cInputManager::getThrowMouseButton()) {
					cInputManager::mouseButtonDown(cInputManager::getThrowMouseButton());
					m_state->mouseButtonDown(this, cInputManager::getThrowMouseButton());
				}
				if (sfEvent.key.code == cInputManager::getShootMouseButton()) {
					cInputManager::mouseButtonDown(cInputManager::getShootMouseButton());
					m_state->mouseButtonDown(this, cInputManager::getShootMouseButton());
				}
			} else if ((sfEvent.type == sf::Event::MouseButtonReleased)) {
				if (sfEvent.key.code == cInputManager::getMeleeMouseButton()) {
					cInputManager::mouseButtonUp(cInputManager::getMeleeMouseButton());
					m_state->mouseButtonUp(this, cInputManager::getMeleeMouseButton());
				}
				if (sfEvent.key.code == cInputManager::getJumpMouseButton()) {
					cInputManager::mouseButtonUp(cInputManager::getJumpMouseButton());
					m_state->mouseButtonUp(this, cInputManager::getJumpMouseButton());
				}
				if (sfEvent.key.code == cInputManager::getThrowMouseButton()) {
					cInputManager::mouseButtonUp(cInputManager::getThrowMouseButton());
					m_state->mouseButtonUp(this, cInputManager::getThrowMouseButton());
				}
				if (sfEvent.key.code == cInputManager::getShootMouseButton()) {
					cInputManager::mouseButtonUp(cInputManager::getShootMouseButton());
					m_state->mouseButtonUp(this, cInputManager::getShootMouseButton());
				}
			}
			if ((sfEvent.type == sf::Event::KeyPressed)) {
				if (m_useEventInput) {
					if (sfEvent.key.code == cInputManager::getUpKey()) {
						cInputManager::keyDown(cInputManager::getUpKey());
						m_state->keyDown(this, cInputManager::getUpKey());
					}
					if (sfEvent.key.code == cInputManager::getDownKey()) {
						cInputManager::keyDown(cInputManager::getDownKey());
						m_state->keyDown(this, cInputManager::getDownKey());
					}
					if (sfEvent.key.code == cInputManager::getLeftKey()) {
						cInputManager::keyDown(cInputManager::getLeftKey());
						m_state->keyDown(this, cInputManager::getLeftKey());
					}
					if (sfEvent.key.code == cInputManager::getRightKey()) {
						cInputManager::keyDown(cInputManager::getRightKey());
						m_state->keyDown(this, cInputManager::getRightKey());
					}
					if ((sfEvent.key.code == cInputManager::getSprintKey())) {
						cInputManager::keyDown(cInputManager::getSprintKey());
						m_state->keyDown(this, cInputManager::getSprintKey());
					}
				}
				if (sfEvent.key.code == sf::Keyboard::BackSpace) {
					cInputManager::keyDown(sf::Keyboard::BackSpace);
					m_state->keyDown(this, sf::Keyboard::BackSpace);
				}
				if (sfEvent.key.code == sf::Keyboard::Return) {
					cInputManager::keyDown(sf::Keyboard::Return);
					m_state->keyDown(this, sf::Keyboard::Return);
				}
				if (sfEvent.key.code == sf::Keyboard::Escape) {
					cInputManager::keyDown(sf::Keyboard::Escape);
					m_state->keyDown(this, sf::Keyboard::Escape);
				}
				if (sfEvent.key.code == sf::Keyboard::LShift) {
					cInputManager::keyDown(sf::Keyboard::LShift);
					m_state->keyDown(this, sf::Keyboard::LShift);
				}
				// Go through alphabet
				for (int i = 0; i < 26; ++i) {
					if (sfEvent.key.code == i) {
						cInputManager::keyDown(i);
						m_state->keyDown(this, i);
					}
				}
				if ((sfEvent.key.code == cInputManager::getJumpKey())) {
					cInputManager::keyDown(cInputManager::getJumpKey());
					m_state->keyDown(this, cInputManager::getJumpKey());
				}
				if ((sfEvent.key.code == cInputManager::getMeleeKey())) {
					cInputManager::keyDown(cInputManager::getMeleeKey());
					m_state->keyDown(this, cInputManager::getMeleeKey());
				}
				if ((sfEvent.key.code == cInputManager::getThrowKey())) {
					cInputManager::keyDown(cInputManager::getThrowKey());
					m_state->keyDown(this, cInputManager::getThrowKey());
				}
				if ((sfEvent.key.code == cInputManager::getShootKey())) {
					cInputManager::keyDown(cInputManager::getShootKey());
					m_state->keyDown(this, cInputManager::getShootKey());
				}
			} else if ((sfEvent.type == sf::Event::KeyReleased)) {
				if (m_useEventInput) {
					if (sfEvent.key.code == cInputManager::getUpKey()) {
						cInputManager::keyUp(cInputManager::getUpKey());
						m_state->keyUp(this, cInputManager::getUpKey());
					}
					if (sfEvent.key.code == cInputManager::getDownKey()) {
						cInputManager::keyUp(cInputManager::getDownKey());
						m_state->keyUp(this, cInputManager::getDownKey());
					}
					if (sfEvent.key.code == cInputManager::getLeftKey()) {
						cInputManager::keyUp(cInputManager::getLeftKey());
						m_state->keyUp(this, cInputManager::getLeftKey());
					}
					if (sfEvent.key.code == cInputManager::getRightKey()) {
						cInputManager::keyUp(cInputManager::getRightKey());
						m_state->keyUp(this, cInputManager::getRightKey());
					}
					if (sfEvent.key.code == cInputManager::getSprintKey()) {
						cInputManager::keyUp(cInputManager::getSprintKey());
						m_state->keyUp(this, cInputManager::getSprintKey());
					}
				}
				if (sfEvent.key.code == cInputManager::getJumpKey()) {
					cInputManager::keyUp(cInputManager::getJumpKey());
					m_state->keyUp(this, cInputManager::getJumpKey());
				}
				if ((sfEvent.key.code == cInputManager::getMeleeKey())) {
					cInputManager::keyUp(cInputManager::getMeleeKey());
					m_state->keyUp(this, cInputManager::getMeleeKey());
				}
				if (sfEvent.key.code == cInputManager::getThrowKey()) {
					cInputManager::keyUp(cInputManager::getThrowKey());
					m_state->keyUp(this, cInputManager::getThrowKey());
				}
				if (sfEvent.key.code == cInputManager::getShootKey()) {
					cInputManager::keyUp(cInputManager::getShootKey());
					m_state->keyUp(this, cInputManager::getShootKey());
				}
				if (sfEvent.key.code == sf::Keyboard::BackSpace) {
					cInputManager::keyUp(sf::Keyboard::BackSpace);
					m_state->keyUp(this, sf::Keyboard::BackSpace);
				}
				if (sfEvent.key.code == sf::Keyboard::Return) {
					cInputManager::keyUp(sf::Keyboard::Return);
					m_state->keyUp(this, sf::Keyboard::Return);
				}
				if (sfEvent.key.code == sf::Keyboard::Escape) {
					cInputManager::keyUp(sf::Keyboard::Escape);
					m_state->keyUp(this, sf::Keyboard::Escape);
				}
				if (sfEvent.key.code == sf::Keyboard::LShift) {
					cInputManager::keyUp(sf::Keyboard::LShift);
					m_state->keyUp(this, sf::Keyboard::LShift);
				}
				// Go through alphabet
				for (int i = 0; i < 26; ++i) {
					if (sfEvent.key.code == i) {
						cInputManager::keyUp(i);
						m_state->keyUp(this, i);
					}
				}
			}
			if ((sfEvent.type == sf::Event::JoystickButtonPressed)) {
				std::cout << "cApp::run sfEvent.joystickButton.button " << sfEvent.joystickButton.button << "\n";
				cInputManager::joyButtonDown(sfEvent.joystickButton.button);
				m_state->joystickButtonDown(this, sfEvent.joystickButton.button);
			} else if ((sfEvent.type == sf::Event::JoystickButtonReleased)) {
				cInputManager::joyButtonUp(sfEvent.joystickButton.button);
				m_state->joystickButtonUp(this, sfEvent.joystickButton.button);
			}
			if (sfEvent.type == sf::Event::JoystickMoved) {
				//std::cout << sf::Joystick::getAxisPosition(0, sf::Joystick::X) << "\n";

				cInputManager::joyMovedX(sf::Joystick::getAxisPosition(0, sf::Joystick::X));
				m_state->joyMovedX(sf::Joystick::getAxisPosition(0, sf::Joystick::X));

				cInputManager::joyMovedY(sf::Joystick::getAxisPosition(0, sf::Joystick::Y));
				m_state->joyMovedY(sf::Joystick::getAxisPosition(0, sf::Joystick::Y));

				/*cInputManager::joystickMovedX(sf::Joystick::getAxisPosition(0, sf::Joystick::PovX ));
				m_state->joystickMovedX(sf::Joystick::getAxisPosition(0, sf::Joystick::PovX ));*/
			}
		}
		if (!m_useEventInput) {
			if ((sf::Keyboard::isKeyPressed(cInputManager::getLeftKey()))) {
				cInputManager::keyDown(cInputManager::getLeftKey());
				m_state->keyDown(this, cInputManager::getLeftKey());
			} else {
				cInputManager::keyUp(cInputManager::getLeftKey());
				m_state->keyUp(this, cInputManager::getLeftKey());
			}
			if ((sf::Keyboard::isKeyPressed(cInputManager::getRightKey()))) {
				cInputManager::keyDown(cInputManager::getRightKey());
				m_state->keyDown(this, cInputManager::getRightKey());
			} else {
				cInputManager::keyUp(cInputManager::getRightKey());
				m_state->keyUp(this, cInputManager::getRightKey());
			}
			if ((sf::Keyboard::isKeyPressed(cInputManager::getSprintKey()))) {
				cInputManager::keyDown(cInputManager::getSprintKey());
				m_state->keyDown(this, cInputManager::getSprintKey());
			} else {
				cInputManager::keyUp(cInputManager::getSprintKey());
				m_state->keyUp(this, cInputManager::getSprintKey());
			}

			if ((sf::Keyboard::isKeyPressed(cInputManager::getUpKey()))) {
				cInputManager::keyDown(cInputManager::getUpKey());
				m_state->keyDown(this, cInputManager::getUpKey());
			} else {
				cInputManager::keyUp(cInputManager::getUpKey());
				m_state->keyUp(this, cInputManager::getUpKey());
			}

			if ((sf::Keyboard::isKeyPressed(cInputManager::getDownKey()))) {
				cInputManager::keyDown(cInputManager::getDownKey());
				m_state->keyDown(this, cInputManager::getDownKey());
			} else {
				cInputManager::keyUp(cInputManager::getDownKey());
				m_state->keyUp(this, cInputManager::getDownKey());
			}
		}

		prevTime = newTime;
		newTime = clock.getElapsedTime().asSeconds();
		deltaTime = (newTime - prevTime);

		frameCount += deltaTime;

		/*if (m_isGameLocked) {
			frameCount = 0.0f;
		}*/

		fpsCurrent = 1.0f / deltaTime;
		app->setFpsCurrent((int)fpsCurrent);
		//std::cout << fps << "\n";			

		if (m_isUpdatedEveryFrame) {
			frameCount = 0.0f;
			app->update(1.0f);
		} else {
			if (frameCount > 0.016f) {
				frameCount -= 0.016f;
				app->update(1.0f);
			}
		}
		cRenderingManager::clear();

		app->render();
		cRenderingManager::display();
	}
}