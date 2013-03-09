//
//  ArtificialIntelligenceModule.h
//  Bamf
//
//  Created by Matthew Hinkle on 3/7/13.
//
//

#ifndef __Bamf__ArtificialIntelligenceModule__
#define __Bamf__ArtificialIntelligenceModule__

#include <unordered_map>

#include "Astar.h"
#include "ActivePath.h"
#include "BamfObject.h"
#include "MathCommons.h"
#include "Module.h"
#include "Scene.h"

namespace bamf {

class ArticialIntelligenceModule : public Module {
public:

	ArticialIntelligenceModule();
	virtual ~ArticialIntelligenceModule();
	
	void init();
	
	void update(Scene * scene, unsigned dt);
	
	void addObject(BamfObject * object) {
		this->agentById.insert(std::pair<uint64_t, BamfObject *>(object->getId(), object));
	}
	
	inline BamfObject * getObjectById(uint64_t id) {
		std::unordered_map<uint64_t, BamfObject *>::const_iterator i = this->agentById.find(id);
		return i == this->agentById.end() ? NULL : i->second;
	}

private:
	std::unordered_map<uint64_t, BamfObject *> agentById;

	ArticialIntelligenceModule(const ArticialIntelligenceModule &);
	ArticialIntelligenceModule & operator=(const ArticialIntelligenceModule &);
};

}

#endif /* defined(__Bamf__ArtificialIntelligenceModule__) */
