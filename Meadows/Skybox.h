#ifndef SKYBOX_CLASS_H
#define SKYBOX_CLASS_H

#include"AbsolutelyAbstractMesh.h"

class Skybox : protected AbsolutelyAbstractMesh
{
public:
	// Creates the skybox
	Skybox(std::string texturesDirectory);

	// Draws the skybox
	void Draw(Shader& shader, Camera& camera);

private:
	unsigned int cubemapTexture;
};
#endif
