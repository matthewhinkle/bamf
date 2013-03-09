//
//  SceneLayer.h
//  Bamf
//
//  Created by Matthew Hinkle on 3/8/13.
//
//

#ifndef Bamf_SceneLayer_h
#define Bamf_SceneLayer_h

#include "BamfObject.h"
#include "Drawable.h"
#include "Updateable.h"

namespace bamf {

template<
	typename Id,
	typename Value
> class SceneLayer : public Drawable, public Updateable {
public:

	SceneLayer() { }
	virtual ~SceneLayer() { }
	
	virtual void addObject(Value value) = 0;
	
	virtual Value getObjectById(Id id) const = 0;
	
	virtual unsigned getObjectCount() const = 0;
	
	virtual Value removeObject(Id id) = 0;
	virtual Value removeObject(Value value) = 0;
	
private:
	SceneLayer(const SceneLayer &);
	SceneLayer & operator=(const SceneLayer &);
};

}

#endif
