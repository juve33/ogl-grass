#ifndef VAO_CLASS_H
#define VAO_CLASS_H

#include"AbstractObject.h"
#include"Buffer.h"

class VAO : public AbstractObject
{
public:
	// Constructor that generates a VAO ID
	VAO();

	// Links a VBO Attribute such as a position or color to the VAO
	void LinkAttrib(Buffer<Vertex>& VBO, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void* offset);
	// Links a VBO Attribute to the VAO
	void LinkAttrib(Buffer<glm::vec3>& VBO, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void* offset);
	// Binds the VAO
	void Bind();
	// Unbinds the VAO
	void Unbind();
	// Deletes the VAO
	void Delete();
};

#endif