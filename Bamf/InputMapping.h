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

class InputMapping
{
    
private:
    std::vector<IKeyMapping *> * keyMappings;
    
public:
    InputMapping();
    void addKeyMapping(IKeyMapping * keyMapping);

};

#endif
