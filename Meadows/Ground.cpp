#include "Ground.h"

Ground::Ground()
{

}

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