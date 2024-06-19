#ifndef CHUNK_CLASS_H
#define CHUNK_CLASS_H

#include"GLTFModel.h"


class Chunk : public AbstractObject
{
private:
	unsigned int numberOfInstances;
	glm::vec2 position;
	glm::vec2 center;

public:
	// Constructor that generates a buffer object and links it to vertices
	Chunk(unsigned int density, glm::vec2 position = glm::vec2(0.0f, 0.0f));

	void Render(Shader& shader, Camera* camera, GLTFModel* model);

	glm::vec2 GetCenter();
};

#endif
