#include "RenderingManager.h"
#include "EntitySnow.h"
#include "ParticleSnow.h"
#include "LevelNode.h"

cEntitySnow::cEntitySnow() : m_frameCounter(0.0f), m_secondCall(false) {
	

}

cEntitySnow::~cEntitySnow() {

}

void cEntitySnow::update(cApp *app, float time) {
	if (m_attachedLevel == nullptr) {
		return;
	}
	//m_isLocked = false;
	//if (m_x < app->getViewWidth() || m_x > 0.0f) {
	//	for (unsigned short i = 0; i < m_particles.size(); ++i) {
	//		m_particles.at(i)->update(time);
	//		/*if (m_attachedLevel != nullptr && m_particles.at(i)->getLevelY() > m_attachedLevel->getNumRows() * 16 + 64.0f) {
	//			m_particles.at(i)->setIsDead(true);
	//		}
	//		if (m_x > app->getViewWidth()) {
	//			m_particles.at(i)->setIsDead(true);
	//		}*/
	//		if (m_particles.at(i)->getY() > m_attachedLevel->getNumRows()*16 - app->getViewHeight()) {
	//			m_particles.at(i)->die(this);
	//		}
	//		if (m_particles.at(i)->getIsDead() == true) {
	//			cRenderingManager::removeParticle(m_particles.at(i));
	//			m_particles.erase(m_particles.begin() + i, m_particles.begin() + i + 1);
	//		}
	//	}
	//}
	//else {	
	//	m_particles.clear();
	//	m_secondCall = false;
	//	m_frameCounter = 0.0f;
	//	return;
	//}

	float r = (float)(rand()) / (float)(RAND_MAX);
	unsigned short rand64 = rand() % 64;
	unsigned short rand128 = rand() % 128;

	cLevel *level = m_attachedLevel;

	if (!m_secondCall) {
		m_secondCall = true;

		float offsetY = -64.0f;
		if (m_isLocked) {
			offsetY = -96.0f;	// DOesn't work WHY????
		}
		// To prevent empty screen at startup
		for (int i = 0; i < 20; ++i) {
			unsigned short rand64 = rand() % 64;
			unsigned short rand128 = rand() % 128;
			level->addParticle(new cParticleSnow);
			level->getParticleLast()->loadConfig("Data\\Particles\\p_snow_0.cfg");
			level->getParticleLast()->attachLevel(level);
			level->getParticleLast()->attachParent(this);
			level->getParticleLast()->setX(getMiddleX() - 64 + rand128);
			level->getParticleLast()->setY(level->getParticleLast()->getVelocityY()*30*i + m_y + offsetY + rand64);

			float startX = m_levelX + 8 - 64 + rand128;
			float startY = m_levelY + offsetY + rand64;
			level->getParticleLast()->setStartX(startX);
			level->getParticleLast()->setStartY(startY);
			level->getParticleLast()->setLevelX(startX);
			level->getParticleLast()->setLevelY(startY);
			level->getParticleLast()->setVelocityX(level->getParticleLast()->getVelocityX() - 0.25f + r/2);
			level->getParticleLast()->setVelocityY(level->getParticleLast()->getVelocityY() - 0.25f + r/2);
			level->getParticleLast()->setIsHidden(false);
			level->getParticleLast()->setIsLocked(false);
			level->getParticleLast()->setIsSolid(true);
			level->getParticleLast()->update(time);


			int tileX = (int)(startX / 16);
			int tileY = (int)(startY / 16);
			
			int nodeX = (int)(tileX / 5);
			int nodeY = (int)(tileY / 5);

			cLevelNode node;
			node.setX(nodeX);
			node.setY(nodeY);
			unsigned short nodeColumns = level->getNumColumns() / 5;
			node.setColumns(nodeColumns);

			//std::cout << "cEntitySnow NODE " << node.get() << "\n";
			
			//for (unsigned char z = 0; z < l->getNumLayers(); ++z) {
			//	for (unsigned short y = 0; y < l->getNumRows(); ++y) {
			//		for (unsigned short x = 0; x < l->getNumColumns(); ++x) {
			//			unsigned short n = x + y * l->getNumColumns();
			//			n = x / 5 + (y / 5) * l->getNumColumns() / 5;
			//			level->getParticleLast()->setLevelNode(n);

			//			/*if (n == l->m_tileObjects[z][n].getLevelNode() && l->m_tileObjects[z][n].getIsSolidY()) {
			//				level->getParticleLast()->setIsDead(true);
			//			}*/

			//			//std::cout << l->getParticleLast()->getLevelNode() << " " << l->m_tileObjects[z][n].getLevelNode() << "\n";
			//			/*m_particles.at(l->m_particles.size() - 1)->collisionCheckX(&l->m_tileObjects[z][n]);
			//			m_particles.at(l->m_particles.size() - 1)->collisionCheckY(&l->m_tileObjects[z][n]);*/
			//		}
			//	}
			//}
			level->getParticleLast()->update(time);
		}
	}
	//std::cout << "hello" << "\n";
	const float frameLimit = 30;
	//std::cout << r << "\n";
	m_frameCounter += time;
	if (m_frameCounter > frameLimit*time/* && app->getWeatherColor() < 255.0f*/) {
		m_frameCounter = 0.0f;
		level->addParticle(new cParticleSnow);
		level->getParticleLast()->loadConfig("Data\\Particles\\p_snow_0.cfg");
		level->getParticleLast()->attachLevel(level);
		level->getParticleLast()->attachParent(this);
		level->getParticleLast()->setX(getMiddleX() - 64 + rand128);
		level->getParticleLast()->setY(m_y - 64 + rand64);

		float posX = m_levelX + 8 - 64 + rand128;
		float posY = m_levelY - 64 + rand64;
		level->getParticleLast()->setLevelX(posX);
		level->getParticleLast()->setLevelY(posY);
		level->getParticleLast()->setStartX(posX);
		level->getParticleLast()->setStartY(posY);

		level->getParticleLast()->setVelocityX(level->getParticleLast()->getVelocityX() - 0.25f + r/2);
		level->getParticleLast()->setVelocityY(level->getParticleLast()->getVelocityY() - 0.25f + r/2);
		//l->getParticleLast()->setDoGravitate(true);
		level->getParticleLast()->setIsHidden(false);
		level->getParticleLast()->setIsLocked(m_isLocked);
		level->getParticleLast()->setIsSolid(true);
		/*l->getParticleLast()->setVelocityX(0.0f);
		level->getParticleLast()->setVelocityY(2.0f);		*/
	}

	
}