#ifndef ATMOSPHERE_CLASS_H
#define ATMOSPHERE_CLASS_H

#include"AbstractMesh.h"

class Atmosphere
{
public:
	// Constructs atmosphere object
	Atmosphere();

	// Binds shader to atmosphere object
	void bindShader(Shader* shader);

	// changes the atmosphere in all bound shaders
	void set(glm::vec4 lightColor, glm::vec3 lightPos, glm::vec4 fogColor);

private:
	std::vector<Shader*> shader_ptrs;
};
#endif