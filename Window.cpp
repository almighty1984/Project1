#include "Window.h"
#include <iostream>
//#include "StandardCursor.h"

cWindow::cWindow() : m_attachedLevel(nullptr), m_framerateLimit(0), m_viewTargetX(0.0f), m_viewX(0.0f),
m_useVerticalSync(false), m_isWidescreen(false), m_isViewLocked(false), m_showLevelNodeGrid(false), m_secondCall(false) {
	//m_shader.load("Data\\Shaders\\test.frag", "fragment");
	/*leftShape.setPosition(160, 120);
	leftShape.setSize(sf::Vector2f(128, 1));
	leftShape.setFillColor(sf::Color(128, 128, 128));*/

	
}

void cWindow::clearGrid() {
	m_horizontalLines.clear();
	m_verticalLines.clear();
	m_showLevelNodeGrid = false;
}

void cWindow::setShowLevelNodeGrid(bool showLevelNodeGrid) {	
	if (!m_showLevelNodeGrid) {
		if (m_attachedLevel != nullptr) {
			m_horizontalLines.clear();

			for (int i = 0; i < m_attachedLevel->getNumRows() / 5; ++i) {
				m_horizontalLines.push_back(new sf::RectangleShape);
				m_horizontalLines.at(m_horizontalLines.size() - 1)->setPosition(0.0f, (float)(i * 16));
				m_horizontalLines.at(m_horizontalLines.size() - 1)->setSize(sf::Vector2f((float)(m_attachedLevel->getNumColumns() * 16), 1.0f));
				m_horizontalLines.at(m_horizontalLines.size() - 1)->setFillColor(sf::Color(128, 128, 128));
			}
			m_verticalLines.clear();

			for (int i = 0; i < m_attachedLevel->getNumColumns() / 5; ++i) {
				m_verticalLines.push_back(new sf::RectangleShape);
				m_verticalLines.at(m_verticalLines.size() - 1)->setPosition((float)(i * 16), 0.0f);
				m_verticalLines.at(m_verticalLines.size() - 1)->setSize(sf::Vector2f(1.0f, (float)(m_attachedLevel->getNumRows() * 16)));
				m_verticalLines.at(m_verticalLines.size() - 1)->setFillColor(sf::Color(128, 128, 128));
			}
		}
	} else {
		m_horizontalLines.clear();
	}
	m_showLevelNodeGrid = showLevelNodeGrid;
}
void cWindow::attachLevel(cLevel *level) {
	m_attachedLevel = level;
	/*for (unsigned short y = 0; y < m_attachedLevel->getNumRows() / 5; ++y) {
		for (unsigned short x = 0; x < m_attachedLevel->getNumColumns() / 5; ++x) {
			m_gridShapes.push_back(new sf::RectangleShape);
			m_gridShapes.at(m_gridShapes.size() - 1)->setPosition(x * 5 * 16, (float)(y * 5 * 16));
			m_gridShapes.at(m_gridShapes.size() - 1)->setSize(sf::Vector2f(5.0f * 16.0f, 5.0f * 16.0f));
			m_gridShapes.at(m_gridShapes.size() - 1)->setFillColor(sf::Color::Transparent);
			m_gridShapes.at(m_gridShapes.size() - 1)->setOutlineThickness(2.0f);
		}
	}*/
}

void cWindow::create(unsigned short width, unsigned short height, unsigned short bits, char *title, float multiplier, bool isFullscreen, bool isWidescreen) {
	m_isWidescreen = isWidescreen;
	//multiplier = 3.0f;
	if (isWidescreen) {
		if (multiplier == 3.0f) {
			isFullscreen ? m_sfApp.create(sf::VideoMode(1280, 720, bits), title, sf::Style::Fullscreen) : m_sfApp.create(sf::VideoMode(1280, 720, bits), title, sf::Style::Close);
		} else if (multiplier == 2.0f) {
			isFullscreen ? m_sfApp.create(sf::VideoMode(854, 480, bits), title, sf::Style::Fullscreen) : m_sfApp.create(sf::VideoMode(854, 480, bits), title, sf::Style::Close);
		} else {
			isFullscreen ? m_sfApp.create(sf::VideoMode(854, 480, bits), title, sf::Style::Fullscreen) : m_sfApp.create(sf::VideoMode(426, 240, bits), title, sf::Style::Close);
		}

		m_sfApp.setView(sf::View((sf::FloatRect(-48, 0, 426/**2*/, 240/* * 2*/))));
	}
	else {
		m_sfApp.create(sf::VideoMode((int)(width*multiplier), (int)(height*multiplier), bits), title, sf::Style::Close);
		m_sfApp.setView(sf::View((sf::FloatRect(0, 0, 320, 240))));
	}
	m_sfApp.setMouseCursorVisible(true);
}

void cWindow::setView(float x1, float y1, float x2, float y2) {
	if (m_isViewLocked) {
		m_viewTargetX = 32.0f;
	}
	else {
		m_viewTargetX = x1;
	}

	if (m_viewTargetX < m_viewX) {
		//std::cout << "--m_viewX" << "\n";
		m_viewX-=1.0f;
	} else if (m_viewTargetX > m_viewX) {
		//std::cout << "++m_viewX" << "\n";
		m_viewX+=1.0f;
	} else if (m_viewTargetX == m_viewX) {
		return;
	}

	if (m_isWidescreen) {
		m_sfApp.setView(sf::View((sf::FloatRect(m_viewX - 48.0f, y1, x2, y2))));
	} else {
		m_sfApp.setView(sf::View((sf::FloatRect(m_viewX - 32.0f, y1, x2, y2))));
	}
	
}

void cWindow::setFramerateLimit(unsigned short framerateLimit) {
	m_sfApp.setFramerateLimit(framerateLimit);
	m_framerateLimit = framerateLimit;
}

void cWindow::setUseVerticalSync(bool useVerticalSync) {
	m_sfApp.setVerticalSyncEnabled(useVerticalSync);
	m_useVerticalSync = useVerticalSync;
}

void cWindow::draw(cSprite *sprite) {
	if (sprite == nullptr || sprite->getSfSprite() == nullptr) {
		return;
	}
	/*if (!m_secondCall) {
		m_secondCall = true;
		m_horizontalLines.clear();
		m_verticalLines.clear();
	}*/

	//if (m_attachedLevel != nullptr) {

	//	int posX = (int)(m_attachedLevel->getX() / 16 / 5);
	//	int posY = (int)(m_attachedLevel->getY() / 16 / 5);

	//	//std::cout << (int)(m_attachedLevel->getX() / 16/5) << "\n";

	//	for (unsigned short y = posY; y < 5; ++y) {
	//		for (unsigned short x = posX; x < 5; ++x) {
	//			int n = posX + posY * m_attachedLevel->getNumColumns() / 5;
	//			m_gridShapes.at(n)->setPosition(sf::Vector2f(posX + x * 5 * 16, posY + (float)(y * 5 * 16)));
	//			m_sfApp.draw(*m_gridShapes.at(n));
	//		}
	//	}

	//}

	m_sfApp.draw( *sprite->getSfSprite() );

}

void cWindow::draw(cSprite* sprite, cShader* shader) {
	if (sprite == nullptr || shader == nullptr || sprite->getSfSprite() == nullptr || shader->getSfShader() == nullptr) {
		return;
	}
	


	/*sf::RectangleShape fullscreen({100, 100 });

	sf::Texture texture;

	texture.update(m_sfApp);
	fullscreen.setPosition(sf::Vector2f(-48.0f, 0.0f));
	fullscreen.setTexture(&texture);
	sf::Shader sfShader;
	sfShader.loadFromFile("Data\\Shaders\\test.frag", sf::Shader::Fragment);

	m_sfApp.draw(fullscreen, &sfShader);*/
	m_sfApp.draw( *sprite->getSfSprite(), shader->getSfShader() );
	//m_sfApp.draw(*sprite->getSprite(), m_shader.getSfShader());

}

void cWindow::drawGrid() {
	if (!m_showLevelNodeGrid) {
		return;
	}	
	if (m_attachedLevel != nullptr) {
		for (unsigned short i = 0; i < m_horizontalLines.size(); ++i) {
			m_horizontalLines.at(i)->setPosition(sf::Vector2f(m_attachedLevel->getReferenceX(), m_attachedLevel->getReferenceY() + (float)(i * 5 * 16)));
			m_sfApp.draw(*m_horizontalLines.at(i));
		}
		for (unsigned short i = 0; i < m_verticalLines.size(); ++i) {
			m_verticalLines.at(i)->setPosition(sf::Vector2f(m_attachedLevel->getReferenceX() + (float)(i * 5 * 16), m_attachedLevel->getReferenceY()));
			m_sfApp.draw(*m_verticalLines.at(i));
		}
	}	
}

void cWindow::draw(cQuadNode* quadNode) {
	m_sfApp.draw(quadNode->upShape);
	m_sfApp.draw(quadNode->downShape);
	m_sfApp.draw(quadNode->leftShape);
	m_sfApp.draw(quadNode->rightShape);
}

void cWindow::close() {
	m_sfApp.close();
}

void cWindow::clear() {
	m_sfApp.clear(sf::Color(0,0,0,255));
}

void cWindow::display() {
	//sf::Sprite fullscreen;
	//sf::Texture texture;

	////texture.loadFromFile("Data\\Objects\\Images\\blob.png");

	//texture.update(m_sfApp);
	//fullscreen.setPosition(sf::Vector2f(-48.0f, 0.0f));
	//fullscreen.setTexture(texture);
	//fullscreen.setTextureRect(sf::IntRect(0, 0, 100, 100));
	//sf::Shader sfShader;
	//sfShader.loadFromFile("Data\\Shaders\\test.frag", sf::Shader::Fragment);
	//m_sfApp.draw(fullscreen, &sfShader);
	m_sfApp.display();
}

bool cWindow::isOpen() const {
	return m_sfApp.isOpen();
}

bool cWindow::getEvent(sf::Event &sfEvent) {
	return m_sfApp.pollEvent(sfEvent);
}
