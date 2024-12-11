#ifndef COMPUTE_SHADER_CLASS_H
#define COMPUTE_SHADER_CLASS_H

#include"Shader.h"
#include"Buffer.h"

class ComputeShader : public Shader
{
public:
	unsigned int bufferIndex = 0;
	// Dispatches the Shader Program
	void Dispatch();

	// Adds another Shader Storage Buffer Object
	void AddSSBO(GLsizeiptr size, GLenum usage);
};

#endif