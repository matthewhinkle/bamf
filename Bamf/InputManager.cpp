// Nothing about input is thread safe.
//
//  InputManager.cpp
//  Bamf
//
//  Created by Mike Hershey on 2/11/13.
//
//

#include "InputManager.h"

namespace bamf {
    
InputManager::InputManager()
    : currentInputMapping(new InputMapping())
{
    
}
    
void InputManager::init()
{
    
}

void InputManager::update(unsigned int delta)
{
    SDL_Event e;
    while(SDL_PollEvent(&e)) {
        if(e.type == SDL_QUIT) {
            this->currentInputMapping->getQuitHandler()->onShouldQuit();
        }
        if(e.type == SDL_KEYDOWN) {
            this->currentInputMapping->dispatchKeyEvent(KEY_DOWN, e.key.keysym.sym);
        }
        if(e.type == SDL_KEYUP) {
            this->currentInputMapping->dispatchKeyEvent(KEY_UP, e.key.keysym.sym);
        }
    }
}

void InputManager::setInputMapping(InputMapping * inputMapping)
{
    currentInputMapping = inputMapping;
}
    
}