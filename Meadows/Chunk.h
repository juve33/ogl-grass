#ifndef CHUNK_CLASS_H
#define CHUNK_CLASS_H

#include"GLTFModel.h"


// Chunk size in world space units
#define CHUNK_SIZE 0.5f
// LOD distance in world space units
#define LOD_DISTANCE 1.0f
// Render distance in chunks
#define RENDER_DISTANCE 6


class Chunk : public AbstractObject
{
private:
	unsigned int numberOfInstances;
	glm::vec2 position;
	glm::vec2 center;

public:
	// Constructor that generates a buffer object and links it to vertices
	Chunk(unsigned int density, glm::vec2 position = glm::vec2(0.0f, 0.0f));

	void Render(Shader& shader, Camera& camera, GLTFModel* model);

	glm::vec2 GetCenter();
};

#endif
