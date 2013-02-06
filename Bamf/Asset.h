//
//  Asset.h
//  Bamf
//
//  Created by Matthew Hinkle on 2/2/13.
//
//

#ifndef Bamf_Asset_h
#define Bamf_Asset_h

#include <vector>

#include "Resource.h"

namespace bamf {

/**
	Asset interface.  An asset is a higher-level object
	compounded with one or more resources or assets.
	
	Assets do not own the resources they are made of as
	resources are shared.  Hence an asset must not delete
	or free any of its resources.  If an asset is loading
	or unloading resources (via a resource manager), then
	you are likely doing something wrong.
 */
class Asset {
public:

	explicit Asset() { }
	virtual ~Asset() { }
	
	/**
		Return the id of the asset
		
		@return the id of the asset
	 */
	virtual uint64_t getId() const = 0;

private:
	Asset(const Asset &);
	Asset & operator=(const Asset &);
};

}

#endif
