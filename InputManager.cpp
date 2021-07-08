#include "InputManager.h"
#include <iostream>
#include <sstream>

float cInputManager::m_joyDeadzone = 0.0f;
float cInputManager::m_joyMovedX = 0.0f;
float cInputManager::m_joyMovedY = 0.0f;
unsigned short cInputManager::m_jumpJoyButton	= 0;
unsigned short cInputManager::m_meleeJoyButton	= 1;
unsigned short cInputManager::m_sprintJoyButton	= 2;
unsigned short cInputManager::m_shootJoyButton		= 3;

sf::Keyboard::Key cInputManager::m_upKey		= sf::Keyboard::Up;
sf::Keyboard::Key cInputManager::m_leftKey		= sf::Keyboard::Left;
sf::Keyboard::Key cInputManager::m_downKey		= sf::Keyboard::Down;
sf::Keyboard::Key cInputManager::m_rightKey		= sf::Keyboard::Right;
sf::Keyboard::Key cInputManager::m_sprintKey	= sf::Keyboard::Z;
sf::Keyboard::Key cInputManager::m_jumpKey		= sf::Keyboard::X;
sf::Keyboard::Key cInputManager::m_meleeKey	= sf::Keyboard::C;
sf::Keyboard::Key cInputManager::m_throwKey		= sf::Keyboard::V;
sf::Keyboard::Key cInputManager::m_shootKey		= sf::Keyboard::F;

int cInputManager::m_mouseX = 0;
int cInputManager::m_mouseY = 0;
bool cInputManager::m_hasMouseMoved = false;
sf::Mouse::Button cInputManager::m_meleeMouseButton	= sf::Mouse::Left;
sf::Mouse::Button cInputManager::m_jumpMouseButton		= sf::Mouse::Right;
sf::Mouse::Button cInputManager::m_throwMouseButton		= sf::Mouse::XButton1;
sf::Mouse::Button cInputManager::m_shootMouseButton		= sf::Mouse::XButton2;

std::list<cObject*> cInputManager::m_listeners;

void cInputManager::loadConfig(char* fileName) {
	std::ifstream dataFile( fileName );

	  // Verify the data file was opened; exit if not.
	if ( !dataFile ) {
		std::cout << "Error:  Cannot open file " << fileName << "\n";
		//exit( 1 );
	} 

	std::istringstream iStr(std::ios_base::out);
	char buf[ 80 ] = {0};
	std::string firstField;
	std::string secondField;
	std::string data;
	std::string data2;

	while (!dataFile.eof() ) {	
		dataFile.getline( buf, sizeof( buf ) );

		iStr.str(std::string(buf));
		iStr >> firstField;
		iStr.clear();
		iStr.str("");
		
		if (firstField == "Input") {
			std::cout << "Input\n{\n";
			while (dataFile.peek() != '}' ) {
				dataFile.getline( buf, sizeof( buf ) );

				iStr.str(std::string(buf));
				iStr >> firstField >> secondField >> data;
				iStr.clear();
				iStr.str("");

				if (firstField == "up" || data == "Up" || data == "UP") {
					if (data == "A" || data == "a")
						m_upKey = sf::Keyboard::A;
					else if (data == "B" || data == "b")
						m_upKey = sf::Keyboard::B;
					else if (data == "C" || data == "c")
						m_upKey = sf::Keyboard::C;
					else if (data == "D" || data == "d")
						m_upKey = sf::Keyboard::D;
					else if (data == "E" || data == "e")
						m_upKey = sf::Keyboard::E;
					else if (data == "F" || data == "f")
						m_upKey = sf::Keyboard::F;
					else if (data == "G" || data == "g")
						m_upKey = sf::Keyboard::G;
					else if (data == "H" || data == "h")
						m_upKey = sf::Keyboard::H;
					else if (data == "I" || data == "i")
						m_upKey = sf::Keyboard::I;
					else if (data == "J" || data == "j")
						m_upKey = sf::Keyboard::J;
					else if (data == "K" || data == "k")
						m_upKey = sf::Keyboard::K;
					else if (data == "L" || data == "l")
						m_upKey = sf::Keyboard::L;
					else if (data == "M" || data == "m")
						m_upKey = sf::Keyboard::M;
					else if (data == "N" || data == "n")
						m_upKey = sf::Keyboard::N;
					else if (data == "O" || data == "o")
						m_upKey = sf::Keyboard::O;
					else if (data == "P" || data == "p")
						m_upKey = sf::Keyboard::P;
					else if (data == "Q" || data == "q")
						m_upKey = sf::Keyboard::Q;
					else if (data == "R" || data == "r")
						m_upKey = sf::Keyboard::R;
					else if (data == "S" || data == "s")
						m_upKey = sf::Keyboard::S;
					else if (data == "T" || data == "t")
						m_upKey = sf::Keyboard::T;
					else if (data == "U" || data == "u")
						m_upKey = sf::Keyboard::U;
					else if (data == "V" || data == "v")
						m_upKey = sf::Keyboard::V;
					else if (data == "W" || data == "w")
						m_upKey = sf::Keyboard::W;
					else if (data == "X" || data == "x")
						m_upKey = sf::Keyboard::X;
					else if (data == "Y" || data == "y")
						m_upKey = sf::Keyboard::Y;
					else if (data == "Z" || data == "z")
						m_upKey = sf::Keyboard::Z;
					else if (data == "up" || data == "Up" || data == "UP")
						m_upKey = sf::Keyboard::Up;
					else if (data == "left" || data == "Left" || data == "LEFT")
						m_upKey = sf::Keyboard::Left;
					else if (data == "down" || data == "Down" || data == "DOWN")
						m_upKey = sf::Keyboard::Down;
					else if (data == "right" || data == "Right" || data == "RIGHT")
						m_upKey = sf::Keyboard::Right;
					else if (data == "space" || data == "Space" || data == "SPACE")
						m_upKey = sf::Keyboard::Space;
					else if (data == "lshift" || data == "LShift" || data == "LSHIFT")
						m_upKey = sf::Keyboard::LShift;
					else if (data == "lcontrol" || data == "LControl" || data == "LCONTROL")
						m_upKey = sf::Keyboard::LControl;
				}
				else if (firstField == "left" || data == "Left" || data == "LEFT") {
					if (data == "A" || data == "a")
						m_leftKey = sf::Keyboard::A;
					else if (data == "B" || data == "b")
						m_leftKey = sf::Keyboard::B;
					else if (data == "C" || data == "c")
						m_leftKey = sf::Keyboard::C;
					else if (data == "D" || data == "d")
						m_leftKey = sf::Keyboard::D;
					else if (data == "E" || data == "e")
						m_leftKey = sf::Keyboard::E;
					else if (data == "F" || data == "f")
						m_leftKey = sf::Keyboard::F;
					else if (data == "G" || data == "g")
						m_leftKey = sf::Keyboard::G;
					else if (data == "H" || data == "g")
						m_leftKey = sf::Keyboard::H;
					else if (data == "I" || data == "i")
						m_leftKey = sf::Keyboard::I;
					else if (data == "J" || data == "j")
						m_leftKey = sf::Keyboard::J;
					else if (data == "K" || data == "k")
						m_leftKey = sf::Keyboard::K;
					else if (data == "L" || data == "l")
						m_leftKey = sf::Keyboard::L;
					else if (data == "M" || data == "m")
						m_leftKey = sf::Keyboard::M;
					else if (data == "N" || data == "n")
						m_leftKey = sf::Keyboard::N;
					else if (data == "O" || data == "o")
						m_leftKey = sf::Keyboard::O;
					else if (data == "P" || data == "p")
						m_leftKey = sf::Keyboard::P;
					else if (data == "Q" || data == "q")
						m_leftKey = sf::Keyboard::Q;
					else if (data == "R" || data == "r")
						m_leftKey = sf::Keyboard::R;
					else if (data == "S" || data == "s")
						m_leftKey = sf::Keyboard::S;
					else if (data == "T" || data == "t")
						m_leftKey = sf::Keyboard::T;
					else if (data == "U" || data == "u")
						m_leftKey = sf::Keyboard::U;
					else if (data == "V" || data == "v")
						m_leftKey = sf::Keyboard::V;
					else if (data == "W" || data == "w")
						m_leftKey = sf::Keyboard::W;
					else if (data == "X" || data == "x")
						m_leftKey = sf::Keyboard::X;
					else if (data == "Y" || data == "y")
						m_leftKey = sf::Keyboard::Y;
					else if (data == "Z" || data == "z")
						m_leftKey = sf::Keyboard::Z;
					else if (data == "up" || data == "Up" || data == "UP")
						m_leftKey = sf::Keyboard::Up;
					else if (data == "left" || data == "Left" || data == "LEFT")
						m_leftKey = sf::Keyboard::Left;
					else if (data == "down" || data == "Down" || data == "DOWN")
						m_leftKey = sf::Keyboard::Down;
					else if (data == "right" || data == "Right" || data == "RIGHT")
						m_leftKey = sf::Keyboard::Right;
					else if (data == "space" || data == "Space" || data == "SPACE")
						m_leftKey = sf::Keyboard::Space;
					else if (data == "lshift" || data == "LShift" || data == "LSHIFT")
						m_leftKey = sf::Keyboard::LShift;
					else if (data == "lcontrol" || data == "LControl" || data == "LCONTROL")
						m_leftKey = sf::Keyboard::LControl;
				}
				else if (firstField == "down" || data == "Down" || data == "DOWN") {
					if (data == "A" || data == "a")
						m_downKey = sf::Keyboard::A;
					else if (data == "B" || data == "b")
						m_downKey = sf::Keyboard::B;
					else if (data == "C" || data == "c")
						m_downKey = sf::Keyboard::C;
					else if (data == "D" || data == "d")
						m_downKey = sf::Keyboard::D;
					else if (data == "E" || data == "e")
						m_downKey = sf::Keyboard::E;
					else if (data == "F" || data == "f")
						m_downKey = sf::Keyboard::F;
					else if (data == "G" || data == "g")
						m_downKey = sf::Keyboard::G;
					else if (data == "H" || data == "h")
						m_downKey = sf::Keyboard::H;
					else if (data == "I" || data == "i")
						m_downKey = sf::Keyboard::I;
					else if (data == "J" || data == "j")
						m_downKey = sf::Keyboard::J;
					else if (data == "K" || data == "k")
						m_downKey = sf::Keyboard::K;
					else if (data == "L" || data == "l")
						m_downKey = sf::Keyboard::L;
					else if (data == "M" || data == "m")
						m_downKey = sf::Keyboard::M;
					else if (data == "N" || data == "n")
						m_downKey = sf::Keyboard::N;
					else if (data == "O" || data == "o")
						m_downKey = sf::Keyboard::O;
					else if (data == "P" || data == "p")
						m_downKey = sf::Keyboard::P;
					else if (data == "Q" || data == "q")
						m_downKey = sf::Keyboard::Q;
					else if (data == "R" || data == "r")
						m_downKey = sf::Keyboard::R;
					else if (data == "S" || data == "s")
						m_downKey = sf::Keyboard::S;
					else if (data == "T" || data == "t")
						m_downKey = sf::Keyboard::T;
					else if (data == "U" || data == "u")
						m_downKey = sf::Keyboard::U;
					else if (data == "V" || data == "v")
						m_downKey = sf::Keyboard::V;
					else if (data == "W" || data == "w")
						m_downKey = sf::Keyboard::W;
					else if (data == "X" || data == "x")
						m_downKey = sf::Keyboard::X;
					else if (data == "Y" || data == "y")
						m_downKey = sf::Keyboard::Y;
					else if (data == "Z" || data == "z")
						m_downKey = sf::Keyboard::Z;
					else if (data == "up" || data == "Up" || data == "UP")
						m_downKey = sf::Keyboard::Up;
					else if (data == "left" || data == "Left" || data == "LEFT")
						m_downKey = sf::Keyboard::Left;
					else if (data == "down" || data == "Down" || data == "DOWN")
						m_downKey = sf::Keyboard::Down;
					else if (data == "right" || data == "Right" || data == "RIGHT")
						m_downKey = sf::Keyboard::Right;
					else if (data == "space" || data == "Space" || data == "SPACE")
						m_downKey = sf::Keyboard::Space;
					else if (data == "lshift" || data == "LShift" || data == "LSHIFT")
						m_downKey = sf::Keyboard::LShift;
					else if (data == "lcontrol" || data == "LControl" || data == "LCONTROL")
						m_downKey = sf::Keyboard::LControl;
				}
				else if (firstField == "right" || data == "Right" || data == "RIGHT") {
					if (data == "A" || data == "a")
						m_rightKey = sf::Keyboard::A;
					else if (data == "B" || data == "b")
						m_rightKey = sf::Keyboard::B;
					else if (data == "C" || data == "c")
						m_rightKey = sf::Keyboard::C;
					else if (data == "D" || data == "d")
						m_rightKey = sf::Keyboard::D;
					else if (data == "E" || data == "e")
						m_rightKey = sf::Keyboard::E;
					else if (data == "F" || data == "f")
						m_rightKey = sf::Keyboard::F;
					else if (data == "G" || data == "g")
						m_rightKey = sf::Keyboard::G;
					else if (data == "H" || data == "h")
						m_rightKey = sf::Keyboard::H;
					else if (data == "I" || data == "i")
						m_rightKey = sf::Keyboard::I;
					else if (data == "J" || data == "j")
						m_rightKey = sf::Keyboard::J;
					else if (data == "K" || data == "k")
						m_rightKey = sf::Keyboard::K;
					else if (data == "L" || data == "l")
						m_rightKey = sf::Keyboard::L;
					else if (data == "M" || data == "m")
						m_rightKey = sf::Keyboard::M;
					else if (data == "N" || data == "n")
						m_rightKey = sf::Keyboard::N;
					else if (data == "O" || data == "o")
						m_rightKey = sf::Keyboard::O;
					else if (data == "P" || data == "p")
						m_rightKey = sf::Keyboard::P;
					else if (data == "Q" || data == "q")
						m_rightKey = sf::Keyboard::Q;
					else if (data == "R" || data == "r")
						m_rightKey = sf::Keyboard::R;
					else if (data == "S" || data == "s")
						m_rightKey = sf::Keyboard::S;
					else if (data == "T" || data == "t")
						m_rightKey = sf::Keyboard::T;
					else if (data == "U" || data == "u")
						m_rightKey = sf::Keyboard::U;
					else if (data == "V" || data == "v")
						m_rightKey = sf::Keyboard::V;
					else if (data == "W" || data == "w")
						m_rightKey = sf::Keyboard::W;
					else if (data == "X" || data == "x")
						m_rightKey = sf::Keyboard::X;
					else if (data == "Y" || data == "y")
						m_rightKey = sf::Keyboard::Y;
					else if (data == "Z" || data == "z")
						m_rightKey = sf::Keyboard::Z;
					else if (data == "up" || data == "Up" || data == "UP")
						m_rightKey = sf::Keyboard::Up;
					else if (data == "left" || data == "Left" || data == "LEFT")
						m_rightKey = sf::Keyboard::Left;
					else if (data == "down" || data == "Down" || data == "DOWN")
						m_rightKey = sf::Keyboard::Down;
					else if (data == "right" || data == "Right" || data == "RIGHT")
						m_rightKey = sf::Keyboard::Right;
					else if (data == "space" || data == "Space" || data == "SPACE")
						m_rightKey = sf::Keyboard::Space;
					else if (data == "lshift" || data == "LShift" || data == "LSHIFT")
						m_rightKey = sf::Keyboard::LShift;
					else if (data == "lcontrol" || data == "LControl" || data == "LCONTROL")
						m_rightKey = sf::Keyboard::LControl;
				}
				else if (firstField == "melee" || data == "Melee" || data == "MELEE") {
					if (data == "A" || data == "a")
						m_meleeKey = sf::Keyboard::A;
					else if (data == "B" || data == "b")
						m_meleeKey = sf::Keyboard::B;
					else if (data == "C" || data == "c")
						m_meleeKey = sf::Keyboard::C;
					else if (data == "D" || data == "d")
						m_meleeKey = sf::Keyboard::D;
					else if (data == "E" || data == "e")
						m_meleeKey = sf::Keyboard::E;
					else if (data == "F" || data == "f")
						m_meleeKey = sf::Keyboard::F;
					else if (data == "G" || data == "g")
						m_meleeKey = sf::Keyboard::G;
					else if (data == "H" || data == "h")
						m_meleeKey = sf::Keyboard::H;
					else if (data == "I" || data == "i")
						m_meleeKey = sf::Keyboard::I;
					else if (data == "J" || data == "j")
						m_meleeKey = sf::Keyboard::J;
					else if (data == "K" || data == "k")
						m_meleeKey = sf::Keyboard::K;
					else if (data == "L" || data == "l")
						m_meleeKey = sf::Keyboard::L;
					else if (data == "M" || data == "m")
						m_meleeKey = sf::Keyboard::M;
					else if (data == "N" || data == "n")
						m_meleeKey = sf::Keyboard::N;
					else if (data == "O" || data == "o")
						m_meleeKey = sf::Keyboard::O;
					else if (data == "P" || data == "p")
						m_meleeKey = sf::Keyboard::P;
					else if (data == "Q" || data == "q")
						m_meleeKey = sf::Keyboard::Q;
					else if (data == "R" || data == "r")
						m_meleeKey = sf::Keyboard::R;
					else if (data == "S" || data == "s")
						m_meleeKey = sf::Keyboard::S;
					else if (data == "T" || data == "t")
						m_meleeKey = sf::Keyboard::T;
					else if (data == "U" || data == "u")
						m_meleeKey = sf::Keyboard::U;
					else if (data == "V" || data == "v")
						m_meleeKey = sf::Keyboard::V;
					else if (data == "W" || data == "w")
						m_meleeKey = sf::Keyboard::W;
					else if (data == "X" || data == "x")
						m_meleeKey = sf::Keyboard::X;
					else if (data == "Y" || data == "y")
						m_meleeKey = sf::Keyboard::Y;
					else if (data == "Z" || data == "z")
						m_meleeKey = sf::Keyboard::Z;
					else if (data == "up" || data == "Up" || data == "UP")
						m_meleeKey = sf::Keyboard::Up;
					else if (data == "left" || data == "Left" || data == "LEFT")
						m_meleeKey = sf::Keyboard::Left;
					else if (data == "down" || data == "Down" || data == "DOWN")
						m_meleeKey = sf::Keyboard::Down;
					else if (data == "right" || data == "Right" || data == "RIGHT")
						m_meleeKey = sf::Keyboard::Right;
					else if (data == "space" || data == "Space" || data == "SPACE")
						m_meleeKey = sf::Keyboard::Space;
					else if (data == "lshift" || data == "LShift" || data == "LSHIFT")
						m_meleeKey = sf::Keyboard::LShift;
					else if (data == "lcontrol" || data == "LControl" || data == "LCONTROL")
						m_meleeKey = sf::Keyboard::LControl;
					else if (data == "lmouse" || data == "LMouse" || data == "LMOUSE")
						m_meleeMouseButton = sf::Mouse::Left;
					else if (data == "rmouse" || data == "RMouse" || data == "RMOUSE")
						m_meleeMouseButton = sf::Mouse::Right;
					else if (data == "mmouse" || data == "MMouse" || data == "MMOUSE")
						m_meleeMouseButton = sf::Mouse::Middle;
				}
				else if (firstField == "jump" || data == "Jump" || data == "JUMP") {
					if (data == "A" || data == "a")
						m_jumpKey = sf::Keyboard::A;
					else if (data == "B" || data == "b")
						m_jumpKey = sf::Keyboard::B;
					else if (data == "C" || data == "c")
						m_jumpKey = sf::Keyboard::C;
					else if (data == "D" || data == "d")
						m_jumpKey = sf::Keyboard::D;
					else if (data == "E" || data == "e")
						m_jumpKey = sf::Keyboard::E;
					else if (data == "F" || data == "f")
						m_jumpKey = sf::Keyboard::F;
					else if (data == "G" || data == "g")
						m_jumpKey = sf::Keyboard::G;
					else if (data == "H" || data == "h")
						m_jumpKey = sf::Keyboard::H;
					else if (data == "I" || data == "i")
						m_jumpKey = sf::Keyboard::I;
					else if (data == "J" || data == "j")
						m_jumpKey = sf::Keyboard::J;
					else if (data == "K" || data == "k")
						m_jumpKey = sf::Keyboard::K;
					else if (data == "L" || data == "l")
						m_jumpKey = sf::Keyboard::L;
					else if (data == "M" || data == "m")
						m_jumpKey = sf::Keyboard::M;
					else if (data == "N" || data == "n")
						m_jumpKey = sf::Keyboard::N;
					else if (data == "O" || data == "o")
						m_jumpKey = sf::Keyboard::O;
					else if (data == "P" || data == "p")
						m_jumpKey = sf::Keyboard::P;
					else if (data == "Q" || data == "q")
						m_jumpKey = sf::Keyboard::Q;
					else if (data == "R" || data == "r")
						m_jumpKey = sf::Keyboard::R;
					else if (data == "S" || data == "s")
						m_jumpKey = sf::Keyboard::S;
					else if (data == "T" || data == "t")
						m_jumpKey = sf::Keyboard::T;
					else if (data == "U" || data == "u")
						m_jumpKey = sf::Keyboard::U;
					else if (data == "V" || data == "v")
						m_jumpKey = sf::Keyboard::V;
					else if (data == "W" || data == "w")
						m_jumpKey = sf::Keyboard::W;
					else if (data == "X" || data == "x")
						m_jumpKey = sf::Keyboard::X;
					else if (data == "Y" || data == "y")
						m_jumpKey = sf::Keyboard::Y;
					else if (data == "Z" || data == "z")
						m_jumpKey = sf::Keyboard::Z;
					else if (data == "up" || data == "Up" || data == "UP")
						m_jumpKey = sf::Keyboard::Up;
					else if (data == "left" || data == "Left" || data == "LEFT")
						m_jumpKey = sf::Keyboard::Left;
					else if (data == "down" || data == "Down" || data == "DOWN")
						m_jumpKey = sf::Keyboard::Down;
					else if (data == "right" || data == "Right" || data == "RIGHT")
						m_jumpKey = sf::Keyboard::Right;
					else if (data == "space" || data == "Space" || data == "SPACE")
						m_jumpKey = sf::Keyboard::Space;
					else if (data == "lshift" || data == "LShift" || data == "LSHIFT")
						m_jumpKey = sf::Keyboard::LShift;
					else if (data == "lcontrol" || data == "LControl" || data == "LCONTROL")
						m_jumpKey = sf::Keyboard::LControl;
					else if (data == "lmouse" || data == "LMouse" || data == "LMOUSE")
						m_jumpMouseButton = sf::Mouse::Left;
					else if (data == "rmouse" || data == "RMouse" || data == "RMOUSE")
						m_jumpMouseButton = sf::Mouse::Right;
					else if (data == "mmouse" || data == "MMouse" || data == "MMOUSE")
						m_jumpMouseButton = sf::Mouse::Middle;
				}
				else if (firstField == "throw" || data == "Throw" || data == "THROW") {
					if (data == "A" || data == "a")
						m_throwKey = sf::Keyboard::A;
					else if (data == "B" || data == "b")
						m_throwKey = sf::Keyboard::B;
					else if (data == "C" || data == "c")
						m_throwKey = sf::Keyboard::C;
					else if (data == "D" || data == "d")
						m_throwKey = sf::Keyboard::D;
					else if (data == "E" || data == "e")
						m_throwKey = sf::Keyboard::E;
					else if (data == "F" || data == "f")
						m_throwKey = sf::Keyboard::F;
					else if (data == "G" || data == "g")
						m_throwKey = sf::Keyboard::G;
					else if (data == "H" || data == "h")
						m_throwKey = sf::Keyboard::H;
					else if (data == "I" || data == "i")
						m_throwKey = sf::Keyboard::I;
					else if (data == "J" || data == "j")
						m_throwKey = sf::Keyboard::J;
					else if (data == "K" || data == "k")
						m_throwKey = sf::Keyboard::K;
					else if (data == "L" || data == "l")
						m_throwKey = sf::Keyboard::L;
					else if (data == "M" || data == "m")
						m_throwKey = sf::Keyboard::M;
					else if (data == "N" || data == "n")
						m_throwKey = sf::Keyboard::N;
					else if (data == "O" || data == "o")
						m_throwKey = sf::Keyboard::O;
					else if (data == "P" || data == "p")
						m_throwKey = sf::Keyboard::P;
					else if (data == "Q" || data == "q")
						m_throwKey = sf::Keyboard::Q;
					else if (data == "R" || data == "r")
						m_throwKey = sf::Keyboard::R;
					else if (data == "S" || data == "s")
						m_throwKey = sf::Keyboard::S;
					else if (data == "T" || data == "t")
						m_throwKey = sf::Keyboard::T;
					else if (data == "U" || data == "u")
						m_throwKey = sf::Keyboard::U;
					else if (data == "V" || data == "v")
						m_throwKey = sf::Keyboard::V;
					else if (data == "W" || data == "w")
						m_throwKey = sf::Keyboard::W;
					else if (data == "X" || data == "x")
						m_throwKey = sf::Keyboard::X;
					else if (data == "Y" || data == "y")
						m_throwKey = sf::Keyboard::Y;
					else if (data == "Z" || data == "z")
						m_throwKey = sf::Keyboard::Z;
					else if (data == "up" || data == "Up" || data == "UP")
						m_throwKey = sf::Keyboard::Up;
					else if (data == "left" || data == "Left" || data == "LEFT")
						m_throwKey = sf::Keyboard::Left;
					else if (data == "down" || data == "Down" || data == "DOWN")
						m_throwKey = sf::Keyboard::Down;
					else if (data == "right" || data == "Right" || data == "RIGHT")
						m_throwKey = sf::Keyboard::Right;
					else if (data == "space" || data == "Space" || data == "SPACE")
						m_throwKey = sf::Keyboard::Space;
					else if (data == "lshift" || data == "LShift" || data == "LSHIFT")
						m_throwKey = sf::Keyboard::LShift;
					else if (data == "lcontrol" || data == "LControl" || data == "LCONTROL")
						m_throwKey = sf::Keyboard::LControl;
					else if (data == "lmouse" || data == "LMouse" || data == "LMOUSE")
						m_throwMouseButton = sf::Mouse::Left;
					else if (data == "rmouse" || data == "RMouse" || data == "RMOUSE")
						m_throwMouseButton = sf::Mouse::Right;
					else if (data == "mmouse" || data == "MMouse" || data == "MMOUSE")
						m_throwMouseButton = sf::Mouse::Middle;
				}
				else if (firstField == "shoot" || data == "Shoot" || data == "SHOOT") {
					if (data == "A" || data == "a")
						m_shootKey = sf::Keyboard::A;
					else if (data == "B" || data == "b")
						m_shootKey = sf::Keyboard::B;
					else if (data == "C" || data == "c")
						m_shootKey = sf::Keyboard::C;
					else if (data == "D" || data == "d")
						m_shootKey = sf::Keyboard::D;
					else if (data == "E" || data == "e")
						m_shootKey = sf::Keyboard::E;
					else if (data == "F" || data == "f")
						m_shootKey = sf::Keyboard::F;
					else if (data == "G" || data == "g")
						m_shootKey = sf::Keyboard::G;
					else if (data == "H" || data == "h")
						m_shootKey = sf::Keyboard::H;
					else if (data == "I" || data == "i")
						m_shootKey = sf::Keyboard::I;
					else if (data == "J" || data == "j")
						m_shootKey = sf::Keyboard::J;
					else if (data == "K" || data == "k")
						m_shootKey = sf::Keyboard::K;
					else if (data == "L" || data == "l")
						m_shootKey = sf::Keyboard::L;
					else if (data == "M" || data == "m")
						m_shootKey = sf::Keyboard::M;
					else if (data == "N" || data == "n")
						m_shootKey = sf::Keyboard::N;
					else if (data == "O" || data == "o")
						m_shootKey = sf::Keyboard::O;
					else if (data == "P" || data == "p")
						m_shootKey = sf::Keyboard::P;
					else if (data == "Q" || data == "q")
						m_shootKey = sf::Keyboard::Q;
					else if (data == "R" || data == "r")
						m_shootKey = sf::Keyboard::R;
					else if (data == "S" || data == "s")
						m_shootKey = sf::Keyboard::S;
					else if (data == "T" || data == "t")
						m_shootKey = sf::Keyboard::T;
					else if (data == "U" || data == "u")
						m_shootKey = sf::Keyboard::U;
					else if (data == "V" || data == "v")
						m_shootKey = sf::Keyboard::V;
					else if (data == "W" || data == "w")
						m_shootKey = sf::Keyboard::W;
					else if (data == "X" || data == "x")
						m_shootKey = sf::Keyboard::X;
					else if (data == "Y" || data == "y")
						m_shootKey = sf::Keyboard::Y;
					else if (data == "Z" || data == "z")
						m_shootKey = sf::Keyboard::Z;
					else if (data == "up" || data == "Up" || data == "UP")
						m_shootKey = sf::Keyboard::Up;
					else if (data == "left" || data == "Left" || data == "LEFT")
						m_shootKey = sf::Keyboard::Left;
					else if (data == "down" || data == "Down" || data == "DOWN")
						m_shootKey = sf::Keyboard::Down;
					else if (data == "right" || data == "Right" || data == "RIGHT")
						m_shootKey = sf::Keyboard::Right;
					else if (data == "space" || data == "Space" || data == "SPACE")
						m_shootKey = sf::Keyboard::Space;
					else if (data == "lshift" || data == "LShift" || data == "LSHIFT")
						m_shootKey = sf::Keyboard::LShift;
					else if (data == "lcontrol" || data == "LControl" || data == "LCONTROL")
						m_shootKey = sf::Keyboard::LControl;
					else if (data == "lmouse" || data == "LMouse" || data == "LMOUSE")
						m_shootMouseButton = sf::Mouse::Left;
					else if (data == "rmouse" || data == "RMouse" || data == "RMOUSE")
						m_shootMouseButton = sf::Mouse::Right;
					else if (data == "mmouse" || data == "MMouse" || data == "MMOUSE")
						m_shootMouseButton = sf::Mouse::Middle;
				}
			}
		}
		else if (firstField == "Joystick") {
			std::cout << "Input\n{\n";
			while (dataFile.peek() != '}') {
				dataFile.getline(buf, sizeof(buf));

				iStr.str(std::string(buf));
				iStr >> firstField >> secondField >> data;
				iStr.clear();
				iStr.str("");

				if (firstField == "attack" || data == "Attack" || data == "ATTACK") {
					m_meleeJoyButton = atoi(data.c_str());
				} else if (firstField == "jump" || data == "Jump" || data == "JUMP") {
					m_jumpJoyButton = atoi(data.c_str());
				} else if (firstField == "sprint" || data == "Sprint" || data == "SPRINT") {
					m_sprintJoyButton = atoi(data.c_str());
				} else if (firstField == "shoot" || data == "Shoot" || data == "SHOOT") {
					m_shootJoyButton = atoi(data.c_str());
				}
			}
		}
	}

	dataFile.close();
}

void cInputManager::attachListener(cObject *object) {
	m_listeners.push_back(object);
}

void cInputManager::detachListener(cObject *object) {
	m_listeners.remove(object);
}

void cInputManager::keyDown(int keyDown) {
	for (auto it = m_listeners.begin(); it != m_listeners.end(); ++it) {
		(*it)->keyDown(keyDown);
	}
}

void cInputManager::keyUp(int keyUp) {
	for (auto it = m_listeners.begin(); it != m_listeners.end(); ++it) {
		(*it)->keyUp(keyUp);
	}
}

void cInputManager::mouseButtonDown(int mouseButtonDown) {
	for (auto it = m_listeners.begin(); it != m_listeners.end(); ++it) {
		(*it)->mouseButtonDown(mouseButtonDown);
	}
}

void cInputManager::mouseButtonUp(int mouseButtonUp) {
	for (auto it = m_listeners.begin(); it != m_listeners.end(); ++it) {
		(*it)->mouseButtonUp(mouseButtonUp);
	}
}

void cInputManager::joyButtonDown(int joyButtonDown) {
	for (auto it = m_listeners.begin(); it != m_listeners.end(); ++it) {
		(*it)->joyButtonDown(joyButtonDown);
	}
}

void cInputManager::joyButtonUp(int joyButtonUp) {
	for (auto it = m_listeners.begin(); it != m_listeners.end(); ++it) {
		(*it)->joyButtonUp(joyButtonUp);
	}
}

void cInputManager::joyMovedX(float joyMovedX) {
	for (auto it = m_listeners.begin(); it != m_listeners.end(); ++it) {
		(*it)->setJoyMovedX(joyMovedX);
	}
}

void cInputManager::joyMovedY(float joyMovedY) {
	for (auto it = m_listeners.begin(); it != m_listeners.end(); ++it) {
		(*it)->setJoyMovedY(joyMovedY);
	}
}
