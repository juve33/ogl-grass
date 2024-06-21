#ifndef CHUNK_CLASS_H
#define CHUNK_CLASS_H

#include"GLTFModel.h"
#include "Ground.h"


class Chunk
{
private:
	unsigned int numberOfInstances;
	glm::vec2 position;
	glm::vec3 center;
	float cosViewAngle;
	Ground* ground;

public:
	// Constructor that generates a buffer object and links it to vertices
	Chunk(unsigned int density, Ground* ground = nullptr, glm::vec2 position = glm::vec2(0.0f, 0.0f));

	void Render(Shader& shader, Shader& groundShader, Camera* camera, GLTFModel* model);
	void ForceRender(Shader& shader, Shader& groundShader, Camera* camera, GLTFModel* model);

	glm::vec2 GetCenter();
};

#endif
