#include "Chunk.h"

Chunk::Chunk(unsigned int density, glm::vec2 position)
{
	numberOfInstances = (unsigned int) (density * density * CHUNK_SIZE * CHUNK_SIZE);
	Chunk::position = position;
	center = position + glm::vec2(CHUNK_SIZE / 2.0f);
}

void Chunk::Render(Shader& shader, Camera& camera, GLTFModel* model)
{
	model->DrawInstanced(shader, camera, numberOfInstances, glm::vec3(position.x, 0.0f, position.y));
}

glm::vec2 Chunk::GetCenter()
{
	return center;
}