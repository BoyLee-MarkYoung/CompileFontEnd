//
//  Num.h
//  CompileFrontEnd
//
//  Created by Mark Young on 13-6-20.
//  Copyright (c) 2013年 Boy-Mark. All rights reserved.
//

#ifndef __CompileFrontEnd__Num__
#define __CompileFrontEnd__Num__

#include <iostream>
#include "Token.h"

class Num :public Token {
    
    
public:
    const int value;
    Num(int v)
    :Token(Tag::NUM), value(v)
    {}
    string toString();
};
#endif /* defined(__CompileFrontEnd__Num__) */
