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

#include "SDL2/SDL.h"

#include "Resource.h"
#include "ResourceManager.h"

namespace bamf {

/**
	Asset abstract class.  An asset is a higher-level object
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
		Load the resources used by this asset.  This method
		must be idempotent -- successive calls to Asset::load()
		shall have no effect (unless the class implements
		unloading, in that case successive calls should have
		no effect until the asset is unloaded)
		
		@param resourceManager the resource manager to use when
		                       loading this asset's resources
	 */
	virtual void load(ResourceManager & resourceManager) = 0;
	
	/**
		Return true if the asset has been loaded, false
		otherwise
		
		@return true if the asset has been loaded, false
		        otherwise
	 */
	virtual bool wasLoaded() const = 0;
	
private:
	Asset(const Asset &);
	Asset & operator=(const Asset &);
};

}

#endif
