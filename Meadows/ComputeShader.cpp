#include"ComputeShader.h"

// Dispatches the Shader Program
void ComputeShader::Dispatch()
{
	glDispatchCompute(1, 1, 1);
	glMemoryBarrier(GL_ALL_BARRIER_BITS);
}

// Adds another Shader Storage Buffer Object
void ComputeShader::AddSSBO(GLsizeiptr size, GLenum usage)
{
	Buffer<bool> ssbo(GL_SHADER_STORAGE_BUFFER, size, usage);
	ssbo.SetBinding(bufferIndex++);
	ssbo.Unbind();
}