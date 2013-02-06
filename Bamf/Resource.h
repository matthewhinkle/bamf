//
//  Resource.h
//  Bamf
//
//  Created by Matthew Hinkle on 2/1/13.
//
//

#ifndef Bamf_Resource_h
#define Bamf_Resource_h

#include <string>

namespace bamf {

/**
	Resource interface.
	
	Resources differ from assets in that resources represent
	raw entities such as image, audio, and map files whereas
	assets represent entities such as sprites, maps, and the
	like
 */
class Resource {
public:

	explicit Resource() { }
	virtual ~Resource() { }
	
	/**
		Return the id of th resource
		
		@return the id of the resource
	 */
	virtual uint64_t getId() const = 0;
	
	/**
		Return the name of the resource.  This will typically
		be the resource's path
		
		@return the name of the resource
	 */
	virtual const std::string & getName() const = 0;

private:
	Resource(const Resource &);
	Resource & operator=(const Resource &);
};

}

#endif
