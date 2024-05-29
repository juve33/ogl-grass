#ifndef VAO_CLASS_H
#define VAO_CLASS_H

#include<glad/glad.h>
#include"Buffer.h"
// I'm including Buffer.cpp here bc off the linking error you probably already read about in another header file
#include"Buffer.cpp"

class VAO
{
public:
	// ID reference for the Vertex Array Object
	GLuint ID;
	// Constructor that generates a VAO ID
	VAO();

	// Links a VBO Attribute such as a position or color to the VAO
	void LinkAttrib(Buffer<Vertex>& VBO, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void* offset);
	// Binds the VAO
	void Bind();
	// Unbinds the VAO
	void Unbind();
	// Deletes the VAO
	void Delete();
};

#endif