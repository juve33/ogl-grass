#include "Atmosphere.h"

Atmosphere::Atmosphere()
{

}

void Atmosphere::bindShader(Shader* shader)
{
	shader_ptrs.push_back(shader);
}

void Atmosphere::set(glm::vec4 lightColor, glm::vec3 lightPos, glm::vec4 fogColor)
{
	glm::vec3 lightDir = glm::normalize(lightPos);
	for (Shader* shader : shader_ptrs)
	{
		shader->Activate();
		glUniform4f(glGetUniformLocation(shader->ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
		glUniform4f(glGetUniformLocation(shader->ID, "fogColor"), fogColor.x, fogColor.y, fogColor.z, fogColor.w);
		glUniform3f(glGetUniformLocation(shader->ID, "lightDir"), lightDir.x, lightDir.y, lightDir.z);
	}
}