#ifndef CHUNK_HANDLER_CLASS_H
#define CHUNK_HANDLER_CLASS_H

#include"Chunk.h"
#include"ComputeShader.h"


class ChunkHandler
{
private:
	std::vector<Chunk> chunks;
	unsigned int numberOfInstancesPerChunk;
	int x;
	int y;
	glm::vec2 startPosition;
	Ground ground;

public:
	// Constructor that generates a buffer object and links it to vertices
	ChunkHandler(std::string groundTexDir, unsigned int x, unsigned int y, unsigned int density, glm::vec2 startPosition = glm::vec2(0.0f, 0.0f));

	void BindCamera(Camera* camera);

	void Render(Shader& shader, Shader& groundShader, Camera* camera, AbstractModel* LOD1, AbstractModel* LOD2);

	unsigned int GetNumberOfInstancesPerChunk();
};

#endif
