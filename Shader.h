#pragma once

#include <string>
#include <SFML/Graphics.hpp>

//#include "Object.h"
//#include "Particle.h"

class cShader
{
public:
	cShader();
	//cSprite(const cBaseObject& other);
	//cSprite& operator=(const cBaseObject& other);
	~cShader();
	//void update(float time);

	void load(std::string fileName, std::string shaderType);

	sf::Shader* getSfShader() { return &m_sfShader; };

protected:
	sf::Shader m_sfShader;	
	std::string m_shaderType;
};