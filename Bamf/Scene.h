//
//  Scene.h
//  Bamf
//
//  Created by Matthew Hinkle on 2/15/13.
//
//

#ifndef Bamf_Scene_h
#define Bamf_Scene_h

#include <unordered_map>

#include "MatrixStack.h"
#include "SpriteStream.h"

#include "Drawable.h"

namespace bamf {

class SceneLayer;
class BamfObject;

class Scene : public Drawable {
public:

	Scene();
	virtual ~Scene();
	
	void addObjectWithZValue(BamfObject * bamf, float layerZValue);
		
	BamfObject * removeObject(uint64_t id);
	BamfObject * removeObject(BamfObject * bamf);
	
	void removeLayerWithZValue(float zValue);
	
	BamfObject * getObjectById(uint64_t id) const;
	
	void update(unsigned dt);
	
	void draw(SpriteStream * spriteStream, unsigned dt);
	
	/* common layers */
	static const float kPhysicsLayer;
	static const float kBackgroundLayer;
	static const float kForegroundFarLayer;
	static const float kForegroundMidLayer;
	static const float kForegroundNearLayer;
	static const float kHudLayer;
	
private:
	std::unordered_map<uint64_t, SceneLayer *> layerByObjectId;
	std::map<float, SceneLayer *> layerByZValue;
	
	Scene(const Scene &);
	Scene & operator=(const Scene &);
};

}

#endif
