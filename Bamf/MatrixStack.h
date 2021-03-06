//
//  MatrixStack.h
//  Bamf
//
//  Created by Matthew Hinkle on 2/8/13.
//
//

#ifndef __Bamf__MatrixStack__
#define __Bamf__MatrixStack__

#include <stack>

#include "glm/glm.hpp"

#include "SDL2/SDL.h"
#include "SDL2/SDL_opengl.h"

namespace bamf {

typedef enum {
	kMatrixModeProjection = GL_PROJECTION,
	kMatrixModeModel = GL_MODELVIEW
} MatrixMode;

/**
	Implementation of the matrix push and pop operations
	as glMatrixPush() and glMatrixPop() have been
	deprecated
 */
class MatrixStack {
public:

	MatrixStack() {
		/* initialize with the identity matrix */
		this->stack.push(glm::mat4());
	}
	
	virtual ~MatrixStack() { }
	
	inline glm::mat4 & push() {
		glm::mat4 top = this->stack.top();
		this->stack.push(top);
		glm::mat4 & ret = this->stack.top();
		
		return ret;
	}
	
	inline void pop() {
		if(this->stack.size() > 0) {
			this->stack.pop();
		}
	}
	
	inline void mult(const glm::mat4 & m) {
		if(this->stack.size() > 0) {
			glm::mat4 top = this->stack.top();
			this->stack.pop();
			this->stack.push(top * m);
		}
	}
	
	inline void reset(const glm::mat4 & m = glm::mat4()) {
		this->stack = std::stack<glm::mat4>();
		this->stack.push(m);
	}
	
	inline const glm::mat4 & top() const { return this->stack.top(); }
	
	static inline void setMatrixMode(MatrixMode mode) { glMatrixMode(mode); }
	static inline void loadMatrix(const glm::mat4 & m = kIdentMatrix) { glLoadMatrixf(&m[0][0]); }
	
	static const glm::mat4 kIdentMatrix;
	
private:
	std::stack<glm::mat4> stack;
	
	MatrixStack(const MatrixStack &);
	MatrixStack & operator=(const MatrixStack &);
};

}

#endif /* defined(__Bamf__MatrixStack__) */
