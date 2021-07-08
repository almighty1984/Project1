#include "App.h"
#include "InputManager.h"
#include "RenderingManager.h"
#include "SavesManager.h"
#include "SoundsManager.h"

#include <sstream>

void cApp::loadConfig(char* fileName) {
	std::ifstream dataFile(fileName);

	// Verify the data file was opened; exit if not.
	if (!dataFile) {
		std::cout << "Error:  Cannot open file " << fileName << "\n";
		//exit( 1 );
	}

	std::istringstream iStr(std::ios_base::out);
	char buf[80] = { 0 };
	std::string firstField, secondField, data, data2;
	firstField.clear();
	secondField.clear();
	data.clear();
	data2.clear();

	while (!dataFile.eof()) {
		dataFile.getline(buf, sizeof(buf));

		firstField.clear();
		secondField.clear();

		iStr.str(std::string(buf));
		iStr >> firstField >> secondField;
		iStr.clear();
		iStr.str("");

		if (firstField == "Config") {
			while (dataFile.peek() != '}') {
				dataFile.getline(buf, sizeof(buf));

				iStr.str(std::string(buf));
				iStr >> firstField >> secondField >> data;
				iStr.clear();
				iStr.str("");

				if (firstField == "player1") {
					m_pathPlayer1 = data;
				} else if (firstField == "joyDeadzone" || firstField == "joystickDeadzone") {
					//m_joystickDeadzone = atof(data.c_str());
					cInputManager::setJoyDeadzone((float)atof(data.c_str()));
				} else if (firstField == "font") {
					cRenderingManager::setPathFont(data);
					//m_pathFont = data;
					//std::cout << "FONT = " << m_pathFont << "\n";
				}
			}

		} else if (firstField == "Sounds") {
			while (dataFile.peek() != '}') {
				dataFile.getline(buf, sizeof(buf));

				iStr.str(std::string(buf));
				iStr >> firstField >> secondField >> data;
				iStr.clear();
				iStr.str("");
				cSoundsManager::createSound(firstField, data);
			}
		}
	}
	dataFile.close();

	cInputManager::loadConfig(fileName);
}

void cApp::clearLevelConfig() {
	clearTrains();
	setLevelStartDelay(0.0f);
}

void cApp::loadLevelConfig(const std::string fileName) {
	std::ifstream dataFile(fileName.c_str());

	// Verify the data file was opened; exit if not.
	if (!dataFile) {
		std::cout << "Error:  Cannot open file " << fileName << "\n";
		//exit( 1 );
	}

	std::istringstream iStr(std::ios_base::out);
	iStr.str("");
	iStr.clear();
	char buf[240] = { 0 };
	std::string firstField, secondField, data, data2;
	firstField.clear();
	secondField.clear();
	data.clear();
	data2.clear();

	//m_pathBackground.clear();

	//std::cout << "While !dataFile.eof" << "\n";
	while (!dataFile.eof()) {
		dataFile.getline(buf, sizeof(buf));

		iStr.str(std::string(buf));
		iStr >> firstField;
		iStr.clear();
		iStr.str("");

		if (firstField == m_pathLevel) {
			std::cout << fileName << "\n";
			while (dataFile.peek() != '}') {
				dataFile.getline(buf, sizeof(buf));

				iStr.str(std::string(buf));
				iStr >> firstField >> secondField >> data >> data2;
				iStr.clear();
				iStr.str("");

				if (firstField == "music0") {
					m_pathMusic[0] = data;
				} else if (firstField == "music1") {
					m_pathMusic[1] = data;
				} else if (firstField == "background") {
					m_pathBackground = data;
				} else if (firstField == "startDelay") {
					m_levelStartDelay = (float)atof(data.c_str());
				} else if (firstField.substr(0, 5) == "train") {
					std::cout << "FOUND A TRAIN " << firstField << secondField << data << data2 << "\n";
					int trainNum = 0;
					if (firstField.size() == 6) {
						trainNum = atoi(firstField.substr(5, 1).c_str());
					} else if (firstField.size() == 7) {
						trainNum = atoi(firstField.substr(5, 2).c_str());
					}
					size_t found = data.find("{");
					unsigned short i = 1;
					while (i < data.size()) {
						unsigned short pathNum = 0;
						if (data.at(i + 1) == ',' || data.at(i + 1) == '}') {
							pathNum = (int)atoi(data.substr(found + i, 1).c_str());
							m_trainNumbers[trainNum].push_back(pathNum);
							std::cout << "FOUND A TRAIN NUMBER " << data.substr(found + i, 1).c_str() << " " << pathNum << " " << "\n";
						} else if (data.at(i + 2) == ',' || data.at(i + 2) == '}') {
							pathNum = (int)atoi(data.substr(found + i, 2).c_str());
							m_trainNumbers[trainNum].push_back(pathNum);
							std::cout << "FOUND A TRAIN NUMBER " << data.substr(found + i, 2).c_str() << " " << pathNum << " " << "\n";
							++i;
						}
						i += 2;
					}
					//if (data2.substr(0, 6) == "Data\\" && m_trainPaths[trainNum].empty()) {
					std::cout << "m_trainPaths[trainNum] = " << data2 << "\n";
					m_trainPaths[trainNum] = data2;
					//}
				} else if (firstField.substr(0, 7) == "trigger" && firstField.size() == 8) {
					int num = 0;
					if (firstField.size() == 8) {
						std::istringstream(firstField.substr(7, 1)) >> num;
					} else if (firstField.size() == 9) {
						std::istringstream(firstField.substr(7, 2)) >> num;
					}
					strcpy_s(m_pathTrigger[num], 64, data.c_str());
				} else if (firstField == "weatherType") {
					m_weatherType = atoi(data.c_str());
				} else if (firstField == "doRain") {
					if (data == "true") {
						m_doRain = true;
					} else {
						m_doRain = false;
					}
				} else if (firstField == "precipitation") {
					m_darkenNumerator = atoi(data.substr(0, 1).c_str());
					m_darkenDenominator = atoi(data.substr(2, 1).c_str());

					if (data.size() > 3 && data.substr(3, 1) == ",") {
						m_lightenNumerator = atoi(data.substr(4, 1).c_str());
						m_lightenDenominator = atoi(data.substr(6, 1).c_str());
					}
				} else if (firstField.substr(0, 7) == "textBox") {
					unsigned char num = atoi(firstField.substr(7, 1).c_str());
					m_pathTextBox[num] = data;
				} else if (firstField.substr(0, 4) == "door") {
					int num = atoi(firstField.substr(4, 1).c_str());
					m_pathDoor[num] = data;
				} else if (firstField.substr(0, 4) == "left") {
					int num = atoi(firstField.substr(4, 1).c_str());
					m_pathLeft[num] = data;
				} else if (firstField.substr(0, 5) == "right") {
					int num = atoi(firstField.substr(5, 1).c_str());
					m_pathRight[num] = data;
				} else if (firstField.substr(0, 6) == "bottom") {
					int num = atoi(firstField.substr(6, 1).c_str());
					m_pathBottom[num] = data;
				} else if (firstField.substr(0, 3) == "top") {
					int num = atoi(firstField.substr(3, 1).c_str());
					m_pathTop[num] = data;
				}
			}
		}
	}

	dataFile.close();
}
