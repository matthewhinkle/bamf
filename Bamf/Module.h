//
//  Module.h
//  Bamf
//
//  Created by Matthew Hinkle on 2/14/13.
//
//

#ifndef Bamf_Module_h
#define Bamf_Module_h

#include "Updateable.h"

namespace bamf {

class Module : public Updateable {
public:

	explicit Module() { }
	virtual ~Module() { }
	
	virtual void init() = 0;
	
	virtual void update(unsigned delta) = 0;

private:
	Module(const Module &);
	Module & operator=(const Module &);
};

}

#endif
