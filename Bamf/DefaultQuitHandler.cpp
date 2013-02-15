//
//  DefaultQuitHandler.cpp
//  Bamf
//
//  Created by Mike Hershey on 2/14/13.
//
//

#include "DefaultQuitHandler.h"

namespace bamf {

void DefaultQuitHandler::onShouldQuit()
{
    exit(0);
}

}