#include"Buffer.h"
#pragma once
#ifndef _BUFFER_CLASS_CPP_
#define _BUFFER_CLASS_CPP_

// Constructor that generates a buffer object and links it to vertices
template<typename T>
Buffer<T>::Buffer(GLenum target, std::vector<T>& bufferData)
{
	Buffer::target = target;
	glGenBuffers(1, &ID);
	glBindBuffer(target, ID);
	glBufferData(target, bufferData.size() * sizeof(T), bufferData.data(), GL_STATIC_DRAW);
}

// Binds the buffer
template<typename T>
void Buffer<T>::Bind()
{
	glBindBuffer(target, ID);
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