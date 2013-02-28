//
//  InputMapping.h
//  Bamf
//
//  Created by Mike Hershey on 2/11/13.
//
//

#ifndef Bamf_InputMapping_h
#define Bamf_InputMapping_h

#include <vector>
#include "IKeyMapping.h"
#include "KeyPressType.h"
#include "IQuitHandler.h"
#include "DefaultQuitHandler.h"
#include "NetworkingModule.h"
#include "UpdateExecutor.h"

namespace bamf {

class InputMapping
{
    
private:
    std::vector<IKeyMapping *> * keyMappings;
    IQuitHandler * quitHandler;
    
    
public:
    InputMapping();
    void addKeyMapping(IKeyMapping * keyMapping);
    std::vector<IKeyMapping *> * getKeyMappings();

    void dispatchKeyEvent(KeyPressType pressType, int keyCode, ...);

    void setQuitHandler(IQuitHandler * quitHandler);
    IQuitHandler * getQuitHandler();
};

}
    
#endif