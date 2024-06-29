#pragma once
#ifndef BUFFER_CLASS_H
#define BUFFER_CLASS_H

#define GLM_FORCE_SWIZZLE
#include<glm/glm.hpp>
#include"AbstractObject.h"
#include<vector>

// Structure to standardize the vertices used in the meshes
struct Vertex
{
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec3 color;
	glm::vec2 texUV;
};



template<typename T>
class Buffer : public AbstractObject
{
private:
	GLenum target;
public:
	// Constructor that generates a buffer object and links it to vertices
	Buffer(GLenum target, std::vector<T>& bufferData);
	// Constructor that does nothing (to avoid the error message when defining a buffer in a class)
	Buffer();

	// Binds the buffer
	void Bind();
	// Sets the buffer binding
	void SetBinding(GLuint binding);
	// Unbinds the buffer
	void Unbind();
	// Deletes the buffer
	void Delete();
};

// I'm including Buffer.cpp here bc off the linking error you probably already read about in another header file
#include"Buffer.cpp"

#endif