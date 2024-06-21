#include "Chunk.h"

Chunk::Chunk(unsigned int density, Ground* ground, glm::vec2 position)
{
	numberOfInstances = (unsigned int) (density * density * CHUNK_SIZE * CHUNK_SIZE);
	Chunk::position = position;
	Chunk::ground = ground;
	glm::vec2 _center = position + glm::vec2(CHUNK_SIZE / 2.0f);
	center = glm::vec3(_center.x, 0.0f, _center.y);
	if (SCREEN_HEIGHT < SCREEN_WIDTH)
	{
		cosViewAngle = cos(glm::radians((2.0f - (SCREEN_HEIGHT / SCREEN_WIDTH)) * VIEW_ANGLE));
	}
	else
	{
		cosViewAngle = cos(glm::radians(VIEW_ANGLE));
	}
}

void Chunk::Render(Shader& shader, Shader& groundShader, Camera* camera, GLTFModel* model)
{
	//if (glm::dot(glm::normalize(center - camera->Position), glm::normalize(glm::vec3(0.5f, 0.0f, 1.0f))) >= cosViewAngle)
	if (glm::dot(glm::normalize(center - camera->Position), glm::normalize(camera->Orientation)) >= cosViewAngle)
	{
		ground->Draw(groundShader, *camera, glm::mat4(1.0f), glm::vec3(-position.x, 0.0f, -position.y), glm::quat(1.0f, 0.0f, 0.0f, 0.0f), glm::vec3(CHUNK_SIZE, CHUNK_SIZE, CHUNK_SIZE));
		model->DrawInstanced(shader, *camera, numberOfInstances, glm::vec3(position.x, 0.0f, position.y));
	}
}

void Chunk::ForceRender(Shader& shader, Shader& groundShader, Camera* camera, GLTFModel* model)
{
	ground->Draw(groundShader, *camera, glm::mat4(1.0f), glm::vec3(-position.x, 0.0f, -position.y), glm::quat(1.0f, 0.0f, 0.0f, 0.0f), glm::vec3(CHUNK_SIZE, CHUNK_SIZE, CHUNK_SIZE));
	model->DrawInstanced(shader, *camera, numberOfInstances, glm::vec3(position.x, 0.0f, position.y));
}

glm::vec2 Chunk::GetCenter()
{
	return center.xz();
}