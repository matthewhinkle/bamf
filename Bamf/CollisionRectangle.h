//
//  CollisionRectangle.h
//  Bamf
//
//  Created by Anthony Dagostino on 2/11/13.
//
//

#ifndef __Bamf__CollisionRectangle__
#define __Bamf__CollisionRectangle__

#include <iostream>
#include "CollisionShape.h"
#include "Rectangle.h"

namespace bamf {

class CollisionRectangle: public CollisionShape {
public:
    CollisionRectangle(Rectangle r);
    ~CollisionRectangle();
    
protected:
    
private:
    

};
}
#endif /* defined(__Bamf__CollisionRectangle__) */

