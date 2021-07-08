#pragma once

#include "Object.h"
#include <list>

class cInputManager {
public:
	static void attachListener(cObject *object);
	static void detachListener(cObject *object);

	static void joyButtonDown(int buttonDown);
	static void joyButtonUp(int buttonUp);

	static void keyDown(int keyDown);
	static void keyUp(int keyUp);

	static void mouseButtonDown(int mouseButtonDown);
	static void mouseButtonUp(int mouseButtonUp);

	static void setMouseX(int mouseX) { m_mouseX = mouseX; };
	static void setMouseY(int mouseY) { m_mouseY = mouseY; };
	static void setHasMouseMoved(bool hasMouseMoved) { m_hasMouseMoved = hasMouseMoved; };
		
	static sf::Mouse::Button getMeleeMouseButton() { return m_meleeMouseButton; };
	static sf::Mouse::Button getJumpMouseButton() { return m_jumpMouseButton; };
	static sf::Mouse::Button getThrowMouseButton() { return m_throwMouseButton; };
	static sf::Mouse::Button getShootMouseButton() { return m_shootMouseButton; };
	
	static void loadConfig(char* fileName);

	static bool getHasMouseMoved() { return m_hasMouseMoved; };
	static int getMouseX() { return m_mouseX; };
	static int getMouseY() { return m_mouseY; };

	static sf::Keyboard::Key getUpKey() { return m_upKey; };
	static sf::Keyboard::Key getDownKey() { return m_downKey; };
	static sf::Keyboard::Key getLeftKey() { return m_leftKey; };
	static sf::Keyboard::Key getRightKey() { return m_rightKey; };

	static sf::Keyboard::Key getSprintKey() { return m_sprintKey; };
	static sf::Keyboard::Key getJumpKey() { return m_jumpKey; };
	static sf::Keyboard::Key getMeleeKey() { return m_meleeKey; };
	static sf::Keyboard::Key getThrowKey() { return m_throwKey; };
	static sf::Keyboard::Key getShootKey() { return m_shootKey; };

	//const sf::Keyboard::Key getKey(unsigned char key) { return sf::Keyboard[key]; };

	static unsigned short getMeleeJoyButton() { return m_meleeJoyButton; };
	static unsigned short getJumpJoyButton() { return m_jumpJoyButton; };
	static unsigned short getSprintJoyButton() { return m_sprintJoyButton; };
	static unsigned short getShootJoyButton() { return m_shootJoyButton; };

	static void joyMovedX(float joyMovedX);
	static void joyMovedY(float joyMovedY);
	static float getJoyDeadzone() { return m_joyDeadzone; };
	static void setJoyDeadzone(float joyDeadzone) { m_joyDeadzone = joyDeadzone; };
private:
	//cInputManager();
	static std::list<cObject*> m_listeners;
	
	//sf::Keyboard::Key m_keys[323];

	static sf::Keyboard::Key m_upKey;
	static sf::Keyboard::Key m_downKey;
	static sf::Keyboard::Key m_leftKey;
	static sf::Keyboard::Key m_rightKey;

	static sf::Keyboard::Key m_sprintKey;
	static sf::Keyboard::Key m_jumpKey;
	static sf::Keyboard::Key m_meleeKey;
	static sf::Keyboard::Key m_throwKey;
	static sf::Keyboard::Key m_shootKey;
	
	static sf::Mouse::Button m_meleeMouseButton;
	static sf::Mouse::Button m_jumpMouseButton;
	static sf::Mouse::Button m_throwMouseButton;
	static sf::Mouse::Button m_shootMouseButton;

	static bool m_hasMouseMoved;
	static int m_mouseX, m_mouseY;

	static float m_joyMovedX, m_joyMovedY;
	static float m_joyDeadzone;
	static unsigned short m_meleeJoyButton;
	static unsigned short m_jumpJoyButton;
	static unsigned short m_sprintJoyButton;
	static unsigned short m_shootJoyButton;
};
