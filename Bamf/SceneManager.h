//
//  SceneManager.h
//  Bamf
//
//  Created by Matthew Hinkle on 2/22/13.
//
//

#ifndef __Bamf__SceneManager__
#define __Bamf__SceneManager__

#include <stack>

#include "glm/glm.hpp"

#include "Scene.h"
#include "Updateable.h"
#include "Drawable.h"
#include "SpriteStream.h"

namespace bamf {

class SceneManager : public Drawable, public Updateable {
public:

	SceneManager();
	virtual ~SceneManager();
	
	void pushScene(Scene * scene);
	
	Scene * popScene(unsigned num = 1);
	
	inline Scene * getCurrentScene() { return this->scenes.empty() ? NULL : this->scenes.top(); }
	
	void update(Scene * scene, unsigned dt);
	
	void draw(SpriteStream * spriteStream, unsigned dt);
	
private:
	std::stack<Scene *> scenes;
	
	SceneManager(const SceneManager &);
	SceneManager & operator=(const SceneManager &);
};

}

#endif /* defined(__Bamf__SceneManager__) */
