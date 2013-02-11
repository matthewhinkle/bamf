//
//  VertexBufferObject.cpp
//  Bamf
//
//  Created by Matthew Hinkle on 2/10/13.
//
//

#include "VertexBufferObject.h"

namespace bamf {

template<typename T>
VertexBufferObject<T>::VertexBufferObject(unsigned size)
	:
	size(size),
	generated(false)
{
	SDL_assert(size);
	
	unsigned length = size / sizeof(T);
	this->vertices = new T[length];
}

template<typename T>
VertexBufferObject<T>::~VertexBufferObject()
{
	if(this->vertices) {
		delete[] this->vertices;
		this->vertices = NULL;
	}
	
	if(this->generated) {
		glDeleteBuffers(1, &this->vbo);
		this->generated = false;
	}
}

template<typename T>
void VertexBufferObject<T>::generate()
{
	if(__sync_bool_compare_and_swap(&this->generated, false, true)) {
		glGenBuffers(1, &this->vbo);
	}
}

template<typename T>
void VertexBufferObject<T>::bind()
{
	if(this != VertexBufferObject::current()) {
		glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
	}
}

template<typename T>
void VertexBufferObject<T>::map(VboAccessMode accessMode)
{
	glMapBuffer(GL_ARRAY_BUFFER, static_cast<GLenum>(accessMode));
}

template<typename T>
void VertexBufferObject<T>::unmap()
{
	glUnmapBuffer(GL_ARRAY_BUFFER, this->vbo);
}

template<typename T>
void VertexBufferObject<T>::buffer(size_t size, const void * data, VboDrawMode drawMode)
{
	glBufferData(GL_ARRAY_BUFFER, size, data, static_cast<GLenum>(drawMode));
}

}
