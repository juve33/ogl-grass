#include "Ground.h"

Ground::Ground(std::string texturesDirectory)
{
	vertices =
	{
		Vertex{glm::vec3( 0.0f,  0.0f,  0.0f), glm::vec3( 0.0f,  1.0f,  0.0f), glm::vec3(0.0f, 0.2f, 0.0f), glm::vec2(0.0f, 0.0f)},
		Vertex{glm::vec3( 0.0f,  0.0f, -1.0f), glm::vec3( 0.0f,  1.0f,  0.0f), glm::vec3(0.0f, 0.2f, 0.0f), glm::vec2(0.0f, 1.0f)},
		Vertex{glm::vec3(-1.0f,  0.0f, -1.0f), glm::vec3( 0.0f,  1.0f,  0.0f), glm::vec3(0.0f, 0.2f, 0.0f), glm::vec2(1.0f, 1.0f)},
		Vertex{glm::vec3(-1.0f,  0.0f,  0.0f), glm::vec3( 0.0f,  1.0f,  0.0f), glm::vec3(0.0f, 0.2f, 0.0f), glm::vec2(1.0f, 0.0f)}
	};
	indices =
	{
		0, 1, 2,
		2, 3, 0
	};
	textures.push_back(Texture((texturesDirectory + "/diffuse.jpg").c_str(), "diffuse", 0));
	//textures.push_back(Texture((texturesDirectory + "/specular.jpg").c_str(), "specular", 0));

	VAO.Bind();
	// Generates Vertex Buffer Object and links it to vertices
	Buffer<Vertex> VBO(GL_ARRAY_BUFFER, vertices);
	// Generates Element Buffer Object and links it to indices
	Buffer<GLuint> EBO(GL_ELEMENT_ARRAY_BUFFER, indices);
	// Links VBO attributes such as coordinates and colors to VAO
	VAO.LinkAttrib(VBO, 0, 3, GL_FLOAT, sizeof(Vertex), (void*)0);
	VAO.LinkAttrib(VBO, 1, 3, GL_FLOAT, sizeof(Vertex), (void*)(3 * sizeof(float)));
	VAO.LinkAttrib(VBO, 2, 3, GL_FLOAT, sizeof(Vertex), (void*)(6 * sizeof(float)));
	VAO.LinkAttrib(VBO, 3, 2, GL_FLOAT, sizeof(Vertex), (void*)(9 * sizeof(float)));
	// Unbind all to prevent accidentally modifying them
	VAO.Unbind();
	VBO.Unbind();
	EBO.Unbind();
}

void Ground::prepareDraw
(
	Shader& shader,
	Camera& camera,
	glm::mat4 matrix,
	glm::vec3 translation,
	glm::quat rotation,
	glm::vec3 scale
)
{
	// Bind shader to be able to access uniforms
	shader.Activate();
	VAO.Bind();

	// Keep track of how many of each type of textures we have
	unsigned int numDiffuse = 0;
	unsigned int numSpecular = 0;

	for (unsigned int i = 0; i < textures.size(); i++)
	{
		std::string num;
		std::string type = textures[i].type;
		if (type == "diffuse")
		{
			num = std::to_string(numDiffuse++);
		}
		else if (type == "specular")
		{
			num = std::to_string(numSpecular++);
		}
		textures[i].texUnit(shader, (type + num).c_str(), i);
		textures[i].Bind();
	}
	// Take care of the camera Matrix
	glUniform3f(glGetUniformLocation(shader.ID, "camPos"), camera.Position.x, camera.Position.y, camera.Position.z);
	camera.Matrix(shader, "camMatrix");

	// Initialize matrices
	glm::mat4 trans = glm::mat4(1.0f);
	glm::mat4 rot = glm::mat4(1.0f);
	glm::mat4 sca = glm::mat4(1.0f);

	// Transform the matrices to their correct form
	trans = glm::translate(trans, translation);
	rot = glm::mat4_cast(rotation);
	sca = glm::scale(sca, scale);

	// Push the matrices to the vertex shader
	glUniformMatrix4fv(glGetUniformLocation(shader.ID, "translation"), 1, GL_FALSE, glm::value_ptr(trans));
	glUniformMatrix4fv(glGetUniformLocation(shader.ID, "rotation"), 1, GL_FALSE, glm::value_ptr(rot));
	glUniformMatrix4fv(glGetUniformLocation(shader.ID, "scale"), 1, GL_FALSE, glm::value_ptr(sca));
	glUniformMatrix4fv(glGetUniformLocation(shader.ID, "model"), 1, GL_FALSE, glm::value_ptr(matrix));
}

void Ground::Draw
(
	Shader& shader,
	Camera& camera,
	glm::mat4 matrix,
	glm::vec3 translation,
	glm::quat rotation,
	glm::vec3 scale
)
{
	prepareDraw(shader, camera, matrix, translation, rotation, scale);

	// Draw the actual mesh
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
}

void Ground::DrawInstanced
(
	Shader& shader,
	Camera& camera,
	GLsizei numberOfInstances,
	glm::mat4 matrix,
	glm::vec3 translation,
	glm::quat rotation,
	glm::vec3 scale
)
{
	prepareDraw(shader, camera, matrix, translation, rotation, scale);

	// Draw the actual mesh
	glDrawElementsInstanced(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0, numberOfInstances);
}