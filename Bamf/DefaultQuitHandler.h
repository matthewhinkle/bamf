//
//  DefaultQuitHandler.h
//  Bamf
//
//  Created by Mike Hershey on 2/14/13.
//
//

#ifndef __Bamf__DefaultQuitHandler__
#define __Bamf__DefaultQuitHandler__

#include <iostream>
#include "IQuitHandler.h"
#include "SDL2/SDL.h"

namespace bamf {

class DefaultQuitHandler : public IQuitHandler
{
    
public:
    void onShouldQuit();
};
    
}

#endif /* defined(__Bamf__DefaultQuitHandler__) */
