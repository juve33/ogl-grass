#include"Buffer.h"
#pragma once
#ifndef _BUFFER_CLASS_CPP_
#define _BUFFER_CLASS_CPP_

// Constructor that does nothing (to avoid the error message when defining a buffer in a class)
template<typename T>
Buffer<T>::Buffer()
{

}

// Constructor that generates a buffer object and links it to vertices
template<typename T>
Buffer<T>::Buffer(GLenum target, std::vector<T>& bufferData)
{
	Buffer::target = target;
	glGenBuffers(1, &ID);
	glBindBuffer(target, ID);
	glBufferData(target, bufferData.size() * sizeof(T), bufferData.data(), GL_STATIC_DRAW);
}

// Constructor that generates a buffer object without any data
template<typename T>
Buffer<T>::Buffer(GLenum target, GLsizeiptr size, GLenum usage)
{
	Buffer::target = target;
	glGenBuffers(1, &ID);
	glBindBuffer(target, ID);
	glBufferData(target, size, NULL, usage);
}

// Binds the buffer
template<typename T>
void Buffer<T>::Bind()
{
	glBindBuffer(target, ID);
}

// Sets the buffer binding
template<typename T>
void Buffer<T>::SetBinding(GLuint binding)
{
	glBindBufferBase(target, binding, ID);
}

// Unbinds the buffer
template<typename T>
void Buffer<T>::Unbind()
{
	glBindBuffer(target, 0);
}

// Deletes the buffer
template<typename T>
void Buffer<T>::Delete()
{
	glDeleteBuffers(1, &ID);
}

#endif