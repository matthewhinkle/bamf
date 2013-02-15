//
//  IQuitHandler.h
//  Bamf
//
//  Created by Mike Hershey on 2/14/13.
//
//

#ifndef __Bamf__IQuitHandler__
#define __Bamf__IQuitHandler__

#include <iostream>

namespace bamf {

class IQuitHandler
{
    
public:
    virtual ~IQuitHandler() {}
    
    virtual void onShouldQuit() = 0;
};
    
}

#endif /* defined(__Bamf__IQuitHandler__) */
