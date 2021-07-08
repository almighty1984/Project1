#include "TextureManager.h"
#include <iostream>

std::map<std::string, sf::Texture*> cTextureManager::m_textures;

cTextureManager::~cTextureManager() {
	unloadAll();
}

sf::Texture* cTextureManager::load(std::string fileName) {
	auto it = m_textures.find(fileName);
	//std::map<std::string, sf::Texture*>::iterator itr = cTextureManager::m_textures.find(fileName);

	sf::Texture *sfTexture;
	
	if (it == m_textures.end()) {
		sfTexture = new sf::Texture;
		sfTexture->loadFromFile(fileName);
		//if(sfImage->LoadFromFile(fileName) == false) {
		//	std::cout << "Image not found: " << fileName << "\n";			
		//}
		sfTexture->setSmooth(false);
		m_textures[fileName] = sfTexture;
		return sfTexture;
	} else {
		//std::cout << "Image already in map: " << itr->second << " " << fileName << "\n";
		return it->second;
	}
}

void cTextureManager::unloadAll() {
	for (auto it = m_textures.begin(); it != m_textures.end(); ++it) {
		delete it->second;
	}
	m_textures.clear();
}