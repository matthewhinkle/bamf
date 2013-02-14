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

class IQuitHandler
{
    virtual ~IQuitHandler() {}
    
public:
    /**
     * Return true if this input mapping should activate for the given key code and masks.
     */
    virtual void onShouldQuit() = 0;
};

#endif /* defined(__Bamf__IQuitHandler__) */
