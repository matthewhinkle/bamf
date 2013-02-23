//
//  SceneLayer.h
//  Bamf
//
//  Created by Matthew Hinkle on 2/22/13.
//
//

#ifndef __Bamf__SceneLayer__
#define __Bamf__SceneLayer__

#include <unordered_map>

namespace bamf {

/**
	A single layer in a Scene.  Objects drawn on the
	same layer have no defined order
 */
class SceneLayer {
public:

	SceneLayer();
	virtual ~SceneLayer();
	
	

private:

	SceneLayer(const SceneLayer &);
	SceneLayer & operator=(const SceneLayer &);
};

}

#endif /* defined(__Bamf__SceneLayer__) */
