//
//  InputManager.h
//  Bamf
//
//  Created by Mike Hershey on 2/11/13.
//
//

#ifndef Bamf_InputManager_h
#define Bamf_InputManager_h

#include "InputMapping.h"
#include "IKeyMapping.h"
#include "KeyPressType.h"
#include "Module.h"
#include <stdio.h>
#include <iostream>

#include "SDL2/SDL.h"

#include "Scene.h"

namespace bamf {

class InputManager : public Module
{
    
private:
    InputMapping * currentInputMapping;
    
public:
    InputManager();
    
    void init();
	
	void update(Scene * scene, unsigned delta);
    
    /**
      * Grabs and processes all user input (shoud be called each loop of game loop)
      */
    void processInput();
    
    /**
      * Sets the input mapping that will be     used here. The game should create an input mapping and set it before 
      * begining the game loop. The default InputMapping will be the nil Input Mapping and the game will have no controls.
      */
    void setInputMapping(InputMapping * inputMapping);
    InputMapping * getInputMapping();

};
    
}

#endif
