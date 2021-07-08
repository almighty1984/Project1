#include "Shader.h"

cShader::cShader() {
	m_shaderType = "Fragment";
	//m_sfShader.setUniform("color", sf::Shader::Vec4(color));
	m_sfShader.setUniform("texture", sf::Shader::CurrentTexture);
}

cShader::~cShader() {
	//m_sfShader.~Shader();
	m_shaderType.clear();
}

void cShader::load(std::string fileName, std::string shaderType) {
	m_shaderType = shaderType;

	if (shaderType == "Fragment") {
		m_sfShader.loadFromFile(fileName, sf::Shader::Fragment);
	} else if (shaderType == "Vertex") {
		m_sfShader.loadFromFile(fileName, sf::Shader::Vertex);
	} else {
		m_shaderType = "Fragment";
		m_sfShader.loadFromFile(fileName, sf::Shader::Fragment);
	}
}