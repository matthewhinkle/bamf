//
//  Paths.h
//  Bamf
//
//  Created by Matthew Hinkle on 2/1/13.
//
//

#ifndef __Bamf__Paths__
#define __Bamf__Paths__

#include <string>

namespace bamf {

/**
	Utility class for dealing with file paths
 */
class Paths {
public:
	/**
		Get the extension from a path if one exists
		
		@return the extension (if it exists) for the specified
		        path.  if no extension is found, then the empty
				string is returned
	 */
	static inline std::string getExtension(const std::string & path) {
		ssize_t pos = path.rfind('.');
		if(pos < 0 || pos >= (path.length() - 1)) {
			return "";
		}
		
		return path.substr(pos + 1);
	}

};

}

#endif /* defined(__Bamf__Paths__) */
