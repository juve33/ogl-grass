#ifndef SHADER_CLASS_H
#define SHADER_CLASS_H

#include"AbstractObject.h"
#include <glsl-includes-expanded/Shadinclude.hpp>
#include<string>
#include<fstream>
#include<sstream>
#include<iostream>
#include<cerrno>

std::string get_file_contents(const char* filename);

class Shader : public AbstractObject
{
public:
	// Constructor that creates an Shader Program Object using the Builder Pattern or something similar
	Shader();

	// Attach Shader File to the Shader Program
	// \param file: Name of the Shader File
	// \param shaderType: Specifies the type of shader to be created. Must be one of GL_COMPUTE_SHADER, GL_VERTEX_SHADER, GL_TESS_CONTROL_SHADER, GL_TESS_EVALUATION_SHADER, GL_GEOMETRY_SHADER, or GL_FRAGMENT_SHADER.
	// \param type: Name of the Shader File
	void Attach(const char* file, GLenum shaderType);
	// Build the Shader Program
	void Build();

	// Activates the Shader Program
	void Activate();
	// Deletes the Shader Program
	void Delete();
private:
	std::vector<GLuint> shaders;
	// Checks if the different Shaders have compiled properly
	void compileErrors(unsigned int shader, const char* type);
};


#endif