//
//  Real.h
//  CompileFrontEnd
//
//  Created by Mark Young on 13-6-20.
//  Copyright (c) 2013年 Boy-Mark. All rights reserved.
//

#ifndef __CompileFrontEnd__Real__
#define __CompileFrontEnd__Real__

#include <iostream>
#include "Token.h"

class Real :public Token {
    
    
public:
    const float value;
    Real(float v)
    :Token(Tag::REAL), value(v)
    {}
    string toString();
};
#endif /* defined(__CompileFrontEnd__Real__) */
