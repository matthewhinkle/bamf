//
//  Updateable.h
//  Bamf
//
//  Created by Matthew Hinkle on 2/14/13.
//
//

#ifndef Bamf_Updateable_h
#define Bamf_Updateable_h

namespace bamf {

class Updateable {
public:

	Updateable() { }
	virtual ~Updateable() { }
	
	void update(unsigned delta);
	
private:
	Updateable(const Updateable &);
	Updateable & operator=(const Updateable &);
	
};

}

#endif
