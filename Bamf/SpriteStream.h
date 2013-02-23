//
//  SpriteStream.h
//  Bamf
//
//  Created by Matthew Hinkle on 2/9/13.
//
//

#ifndef __Bamf__SpriteStream__
#define __Bamf__SpriteStream__

#include <map>
#include <vector>

#include "SDL2/SDL.h"
#include "SDL2/SDL_opengl.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "Camera.h"
#include "MatrixStack.h"
#include "Sprite.h"

namespace bamf {

enum {
	kSpriteStreamClipEdges = 0x1,
	kSpriteStreamEnforceDrawOrder = 0x02
};

/**
	A sprite stream is used to send sprites to the
	frame buffer
 */
class SpriteStream {
public:
	
	explicit SpriteStream(Camera * camera);
	virtual ~SpriteStream();
	
	void begin(const glm::mat4 & transform = MatrixStack::kIdentMatrix, int drawOptions = 0);
	void draw(const Sprite * sprite, const glm::vec2 & position = glm::vec2());
	void end();
	
	void flush();
	
private:
	void render(size_t verticesCount);
	
	inline bool isClipping(const Sprite * sprite, const glm::vec2 & bottomLeft) {
		const Rectangle & bounds = sprite->getBounds();
		const Rectangle & viewArea = this->camera->getViewArea();
				
		return bottomLeft.x + bounds.width < viewArea.x
			|| bottomLeft.x > viewArea.getRight()
			|| bottomLeft.y + bounds.height < viewArea.getBottom()
			|| bottomLeft.y > viewArea.y + viewArea.height;
	}
	
	Camera * camera;

	GLuint vbo;
	
	int drawOptions;
	MatrixStack matrixStack;
	std::multimap<const Sprite *, glm::vec2> sprites;
	std::vector< std::pair<const Sprite *, glm::vec2> > targets;

	SpriteStream(const SpriteStream &);
	SpriteStream & operator=(const SpriteStream &);
};

}

#endif /* defined(__Bamf__SpriteStream__) */
