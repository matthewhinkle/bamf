// An imput mapping is supplied by the game. It maps input events to
// actions that should be executed.
//
// For example you can map the key down event to change a players vector to move right,
// and the key up event to set the vector back to 0.
//
//  IInputMapping.h
//  Bamf
//
//  Created by Mike Hershey on 2/11/13.
//
//

#ifndef Bamf_IInputMapping_h
#define Bamf_IInputMapping_h

#include "Action.h"

class IKeyMapping
{
    
public:
    virtual ~IKeyMapping() {}

    /**
      * Return true if this input mapping should activate for the given key code and mappings.
      */
    virtual bool appliesForInput(int keyCode, ...) = 0;

    /**
     * Returns the action for this given input
     */
    virtual Action actionForInput() = 0;

};

#endif
