//
//  DefaultQuitHandler.cpp
//  Bamf
//
//  Created by Mike Hershey on 2/14/13.
//
//

#include "DefaultQuitHandler.h"

void DefaultQuitHandler::onShouldQuit()
{
    SDL_Quit();
}