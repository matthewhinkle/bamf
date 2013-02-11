//
//  VertexBufferObject.h
//  Bamf
//
//  Created by Matthew Hinkle on 2/10/13.
//
//

#ifndef __Bamf__VertexBufferObject__
#define __Bamf__VertexBufferObject__

#include <string>

#include "SDL2/SDL.h"
#include "SDL2/SDL_opengl.h"

namespace bamf {

typedef enum {
	kVboStaticDraw = GL_STATIC_DRAW,
	kVboDynamicDraw = GL_DYNAMIC_DRAW,
	kVboStreamDraw = GL_STREAM_DRAW
} VboDrawMode;

typedef enum {
	kVboReadOnly = GL_READ_ONLY,
	kVboWriteOnly = GL_WRITE_ONLY,
	kVboReadWrite = GL_READ_WRITE
} VboAccessMode;

enum {
	kVboMegabyte = 1048576,
	kVboVerticesPerSprite = 6
};

template<typename T>
class VertexBufferObject {
public:

	explicit VertexBufferObject(unsigned size = kVboMegabyte);
	virtual ~VertexBufferObject();
	
	/**
		Generate the buffer object
	 */
	void generate();
	
	/**
		Bind the buffer object
	 */
	void bind();
	
	/**
		Map the buffer from the gpu.  Do this when making
		frequent updates, remembering to call
		VertexBufferObject::unmap() when finished
		
		@param accessMode the access mode to use.  Unless
						  reading is actually required, then
						  kVboWriteOnly should be used
	 */
	void map(VboAccessMode accessMode = kVboWriteOnly);
	
	/**
		Unmap the mapped buffer.  If no buffer is mapped
		then this method results in undefined behavior
	 */
	void unmap();
	
	/**
		Buffer data using the specified draw mode
	 */
	void buffer(size_t size, const void * data, VboDrawMode drawMode);
	
	inline T * & operator[](unsigned i) { return this->vertices + i; }
	inline const T * & operator[](unsigned i) const { return this->verties + i; }
	
	static inline VertexBufferObject * current() { return VertexBufferObject::currentVbo; }
	
private:
	GLuint vbo;
	
	unsigned size;
	bool generated;
	
	T * vertices;
	
	static std::atomic<VertexBufferObject *> currentVbo;
	
	const std::string kVboName = "";
	
	VertexBufferObject(const VertexBufferObject &);
	VertexBufferObject & operator=(const VertexBufferObject &);
};

}

#endif /* defined(__Bamf__VertexBufferObject__) */
