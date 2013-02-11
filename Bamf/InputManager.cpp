// Nothing about input is thread safe.
//
//  InputManager.cpp
//  Bamf
//
//  Created by Mike Hershey on 2/11/13.
//
//

#include "InputManager.h"

InputManager::InputManager()
    : currentInputMapping(new InputMapping())
{
    
}

void InputManager::processInput()
{
    SDL_Event e;
    while(SDL_PollEvent(&e)) {
        if(e.type == SDL_KEYDOWN) {
            this->currentInputMapping->dispatchKeyEvent(KEY_DOWN, e.key.keysym.sym);
        }
    }
}

void InputManager::setInputMapping(InputMapping * inputMapping)
{
    currentInputMapping = inputMapping;
}