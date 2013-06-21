//
//  Array.h
//  CompileFrontEnd
//
//  Created by Mark Young on 13-6-19.
//  Copyright (c) 2013年 Boy-Mark. All rights reserved.
//

#ifndef __CompileFrontEnd__Array__
#define __CompileFrontEnd__Array__

#include <iostream>
#include "Type.h"

class Array : public Type {
    
    
public:
    Type of;                  // array *of* type
    int size = 1;             // number of elements
    Array(int sz, Type p)
    :Type("[]", Tag::INDEX, sz*p.width), size(sz), of(p)
    {}
    
    string toString();
};
#endif /* defined(__CompileFrontEnd__Array__) */
