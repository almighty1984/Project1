#pragma once

#include <SFML/Graphics.hpp>
#include <map>

#include "App.h"

class cTextureManager {
public:
	~cTextureManager();
	static sf::Texture* load(std::string fileName);
	//void unload(std::string fileName);
	static void unloadAll();
private:
	static std::map<std::string, sf::Texture*> m_textures;
};
